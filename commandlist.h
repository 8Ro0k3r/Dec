#ifndef _DEC_COMMANDLIST_
#define _DEC_COMMANDLIST_

#include "header.h"

popBegin

class Device;

class CommandList
{
public:
	CommandList(const Device& device, U32 familyIndex);
	~CommandList();
private:
	const Device& m_Device;
	VkCommandPool m_CommandPool;
};

popEnd

#endif // _DEC_COMMANDLIST_

