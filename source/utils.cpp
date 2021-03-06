#include "utils.h"

popBegin

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	QueueFamilyIndices queueFamilyIndices;

	U32 queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	Vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	U32 i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 
			&& queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
		{
			VkBool32 presentSupport = false;

			popCallAPI(vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport));

			if (queueFamily.queueCount > 0 && presentSupport) {
				queueFamilyIndices.GraphicsFamily = i;
			}

			queueFamilyIndices.GraphicsFamily = i;
		}

		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
		{
			queueFamilyIndices.ComputeFamily = i;
		}

		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
		{
			queueFamilyIndices.CopyFamily = i;
		}
		
		if (queueFamilyIndices.isComplete())
		{
			break;
		}

		i++;
	}

	return queueFamilyIndices;
}

popEnd
