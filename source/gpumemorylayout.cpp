#include "gpumemorylayout.h"

popBegin

GPUMemoryLayout::GPUMemoryLayout(const GPUMemoryHeap& pool, const BufferCreation& creation)
	: m_Pool(pool)
{

}

GPUMemoryLayout::GPUMemoryLayout(const GPUMemoryHeap& pool, const TextureCreation& creation)
	: m_Pool(pool)
{

}


GPUMemoryLayout::~GPUMemoryLayout()
{
}

popEnd
