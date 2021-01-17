#ifndef _DEC_GPUMEMORYLAYOUT_
#define _DEC_GPUMEMORYLAYOUT_

#include "header.h"

popBegin
class GPUMemoryHeap;

struct BufferCreation
{
	U32 Size;
	U32 Alignment;
};

struct TextureCreation
{
	TextureType		Type;
	U32				Height;
	U32				Width;
	U32				Depth;
	U32				Level;
	U32				ArraySize;
	VkFormat		Format;			// TODO
	TilingMode		Tiling;
	ImageBindFlage  Usage;
	SampleCount		Sample;
};

class GPUMemoryLayout
{
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, Size)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U64, Offset)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, Alignment)
	DEFINE_PRAVATE_CONST_MEMBER_REFERENCE(GPUMemoryHeap, Pool)
public:
	GPUMemoryLayout(const GPUMemoryHeap& pool, const BufferCreation& creation);
	GPUMemoryLayout(const GPUMemoryHeap& pool, const TextureCreation& creation);
	~GPUMemoryLayout();
};

popEnd

#endif // _DEC_GPUMEMORYLAYOUT_

