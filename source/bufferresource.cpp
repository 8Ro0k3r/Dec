#include "bufferresource.h"
#include "gpumemorylayout.h"
#include "gpumemoryheap.h"
#include "device.h"

popBegin

VkBufferUsageFlagBits UsageToVKBufferUsageFlagBit(BufferUsage usage)
{
	static const VkBufferUsageFlagBits bufferUsageFlagBitsLUT[] =
	{
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT,
		VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
		VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
		VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT,
		VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT,
		VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT,
		VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT,
		VK_BUFFER_USAGE_RAY_TRACING_BIT_NV,
		VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_EXT
	};

	popAssert((U32)usage > popArraySize(bufferUsageFlagBitsLUT));
	return bufferUsageFlagBitsLUT[(U32)usage];
}

BufferResource::BufferResource(const Device& device, const GPUMemoryLayout& memoryLayout, BufferUsage usage)
	: m_Device(device)
	, m_MapPtr(nullptr)
{
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = memoryLayout.GetSize();
	bufferInfo.usage = usage;
	// TODO VkSharingMode
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	popCallAPI(vkCreateBuffer(device.GetDevice(), &bufferInfo, nullptr, &m_Buffer));
	vkBindBufferMemory(device.GetDevice(), m_Buffer, memoryLayout.GetPool().GetMemoryHeap(), memoryLayout.GetOffset());

	if (memoryLayout.GetPool().GetMapPtr())
	{
		m_MapPtr = (void*)((PTRDIFF)(memoryLayout.GetPool().GetMapPtr()) + memoryLayout.GetOffset());
	}
}

void* BufferResource::Map()
{
	return m_MapPtr;
}

void BufferResource::Unmap()
{
}

BufferResource::~BufferResource()
{
	vkDestroyBuffer(m_Device.GetDevice(), m_Buffer, nullptr);
}

popEnd