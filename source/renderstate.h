#ifndef _DEC_RENDERSTATE_
#define _DEC_RENDERSTATE_

#include "header.h"

popBegin

class RenderState
{
	DEFINE_PRAVATE_MEMBER_HANDLE(VkPipelineViewportStateCreateInfo, ViewportState)
	DEFINE_PRAVATE_MEMBER_HANDLE(VkPipelineRasterizationStateCreateInfo, Rasterizer)
	DEFINE_PRAVATE_MEMBER_HANDLE(VkPipelineMultisampleStateCreateInfo, Multisampling)
	DEFINE_PRAVATE_MEMBER_HANDLE(VkPipelineDepthStencilStateCreateInfo, DepthStencil)
	DEFINE_PRAVATE_MEMBER_HANDLE(VkPipelineColorBlendStateCreateInfo, ColorBlending)
	DEFINE_PRAVATE_MEMBER_HANDLE(VkPipelineColorBlendAttachmentState, ColorBlendAttachment)
public:
	RenderState();
	~RenderState();
	void Reset();
};

popEnd

#endif // _DEC_RENDERSTATE_
