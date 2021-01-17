#ifndef _DEC_TEXTURERESOURCE_
#define _DEC_TEXTURERESOURCE_

#include "header.h"

popBegin
class Device;
class GPUMemoryLayout;
struct TextureCreation;

class TextureResource
{
	DEFINE_PRAVATE_MEMBER_HANDLE(VkImage, Image)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(VkFormat, Format)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(TextureType, ImageType)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, Width)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, Height)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, Depth)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, Level)
	DEFINE_PRAVATE_MEMBER_BASE_TYPE(U32, ArraySize)
public:
	TextureResource(const Device& device, const GPUMemoryLayout& memoryLayout, const TextureCreation& textureCreation);
	~TextureResource();
private:
	
	const Device& m_Device;
};

popEnd

#endif // _DEC_TEXTURERESOURCE_

