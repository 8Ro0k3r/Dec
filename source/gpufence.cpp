#include "GpuFence.h"
#include "device.h"

popBegin

GpuFence::GpuFence(const Device& device)
	: m_Device(device)
{
	VkSemaphoreCreateInfo semaphoreCreateInfo = {};
	semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	popCallAPI(vkCreateSemaphore(device.GetDevice(), &semaphoreCreateInfo, nullptr, &m_Sync));
}

GpuFence::~GpuFence()
{
	vkDestroySemaphore(m_Device.GetDevice(), m_Sync, nullptr);
}

popEnd
