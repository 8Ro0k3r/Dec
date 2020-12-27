#include "Instance.h"

popBegin

Instance::Instance(funcVulkanExtensions& vulkanExtension, BOOL needValidateLayer)
	: m_FuncVulkanExtension(vulkanExtension)
	, m_PhysicalDevice(VK_NULL_HANDLE)
	, m_Surface(VK_NULL_HANDLE)
{
	CreateInstance(needValidateLayer);
	CreatePhysicalDevice();
	CreateQueueCreateInfo();
}

Instance::~Instance()
{
	popAssert(m_Surface);
	popAssert(m_PhysicalDevice);
	vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
	vkDestroyInstance(m_Instance, nullptr);
}

void Instance::CreateInstance(BOOL needValidateLayer)
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pEngineName = "Dirty";
	appInfo.pApplicationName = "Dirty";
	appInfo.apiVersion = VK_API_VERSION_1_0;
	appInfo.applicationVersion = VK_API_VERSION_1_0;
	appInfo.engineVersion = VK_API_VERSION_1_0;

	CheckRequiredExtension();

	BOOL foundValidateLayer = false;
	if (needValidateLayer)
	{
		foundValidateLayer = FoundRequiredLayer();
	}

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.enabledExtensionCount = (U32)m_RequireVulkanExtensionNames.size();
	createInfo.ppEnabledExtensionNames = m_RequireVulkanExtensionNames.data();
	createInfo.enabledLayerCount = foundValidateLayer ? (U32)validationLayers.size() : 0;
	createInfo.ppEnabledLayerNames = foundValidateLayer ? validationLayers.data() : nullptr;
	createInfo.pApplicationInfo = &appInfo;

	//TODO: Need the user memory allocation callback.
	vkCreateInstance(&createInfo, nullptr, &m_Instance);
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
		m_QueueFamilyIndices.PresentFamily.value()
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
	U32 extensionNameCount = 0;
	CHAR** extensionNames = m_FuncVulkanExtension(extensionNameCount);

	if (extensionNameCount > 0)
	{
		Vector<const CHAR*> vExtensionNames(extensionNames, extensionNames + extensionNameCount);
		m_RequireVulkanExtensionNames = std::move(vExtensionNames);
	}
}

BOOL Instance::FoundRequiredLayer()
{
	U32 instaceLayerCount = 0;
	vkEnumerateInstanceLayerProperties(&instaceLayerCount, nullptr);
	Vector<VkLayerProperties> layerProperties(instaceLayerCount);
	vkEnumerateInstanceLayerProperties(&instaceLayerCount, layerProperties.data());

	for (auto& validateLayerName : validationLayers)
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

S32 Instance::GetGraphicsFamilyIndex() const
{
	if (m_QueueFamilyIndices.GraphicsFamily.has_value())
	{
		return 	m_QueueFamilyIndices.GraphicsFamily.value();
	}
	else
	{
		return -1;
	}
}

S32 Instance::GetComputeFamilyIndex() const
{
	if (m_QueueFamilyIndices.GraphicsFamily.has_value())
	{
		return 	m_QueueFamilyIndices.ComputeFamily.value();
	}
	else
	{
		return -1;
	}
}

S32 Instance::GetPresentFamilyIndex() const
{
	if (m_QueueFamilyIndices.GraphicsFamily.has_value())
	{
		return 	m_QueueFamilyIndices.PresentFamily.value();
	}
	else
	{
		return -1;
	}
}

popEnd