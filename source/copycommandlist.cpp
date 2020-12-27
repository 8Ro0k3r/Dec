#include "CopyCommandlist.h"
#include "device.h"
#include "instance.h"
popBegin

CopyCommandlist::CopyCommandlist(const Device& device)
	: CommandList(device, device.GetInstance().GetGraphicsFamilyIndex())
{

}

CopyCommandlist::CopyCommandlist(const Device& device, U32 familyIndex)
	: CommandList(device, familyIndex)
{
}


CopyCommandlist::~CopyCommandlist()
{
}

popEnd
