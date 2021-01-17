#ifndef _DEC_BUFFERVIEWRO_
#define _DEC_BUFFERVIEWRO_

#include "header.h"
#include "descriptor.h"

popBegin
class Device;
class BufferViewRO : public Descriptor
{
public:
	BufferViewRO(const Device& device);
	~BufferViewRO();
};

popEnd

#endif // _DEC_BUFFERVIEWRO_