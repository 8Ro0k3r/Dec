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

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

popEnd

#endif // _DEC_UTILS_

