#ifndef _DEC_COMPUTECOMMANDLIST_
#define _DEC_COMPUTECOMMANDLIST_

#include "header.h"
#include "copycommandlist.h"

popBegin

class ComputeCommandList : public CopyCommandlist
{
public:
	ComputeCommandList(const Device& device);
	ComputeCommandList(const Device& device, U32 familyIndex);
	~ComputeCommandList();
};

popEnd

#endif // _DEC_COMPUTECOMMANDLIST_
