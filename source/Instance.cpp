#include "Instance.h"

popBegin

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{	
	popLogError(pCallbackData->pMessage);
	return VK_FALSE;
}

Instance::Instance(funcVulkanExtensions extensionFunc, funVulkanCreateSurface surfaceFunc, BOOL enableValidateLayer)
	: m_FuncVulkanExtension(extensionFunc)
	, m_FuncVulkanCreateSurface(surfaceFunc)
	, m_Instance(VK_NULL_HANDLE)
	, m_Surface(VK_NULL_HANDLE)
	, m_PhysicalDevice(VK_NULL_HANDLE)
	, m_EnableValidateLayer(enableValidateLayer)
{
	CreateInstance();
	InitFunc();
	CreatePhysicalDevice();
	CreateSurface();
	CreateQueueCreateInfo();
}

Instance::~Instance()
{
	popAssert(m_Surface);
	popAssert(m_PhysicalDevice);
	if (m_EnableValidateLayer)
	{
		m_FuncDestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
	}
	vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
	vkDestroyInstance(m_Instance, nullptr);
}

void Instance::InitFunc()
{
	m_FuncCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkCreateDebugUtilsMessengerEXT");
	m_FuncDestroyDebugUtilsMessengerEXT	= (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkDestroyDebugUtilsMessengerEXT");
	popAssert(m_FuncCreateDebugUtilsMessengerEXT);
	popAssert(m_FuncDestroyDebugUtilsMessengerEXT);
	popCallAPI(m_FuncCreateDebugUtilsMessengerEXT(m_Instance, &m_DebugUtilsMessengerCreateInfoEXT, nullptr, &m_DebugMessenger));
}

void Instance::CreateSurface()
{
	popCallAPI(m_FuncVulkanCreateSurface(m_Instance, m_Surface));
}

void Instance::CreateInstance()
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pEngineName = "Dec";
	appInfo.pApplicationName = "Dec";
	appInfo.apiVersion = VK_API_VERSION_1_0;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

	CheckRequiredExtension();

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.enabledExtensionCount = (U32)m_RequireVulkanExtensionNames.size();
	createInfo.ppEnabledExtensionNames = m_RequireVulkanExtensionNames.data();
	if (m_EnableValidateLayer && FoundRequiredLayer())
	{
		createInfo.enabledLayerCount = (U32)g_ValidationLayers.size();
		createInfo.ppEnabledLayerNames = g_ValidationLayers.data();
		
		m_DebugUtilsMessengerCreateInfoEXT = {};
		m_DebugUtilsMessengerCreateInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		m_DebugUtilsMessengerCreateInfoEXT.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		m_DebugUtilsMessengerCreateInfoEXT.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		m_DebugUtilsMessengerCreateInfoEXT.pfnUserCallback = debugCallback;
		createInfo.pNext = &m_DebugUtilsMessengerCreateInfoEXT;
	}
	
	createInfo.pApplicationInfo = &appInfo;

	//TODO: Need the user memory allocation callback.
	popCallAPI(vkCreateInstance(&createInfo, nullptr, &m_Instance));
}

void Instance::CreatePhysicalDevice()
{
	static const U32 defaultDeviceIndex = 0;
	U32 deviceCount = 0;
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

	popAssert(deviceCount != 0);

	Vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

	//TODO : Check the GPU ability of device.
	m_PhysicalDevice = devices[defaultDeviceIndex];
}

void Instance::CreateQueueCreateInfo()
{
	m_QueueFamilyIndices = findQueueFamilies(GetPhysicalDevice(), m_Surface);

	Vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	Set<U32> uniqueQueueFamilies =
	{
		m_QueueFamilyIndices.GraphicsFamily.value(),
		m_QueueFamilyIndices.ComputeFamily.value(),
		m_QueueFamilyIndices.CopyFamily.value()
	};

	float queuePriority = 1.0f;
	for (U32 queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		m_QueueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures = {};
	deviceFeatures.samplerAnisotropy = VK_TRUE;
}

void Instance::CheckRequiredExtension()
{
	m_FuncVulkanExtension(m_RequireVulkanExtensionNames);
	if (m_EnableValidateLayer) 
	{
		m_RequireVulkanExtensionNames.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}
}

BOOL Instance::FoundRequiredLayer()
{
	U32 instaceLayerCount = 0;
	vkEnumerateInstanceLayerProperties(&instaceLayerCount, nullptr);
	Vector<VkLayerProperties> layerProperties(instaceLayerCount);
	vkEnumerateInstanceLayerProperties(&instaceLayerCount, layerProperties.data());

	for (auto& validateLayerName : g_ValidationLayers)
	{
		for (auto& layerProperty : layerProperties)
		{
			if (strcmp(layerProperty.layerName, validateLayerName) == 0)
			{
				return true;
			}
		}
	}

	return false;
}

popEnd