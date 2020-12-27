#include "device.h"
#include "Instance.h"

popBegin

Device::Device(const Instance& instance)
	: m_Instance(instance)
{
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	const Vector<VkDeviceQueueCreateInfo>& queueCreateInfos = instance.GetDeviceQueueCreateInfos();
	const VkPhysicalDeviceFeatures& deviceFeatures = instance.GetPhysicalDeviceFeatures();
	const Vector<const CHAR*>& deviceExtensions = m_Instance.GetExtensionNames();
	const Vector<const CHAR*>& validationLayers = m_Instance.GetValidateLayerNames();

	//TODO
	BOOL enableValidationLayers = false;

	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	popCallAPI(vkCreateDevice(instance.GetPhysicalDevice(), &createInfo, nullptr, &m_Device));
}

Device::~Device()
{
	vkDestroyDevice(m_Device, nullptr);
}

popEnd
