#ifndef _DEC_DESCRIPTOR_
#define _DEC_DESCRIPTOR_

#include "header.h"

popBegin
class Device;
class Descriptor
{
	DEFINE_PRAVATE_MEMBER_HANDLE(VkImageView, ImageView)
	DEFINE_PRAVATE_MEMBER_HANDLE(VkBufferView, BufferView)
public:
	Descriptor(const Device& device);
	~Descriptor();

protected:
	void CreateImageView(const VkImageViewCreateInfo& creationInfo);
	void CreateBufferView(const VkBufferViewCreateInfo& creationInfo);
	VkImageViewType GetImageViewType(TextureType type);
private:
	const Device& m_Device;
};

popEnd

#endif // _DEC_DESCRIPTOR_

