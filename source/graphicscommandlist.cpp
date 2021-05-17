#include "GraphicsCommandList.h"
#include "device.h"
#include "Instance.h"
popBegin

GraphicsCommandList::GraphicsCommandList(const Device& device, const CommandAllocator& commandAllcator)
	: ComputeCommandList(device, commandAllcator)
{
}

GraphicsCommandList::~GraphicsCommandList()
{
}

popEnd
