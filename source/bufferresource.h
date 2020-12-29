#ifndef _DEC_BUFFERRESOURCE_
#define _DEC_BUFFERRESOURCE_

#include "header.h"

popBegin

class Device;
class GPUMemoryLayout;

class BufferResource
{
	DEFINE_PRAVATE_MEMBER_HANDLE(VkBuffer, Buffer)
public:
	BufferResource(const Device& device, const GPUMemoryLayout& memoryLayout, BufferUsage usage);
	~BufferResource();
	void* Map();
	void Unmap();

private:
	const Device& m_Device;
	void* m_MapPtr;
};

popEnd

#endif //  _DEC_BUFFERRESOURCE_

