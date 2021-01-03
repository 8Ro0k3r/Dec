#ifndef _DEC_TEXTUREVIEWRW_
#define _DEC_TEXTUREVIEWRW_

#include "header.h"
#include "descriptor.h"

popBegin

class TextureViewRW : public Descriptor
{
public:
	TextureViewRW();
	~TextureViewRW();
};

popEnd

#endif // _DEC_TEXTUREVIEWRW_

