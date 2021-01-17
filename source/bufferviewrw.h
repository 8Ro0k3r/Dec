#ifndef _DEC_BUFFERVIEWRW_
#define _DEC_BUFFERVIEWRW_

#include "header.h"
#include "descriptor.h"

popBegin
class Device;
class BufferViewRW : public Descriptor
{
public:
	BufferViewRW(const Device& device);
	~BufferViewRW();
};

popEnd

#endif // _DEC_BUFFERVIEWRW_

