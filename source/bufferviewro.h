#ifndef _DEC_BUFFERVIEWRO_
#define _DEC_BUFFERVIEWRO_

#include "header.h"
#include "descriptor.h"

popBegin

class BufferViewRO : public Descriptor
{
public:
	BufferViewRO();
	~BufferViewRO();
};

popEnd

#endif // _DEC_BUFFERVIEWRO_