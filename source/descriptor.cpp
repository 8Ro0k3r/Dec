#include "descriptor.h"
#include "device.h"
popBegin

Descriptor::Descriptor(const Device& device)
	: m_Device(device)
	, m_BufferView(VK_NULL_HANDLE)
	, m_ImageView(VK_NULL_HANDLE)
{
}

Descriptor::~Descriptor()
{
	if (m_ImageView)
	{
		vkDestroyImageView(m_Device.GetDevice(), m_ImageView, nullptr);
	}
	else
	{
		vkDestroyBufferView(m_Device.GetDevice(), m_BufferView, nullptr);
	}
	
}

void Descriptor::CreateImageView(const VkImageViewCreateInfo& creationInfo)
{
	popCallAPI(vkCreateImageView(m_Device.GetDevice(), &creationInfo, nullptr, &m_ImageView));
}

void Descriptor::CreateBufferView(const VkBufferViewCreateInfo& creationInfo)
{
	popCallAPI(vkCreateBufferView(m_Device.GetDevice(), &creationInfo, nullptr, &m_BufferView));
}

VkImageViewType Descriptor::GetImageViewType(TextureType type)
{
	static const  VkImageViewType  imageViewTypeLUT[] = 
	{
		 VK_IMAGE_VIEW_TYPE_1D,
		 VK_IMAGE_VIEW_TYPE_2D,
		 VK_IMAGE_VIEW_TYPE_3D,
		 VK_IMAGE_VIEW_TYPE_CUBE,
		 VK_IMAGE_VIEW_TYPE_2D_ARRAY
	};
	popAssert((U32)type > popArraySize(imageViewTypeLUT));
	return 	imageViewTypeLUT[(U32)type];
}

popEnd