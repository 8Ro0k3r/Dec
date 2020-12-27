#include "computecommandlist.h"
#include "device.h"
#include "Instance.h"
popBegin

ComputeCommandList::ComputeCommandList(const Device& device)
	: CopyCommandlist(device, device.GetInstance().GetComputeFamilyIndex())
{
}

ComputeCommandList::ComputeCommandList(const Device& device, U32 familyIndex)
	: CopyCommandlist(device, familyIndex)
{

}


ComputeCommandList::~ComputeCommandList()
{
}

popEnd