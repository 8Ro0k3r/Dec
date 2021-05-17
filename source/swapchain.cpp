#include "SwapChain.h"
#include "device.h"
#include "Instance.h"
#include "gpufence.h"
#include "queue.h"

popBegin

static const U32 defaultSwapchainBackResourceNum = 3;

SwapChain::SwapChain(const Device& device)
	: m_Device(device)
	, m_Fence(nullptr)
{
	VkPhysicalDevice physicalDevice = device.GetInstance().GetPhysicalDevice();
	VkSurfaceKHR surface = device.GetInstance().GetWindowSurface();
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &m_Capabilities);

	m_SurfaceFormat = ChooseSwapSurfaceFormat();
	m_PresentMode = ChooseSwapPresentMode();
	VkExtent2D extent = ChooseSwapExtent();

	uint32_t imageCount = m_Capabilities.minImageCount + 1;
	if (m_Capabilities.maxImageCount > 0 && imageCount > m_Capabilities.maxImageCount) {
		imageCount = m_Capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = device.GetInstance().GetWindowSurface();

	createInfo.minImageCount = defaultSwapchainBackResourceNum;
	createInfo.imageFormat = m_SurfaceFormat.format;
	createInfo.imageColorSpace = m_SurfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	createInfo.preTransform = m_Capabilities.currentTransform;
	// TODO
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = m_PresentMode;
	createInfo.clipped = VK_TRUE;

	popCallAPI(vkCreateSwapchainKHR(m_Device.GetDevice(), &createInfo,
		nullptr, &m_SwapChain));

	m_SwapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(m_Device.GetDevice(), m_SwapChain, &imageCount,
		m_SwapChainImages.data());

	m_Fence = popNew(GpuFence)(device);

}

SwapChain::~SwapChain()
{
	vkDestroySwapchainKHR(m_Device.GetDevice(), m_SwapChain, nullptr);
	popDelete(m_Fence);
}

VkSurfaceFormatKHR SwapChain::ChooseSwapSurfaceFormat() 
{
	VkPhysicalDevice device = m_Device.GetInstance().GetPhysicalDevice();
	VkSurfaceKHR surface = m_Device.GetInstance().GetWindowSurface();
	Vector<VkSurfaceFormatKHR> availableFormats;

	U32 formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount != 0)
	{
		availableFormats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, availableFormats.data());
	}

	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
		return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}

	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}

VkPresentModeKHR SwapChain::ChooseSwapPresentMode() {
	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;
	VkPhysicalDevice device = m_Device.GetInstance().GetPhysicalDevice();
	VkSurfaceKHR surface = m_Device.GetInstance().GetWindowSurface();
	Vector<VkPresentModeKHR> availablePresentModes;

	U32 presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0)
	{
		availablePresentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, availablePresentModes.data());
	}

	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
		else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
			bestMode = availablePresentMode;
		}
	}

	return bestMode;
}

void SwapChain::Acquire() const
{
	vkAcquireNextImageKHR(m_Device.GetDevice(), m_SwapChain, m_TimeoutMs, m_Fence->GetGpuFence(), VK_NULL_HANDLE, &m_CurrentIndex);
}

void SwapChain::Present(const Queue& queue) const
{
	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &m_Fence->GetGpuFence();

	VkSwapchainKHR swapChains[] = { m_SwapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &m_CurrentIndex;

	vkQueuePresentKHR(queue.GetQueue(), &presentInfo);
}

VkExtent2D SwapChain::ChooseSwapExtent() {
	return { pop1080pWidth, pop1080pHeight };
}

popEnd