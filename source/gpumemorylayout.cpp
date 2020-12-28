#include "gpumemorylayout.h"

popBegin

GPUMemoryLayout::GPUMemoryLayout(const GPUMemoryHeap& pool, U32 size, U32 offset)
	: m_Pool(pool)
	, m_Size(size)
	, m_Offset(offset)
{
}


GPUMemoryLayout::~GPUMemoryLayout()
{
}

popEnd
