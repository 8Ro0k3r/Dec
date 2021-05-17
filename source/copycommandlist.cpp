#include "CopyCommandlist.h"
#include "device.h"
#include "instance.h"
popBegin

CopyCommandlist::CopyCommandlist(const Device& device, const CommandAllocator& commandAllcator)
	: CommandList(device, commandAllcator)
{
}


CopyCommandlist::~CopyCommandlist()
{
}

popEnd
