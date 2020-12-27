#ifndef _DEC_GRAPHICSPIPELINE_
#define _DEC_GRAPHICSPIPELINE_

#include "header.h"

popBegin

class Device;
class RenderState;
class Shader;

struct GraphicsPipelineStateCreation
{
	PrimitiveTopology Topology;
	Vector<const Shader*> ShaderModule;
};

class GraphicsPipeline
{
	DEFINE_PRAVATE_MEMBER_HANDLE(VkPipeline, GraphicsPipeline)
public:
	GraphicsPipeline(const Device& device, const RenderState& renderstate, const GraphicsPipelineStateCreation& creation);
	~GraphicsPipeline();
private:
	VkPipelineVertexInputStateCreateInfo m_VertexInputeState;
	VkPipelineInputAssemblyStateCreateInfo m_InputAssembly;
	VkPipelineShaderStageCreateInfo m_ShaderStageInfo[ShaderStage::SHADER_COUNT]; \
    const Device& m_Device;
};

popEnd

#endif // _DEC_GRAPHICSPIPELINE_ 