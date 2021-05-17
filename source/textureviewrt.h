#ifndef _DEC_TEXTUREVIEWRT_
#define _DEC_TEXTUREVIEWRT_

#include "header.h"
#include "descriptor.h"

popBegin

class Device;
class TextureResource;

class TextureTiewRT
{
public:
	TextureTiewRT(const Device& device, const TextureResource& textureResource, const TextureViewCreation& textureCreation);
	~TextureTiewRT();
	inline const VkImageView GetImageView() const { return m_ImageView; }
private:
	VkImageView m_ImageView;
};

popEnd

#endif //  _DEC_TEXTUREVIEWRT_

