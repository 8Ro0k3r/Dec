#include "header.h"

popBegin

class Device;

class CommandAllocator
{
public:
	CommandAllocator(const Device& device, QueueType type);
	~CommandAllocator();
	inline const VkCommandPool& GetCommandPool() const { return m_CommandPool; }
private:
	const Device& m_Device;
	VkCommandPool m_CommandPool;
};

popEnd
