#ifndef _DEC_GRAPHICCOMMANDLIST_
#define _DEC_GRAPHICCOMMANDLIST_

#include "header.h"
#include "computecommandlist.h"

popBegin

class GraphicsCommandList : public ComputeCommandList
{
public:
	GraphicsCommandList(const Device& device);
	~GraphicsCommandList();
};

popEnd

#endif // _DEC_GRAPHICCOMMANDLIST_
