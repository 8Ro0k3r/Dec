#ifndef _DEC_DEVICE_
#define _DEC_DEVICE_

#include "header.h"

popBegin

class Instance;

class Device
{
public:
	Device(const Instance& instance);
	~Device();
	inline const VkDevice GetDevice() const { return m_Device; }
	inline const Instance& GetInstance() const { return m_Instance; }

private:
	const Instance& m_Instance;
	VkDevice m_Device;
};

popEnd

#endif // _DEC_DEVICE_