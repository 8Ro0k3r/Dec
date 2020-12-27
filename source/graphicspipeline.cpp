#include "graphicspipeline.h"
#include "device.h"
#include "renderstate.h"
#include "shader.h"

popBegin

VkShaderStageFlagBits DecToVkShaderStageFlagBits(ShaderStage stage)
{
	static VkShaderStageFlagBits  VkShaderStageFlagBitsLUT[] = 
	{
	   VK_SHADER_STAGE_VERTEX_BIT,
	   VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
	   VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
	   VK_SHADER_STAGE_GEOMETRY_BIT,
	   VK_SHADER_STAGE_FRAGMENT_BIT,
	};

	popAssert((U32)stage < ShaderStage::SHADER_COUNT);
	return 	VkShaderStageFlagBitsLUT[(U32)stage];
}

GraphicsPipeline::GraphicsPipeline(const Device& device, const RenderState& renderstate,
	const GraphicsPipelineStateCreation& creation)
	: m_Device(device)
{
	Vector<VkPipelineShaderStageCreateInfo> ShaderStageInfos;
	for (U32 i = 0; i < creation.ShaderModule.size(); i++)
	{
		const Shader* shader = creation.ShaderModule[i];
		VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = DecToVkShaderStageFlagBits(shader->GetShaderStage());
		vertShaderStageInfo.module = shader->GetShader();
		vertShaderStageInfo.pName = shader->GetEntryPoint();
	}

	popAssert(ShaderStageInfos.size());

	 VkGraphicsPipelineCreateInfo pipelineInfo = {};
	 pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	 pipelineInfo.stageCount = 2;
	 pipelineInfo.pStages = ShaderStageInfos.data();
	 pipelineInfo.pVertexInputState = &m_VertexInputeState; // TODO
	 pipelineInfo.pInputAssemblyState = &m_InputAssembly;  // TODO
	 pipelineInfo.pViewportState = &renderstate.GetViewportState();
	 pipelineInfo.pRasterizationState = &renderstate.GetRasterizer();
	 pipelineInfo.pMultisampleState = &renderstate.GetMultisampling();
	 pipelineInfo.pDepthStencilState = &renderstate.GetDepthStencil();
	 pipelineInfo.pColorBlendState = &renderstate.GetColorBlending();
	 pipelineInfo.layout = nullptr;	   // TODO
	 pipelineInfo.renderPass = nullptr;	  // TODO
	 pipelineInfo.subpass = 0;
	 pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	 popCallAPI(vkCreateGraphicsPipelines(device.GetDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_GraphicsPipeline));
}


GraphicsPipeline::~GraphicsPipeline()
{
	vkDestroyPipeline(m_Device.GetDevice(), m_GraphicsPipeline, nullptr);
}

popEnd