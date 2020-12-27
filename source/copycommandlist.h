#ifndef _DEC_COPYCOMMANDLIST_
#define _DEC_COPYCOMMANDLIST_

#include "header.h"
#include "commandlist.h"

popBegin

class CopyCommandlist : public CommandList
{
public:
	CopyCommandlist(const Device& device);
	CopyCommandlist(const Device& device, U32 familyIndex);
	~CopyCommandlist();
};

popEnd

#endif // _DEC_COPYCOMMANDLIST_

