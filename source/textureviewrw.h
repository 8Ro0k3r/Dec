#ifndef _DEC_TEXTUREVIEWRW_
#define _DEC_TEXTUREVIEWRW_

#include "header.h"
#include "descriptor.h"

popBegin
class Device;
class TextureResource;
class TextureViewRW : public Descriptor
{
public:
	TextureViewRW(const Device& device, const TextureResource& resource);
	~TextureViewRW();
};

popEnd

#endif // _DEC_TEXTUREVIEWRW_

