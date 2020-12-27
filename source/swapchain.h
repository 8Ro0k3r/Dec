#ifndef _DEC_SWAPCHAIN_
#define _DEC_SWAPCHAIN_	

#include "header.h"

popBegin

class Device;

class SwapChain
{
public:
	SwapChain(const Device& device);
	~SwapChain();
private:
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat();
	VkPresentModeKHR ChooseSwapPresentMode();
	VkExtent2D ChooseSwapExtent();

	const Device&				m_Device;
	VkSwapchainKHR				m_SwapChain;
	VkPresentModeKHR			m_PresentMode;
	VkSurfaceFormatKHR			m_SurfaceFormat;
	VkSurfaceCapabilitiesKHR	m_Capabilities;
	Vector<VkImage>				m_SwapChainImages;
};

popEnd

#endif // _DEC_SWAPCHAIN_

