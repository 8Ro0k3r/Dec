#ifndef _DEC_COMPUTECOMMANDLIST_
#define _DEC_COMPUTECOMMANDLIST_

#include "header.h"
#include "copycommandlist.h"

popBegin

class ComputeCommandList : public CopyCommandlist
{
public:
	ComputeCommandList(const Device& device, const CommandAllocator& commandAllcator);
	~ComputeCommandList();
};

popEnd

#endif // _DEC_COMPUTECOMMANDLIST_
