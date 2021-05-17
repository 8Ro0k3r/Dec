#include "header.h"

popBegin

class Device;

class GpuFence
{
public:
	GpuFence(const Device& device);
	~GpuFence();
	inline const VkSemaphore& GetGpuFence() const { return m_Sync; }
private:
	VkSemaphore m_Sync;
	const Device& m_Device;
};

popEnd

