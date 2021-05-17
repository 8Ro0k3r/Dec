#include "queue.h"
#include "device.h"
#include "Instance.h"
#include "gpufence.h"
#include "cpufence.h"
#include "commandlist.h"
popBegin

Queue::Queue(const Device& device, QueueType type, U32 index)
	: m_Device(device)
{
	const Instance& instance = device.GetInstance();
	U32 queueFamily = instance.GetQueueFamilyIndex(type);
	vkGetDeviceQueue(device.GetDevice(), queueFamily, index, &m_Queue);
}

Queue::~Queue()
{
}

void Queue::Submit(const SubmitInfo& info)
{
	Vector<VkSemaphore> waitSemaphore;
	Vector<VkSemaphore> signalSemaphore;
	Vector<VkCommandBuffer> commandBuffer;
	waitSemaphore.resize(info.WaitFenceCount);
	signalSemaphore.resize(info.SignalFenceCount);
	for (U32 i = 0; i < info.WaitFenceCount; i++)
	{
		waitSemaphore[i] = info.WaitFencesPtr[i].GetGpuFence();
	}
	for (U32 j = 0; j < info.WaitFenceCount; j++)
	{
		signalSemaphore[j] = info.SignalFencesPtr[j].GetGpuFence();
	}
	for (U32 k = 0; k < info.CommandBufferCount; k++)
	{
		commandBuffer[k] = info.CommandBuffersPtr[k].GetCommandBuffer();
	}

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = info.WaitFenceCount;
	submitInfo.pWaitSemaphores = waitSemaphore.data();
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = info.CommandBufferCount;
	submitInfo.pCommandBuffers = commandBuffer.data();
	submitInfo.signalSemaphoreCount = info.SignalFenceCount;
	submitInfo.pSignalSemaphores = signalSemaphore.data();

	popCallAPI(vkQueueSubmit(m_Queue, 1, &submitInfo, info.Fence.GetFence()));
}

popEnd