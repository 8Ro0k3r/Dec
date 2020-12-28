#ifndef _DEC_GPUMEMORYLAYOUT_
#define _DEC_GPUMEMORYLAYOUT_

#include "header.h"

popBegin
class GPUMemoryHeap;

class GPUMemoryLayout
{
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, Size)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, Offset)
	DEFINE_PRAVATE_CONST_MEMBER_REFERENCE(GPUMemoryHeap, Pool)
public:
	GPUMemoryLayout(const GPUMemoryHeap& pool, U32 size, U32 offset);
	~GPUMemoryLayout();
};

popEnd

#endif // _DEC_GPUMEMORYLAYOUT_

