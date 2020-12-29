#include "gpumemorylayout.h"

popBegin

GPUMemoryLayout::GPUMemoryLayout(const GPUMemoryHeap& pool, U32 size, U32 offset, U32 alignment)
	: m_Pool(pool)
	, m_Size(size)
	, m_Offset(offset)
	, m_Alignment(alignment)
{
}


GPUMemoryLayout::~GPUMemoryLayout()
{
}

popEnd
