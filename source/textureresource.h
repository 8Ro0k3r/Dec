#ifndef _DEC_TEXTURERESOURCE_
#define _DEC_TEXTURERESOURCE_

#include "header.h"

popBegin

class Device;
class GPUMemoryLayout;

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

class TextureResource
{
	DEFINE_PRAVATE_MEMBER_HANDLE(VkImage, Image)
public:
	TextureResource(const Device& device, const GPUMemoryLayout& memoryLayout, const TextureCreation& textureCreation);
	~TextureResource();
private:
	const Device& m_Device;
};

popEnd

#endif // _DEC_TEXTURERESOURCE_

