#ifndef _DEC_TEXTUREVIEWRO_
#define _DEC_TEXTUREVIEWRO_

#include "header.h"
#include "descriptor.h"

popBegin

class TextureViewRO	: public Descriptor
{
public:
	TextureViewRO();
	~TextureViewRO();
};

popEnd

#endif //  _DEC_TEXTUREVIEWRO_

