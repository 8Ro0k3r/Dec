#ifndef _DEC_BUFFERVIEWRW_
#define _DEC_BUFFERVIEWRW_

#include "header.h"
#include "descriptor.h"

popBegin

class BufferViewRW : public Descriptor
{
public:
	BufferViewRW();
	~BufferViewRW();
};

popEnd

#endif // _DEC_BUFFERVIEWRW_

