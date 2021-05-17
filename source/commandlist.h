#ifndef _DEC_COMMANDLIST_
#define _DEC_COMMANDLIST_

#include "header.h"

popBegin

class Device;
class CommandAllocator;
class CommandList
{
public:
	CommandList(const Device& device, const CommandAllocator& commandAllcator);
	~CommandList();
	inline const VkCommandBuffer& GetCommandBuffer() const { return m_CommandBuffer; }
	void Begin();
	void End();
private:
	void Free();
	const Device& m_Device;
	VkCommandPool m_PoolRef;
	VkCommandBuffer m_CommandBuffer;
};

popEnd

#endif // _DEC_COMMANDLIST_

