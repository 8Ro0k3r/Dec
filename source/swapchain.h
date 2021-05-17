#ifndef _DEC_SWAPCHAIN_
#define _DEC_SWAPCHAIN_	

#include "header.h"

popBegin

class Device;
class GpuFence;
class Queue;

class SwapChain
{
public:
	SwapChain(const Device& device);
	~SwapChain();
	void Acquire() const;
	void Present(const Queue& queue) const;
	inline VkImage GetBackBuffer(U32 index) const { return m_SwapChainImages[index]; }
	inline U32 GetCurrentIndex() const { return m_CurrentIndex; }
private:
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat();
	VkPresentModeKHR ChooseSwapPresentMode();
	VkExtent2D ChooseSwapExtent();
	static const U32			m_TimeoutMs = 1000;
	const Device&				m_Device;
	GpuFence*					m_Fence;
	VkSwapchainKHR				m_SwapChain;
	VkPresentModeKHR			m_PresentMode;
	VkSurfaceFormatKHR			m_SurfaceFormat;
	VkSurfaceCapabilitiesKHR	m_Capabilities;
	Vector<VkImage>				m_SwapChainImages;
	mutable U32					m_CurrentIndex;
};

popEnd

#endif // _DEC_SWAPCHAIN_

