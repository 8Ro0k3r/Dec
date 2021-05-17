#include "commandlist.h"
#include "device.h"
#include "commandallocator.h"
popBegin

CommandList::CommandList(const Device& device, const CommandAllocator& commandAllcator)
	: m_Device(device)
	, m_CommandBuffer(VK_NULL_HANDLE)
	, m_PoolRef(commandAllcator.GetCommandPool())
{
}

CommandList::~CommandList()
{
	Free();	
}

void CommandList::Free()
{
	if (m_CommandBuffer != VK_NULL_HANDLE)
	{
		vkFreeCommandBuffers(m_Device.GetDevice(), m_PoolRef, 1, &m_CommandBuffer);
	}
}

void CommandList::Begin()
{		
	Free();

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = m_PoolRef;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(m_Device.GetDevice(), &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);
}

void CommandList::End()
{
	vkEndCommandBuffer(m_CommandBuffer);

}

popEnd
