#include "commandallocator.h"
#include "device.h"
#include "Instance.h"
popBegin

CommandAllocator::CommandAllocator(const Device& device, QueueType type)
	: m_Device(device)
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = device.GetInstance().GetQueueFamilyIndex(type);
	popCallAPI(vkCreateCommandPool(m_Device.GetDevice(), &poolInfo, nullptr, &m_CommandPool));
}


CommandAllocator::~CommandAllocator()
{
	vkDestroyCommandPool(m_Device.GetDevice(), m_CommandPool, nullptr);
}

popEnd