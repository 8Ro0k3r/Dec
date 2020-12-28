#ifndef _DEC_UTILS_
#define _DEC_UTILS_

#include "header.h"

popBegin

struct QueueFamilyIndices {
	Placehoder<U32> GraphicsFamily;
	Placehoder<U32> ComputeFamily;
	Placehoder<U32> PresentFamily;

	inline BOOL isComplete()
	{
		return GraphicsFamily.has_value() &&
			ComputeFamily.has_value() &&
			PresentFamily.has_value();
	}
};

union GPUMemoryPoolKey
{
	struct 
	{
		U32 AccessFlags : 8;
		U32 MemoryType : 2;
		U32 Unused : 22;
	} m_AllFlags;

	U32 m_Key;
};

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

popEnd

#endif // _DEC_UTILS_

