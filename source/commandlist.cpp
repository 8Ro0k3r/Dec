#include "commandlist.h"
#include "device.h"
popBegin

CommandList::CommandList(const Device& device, U32 familyIndex)
	: m_Device(device)
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = familyIndex;

	popCallAPI(vkCreateCommandPool(device.GetDevice(), &poolInfo,
		nullptr, &m_CommandPool));
}


CommandList::~CommandList()
{
	popAssert(m_CommandPool);
	vkDestroyCommandPool(m_Device.GetDevice(), m_CommandPool, nullptr);
}

popEnd
