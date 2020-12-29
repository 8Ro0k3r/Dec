#include "gpumemoryheap.h"
#include "utils.h"
#include "device.h"
#include "instance.h"

popBegin

static U32 FindMemoryType(VkPhysicalDevice physicalDevice, U32 typeFilter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

	for (U32 i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}

	popAssert(0);
	return 0;
}

static U32 UsageToMemoryType(U32 usage)
{
	// TODO
	return 0;
}

static VkMemoryPropertyFlags AccessFlagToMemoryProperties(U32 accessFlag)
{
	U32 result = 0;
	
	if (accessFlag & CPU_READ)
	{
		result |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
	}
	if (accessFlag & CPU_WRITE)
	{
		result |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	}
	if (accessFlag & CPU_WRITECOMBINED)
	{
		result |= VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
	}
	if (accessFlag & GPU_READWRITE)
	{
		result |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
	}
	return 	(VkMemoryPropertyFlags)result;
}

// TODO : Alignment
GPUMemoryHeap::GPUMemoryHeap(const Device& device, const GPUMemoryHeapCreation& creation)
	: m_Device(device)
	, m_Size(creation.Size)
	, m_Alignment(creation.Alignment)
	, m_HeapKey(creation.HeapKey)
	, m_MapPtr(nullptr)
{
	GPUMemoryPoolKey heapKey;
	heapKey.m_Key = m_HeapKey;
	U32 accessFlag = heapKey.m_AllFlags.AccessFlags;

	U32 memoryType = UsageToMemoryType(creation.Usage);
	VkMemoryPropertyFlags memoryProperty = AccessFlagToMemoryProperties(accessFlag);
	
	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = m_Size;
	allocInfo.memoryTypeIndex = FindMemoryType(device.GetInstance().GetPhysicalDevice(),
		memoryType, memoryProperty);

	popCallAPI(vkAllocateMemory(device.GetDevice(), &allocInfo, nullptr, &m_MemoryHeap));

	if (accessFlag | CPU_READWRITE)
	{
		//TODO :  VkMemoryMapFlags
		popCallAPI(vkMapMemory(device.GetDevice(), m_MemoryHeap, 0, m_Size, 0, &m_MapPtr));
	}
}

GPUMemoryHeap::~GPUMemoryHeap()
{
	vkFreeMemory(m_Device.GetDevice(), m_MemoryHeap, nullptr);
}

popEnd
