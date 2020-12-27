#include "renderstate.h"

 popBegin

RenderState::RenderState()
{
	 Reset();
}


 RenderState::~RenderState()
{
}

void RenderState::Reset()
{
	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)pop1080pWidth;
	viewport.height = (float)pop1080pHeight;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {};
	scissor.offset = { 0, 0 };
	scissor.extent = { pop1080pWidth, pop1080pHeight };

	m_ViewportState = {};
	m_ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	m_ViewportState.viewportCount = 1;
	m_ViewportState.pViewports = &viewport;
	m_ViewportState.scissorCount = 1;
	m_ViewportState.pScissors = &scissor;

	m_Rasterizer = {};
	m_Rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	m_Rasterizer.depthClampEnable = VK_FALSE;
	m_Rasterizer.rasterizerDiscardEnable = VK_FALSE;
	m_Rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	m_Rasterizer.lineWidth = 1.0f;
	m_Rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	m_Rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	m_Rasterizer.depthBiasEnable = VK_FALSE;

	m_Multisampling = {};
	m_Multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	m_Multisampling.sampleShadingEnable = VK_TRUE;
	m_Multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	m_DepthStencil = {};
	m_DepthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	m_DepthStencil.depthTestEnable = VK_TRUE;
	m_DepthStencil.depthWriteEnable = VK_TRUE;
	m_DepthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	m_DepthStencil.depthBoundsTestEnable = VK_FALSE;
	m_DepthStencil.stencilTestEnable = VK_FALSE;

	m_ColorBlendAttachment = {};
	m_ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	m_ColorBlendAttachment.blendEnable = VK_FALSE;

	m_ColorBlending = {};
	m_ColorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	m_ColorBlending.logicOpEnable = VK_FALSE;
	m_ColorBlending.logicOp = VK_LOGIC_OP_COPY;
	m_ColorBlending.attachmentCount = 1;
	m_ColorBlending.pAttachments = &m_ColorBlendAttachment;
	m_ColorBlending.blendConstants[0] = 0.0f;
	m_ColorBlending.blendConstants[1] = 0.0f;
	m_ColorBlending.blendConstants[2] = 0.0f;
	m_ColorBlending.blendConstants[3] = 0.0f;
}

popEnd
