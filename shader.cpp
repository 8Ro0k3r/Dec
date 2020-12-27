#include "Shader.h"
#include "device.h"
popBegin

Shader::Shader(const Device& device, const U8* shaderCode, U32 codeSize, ShaderStage shaderStage, const CHAR* entryPoint)
	: m_Device(device)
	, m_EntryPoint(entryPoint)
	, m_ShaderStage(shaderStage)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = codeSize;
	createInfo.pCode = reinterpret_cast<const U32*>(shaderCode);

	popCallAPI(vkCreateShaderModule(device.GetDevice(), &createInfo, nullptr, &m_Shader));
}


Shader::~Shader()
{
	vkDestroyShaderModule(m_Device.GetDevice(), m_Shader, nullptr);
}

popEnd
