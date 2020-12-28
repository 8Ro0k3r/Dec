#ifndef _DEC_GPUMEMORYLAYOUT_
#define _DEC_GPUMEMORYLAYOUT_

#include "header.h"

popBegin
class Device;

struct GPUMemoryHeapCreation
{
	U32 Size;
	U32 Alignment;
	U32 HeapKey;
	U32 Usage;
};

class GPUMemoryHeap
{
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, Size)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, Alignment)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, HeapKey)
	DEFINE_PRAVATE_MEMBER_PTR(void, MapPtr)
	DEFINE_PRAVATE_MEMBER_HANDLE(VkDeviceMemory, MemoryHeap)
public:
	GPUMemoryHeap(const Device& device, const GPUMemoryHeapCreation& creation);
	~GPUMemoryHeap();
private:
	const Device& m_Device;
};

popEnd

#endif // _DEC_GPUMEMORYLAYOUT_

