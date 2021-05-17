#include "computecommandlist.h"
#include "device.h"
#include "Instance.h"
popBegin

ComputeCommandList::ComputeCommandList(const Device& device, const CommandAllocator& commandAllcator)
	: CopyCommandlist(device, commandAllcator)
{

}


ComputeCommandList::~ComputeCommandList()
{
}

popEnd