#include "header.h"

popBegin

class CpuFence
{
public:
	CpuFence();
	~CpuFence();
	inline const VkFence& GetFence() const { return m_Fence; }
private:
	VkFence m_Fence;
};

popEnd

