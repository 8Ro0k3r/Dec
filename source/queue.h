#include "header.h"

popBegin

class Device;

class Queue
{
public:
	Queue(const Device& device, QueueType type, U32 index = 0);
	~Queue();
	void Submit(const SubmitInfo& submitInfo);
	inline const VkQueue GetQueue() const { return m_Queue; }
private:
	const Device& m_Device;
	VkQueue m_Queue;
};

popEnd