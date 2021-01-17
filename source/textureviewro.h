#ifndef _DEC_TEXTUREVIEWRO_
#define _DEC_TEXTUREVIEWRO_

#include "header.h"
#include "descriptor.h"

popBegin
class Device;
class TextureResource;
class TextureViewRO	: public Descriptor
{
public:
	TextureViewRO(const Device& device, const TextureResource& resource);
	~TextureViewRO();
};

popEnd

#endif //  _DEC_TEXTUREVIEWRO_

