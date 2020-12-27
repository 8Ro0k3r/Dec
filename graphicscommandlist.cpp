#include "GraphicsCommandList.h"
#include "device.h"
#include "Instance.h"
popBegin

GraphicsCommandList::GraphicsCommandList(const Device& device)
	: ComputeCommandList(device, device.GetInstance().GetGraphicsFamilyIndex())
{
}


GraphicsCommandList::~GraphicsCommandList()
{
}

popEnd
