#ifndef _DEC_COPYCOMMANDLIST_
#define _DEC_COPYCOMMANDLIST_

#include "header.h"
#include "commandlist.h"

popBegin

class CopyCommandlist : public CommandList
{
public:
	CopyCommandlist(const Device& device, const CommandAllocator& commandAllcator);
	~CopyCommandlist();
};

popEnd

#endif // _DEC_COPYCOMMANDLIST_

