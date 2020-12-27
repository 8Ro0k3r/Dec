#ifndef _DEC_SHADER_
#define _DEC_SHADER_

#include "header.h"

popBegin

class Device;

class Shader
{
	DEFINE_PRAVATE_MEMBER_HANDLE(VkShaderModule, Shader)
	DEFINE_PRAVATE_MEMBER_HANDLE(ShaderStage, ShaderStage)
	DEFINE_PRAVATE_CONST_MEMBER_PTR(CHAR, EntryPoint)
public:
	Shader(const Device& device, const U8* shaderCode, U32 codeSize, ShaderStage shaderStage, const CHAR* entryPoint = "main");
	~Shader();
private:
	const Device& m_Device;
};

popEnd

#endif // _DEC_SHADER_

