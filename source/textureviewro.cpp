#include "textureviewro.h"
#include "textureresource.h"
popBegin

TextureViewRO::TextureViewRO(const Device& device, const TextureResource& resource)
	: Descriptor(device)
{
	VkImageViewCreateInfo creationInfo = {};
	creationInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	creationInfo.format = resource.GetFormat();
	creationInfo.image = resource.GetImage();
	// TODO: need deffered bit?
	creationInfo.flags = VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT; 
	creationInfo.viewType = GetImageViewType(resource.GetImageType());

	// TODO from document remapping must be the identity swizzle for storage image descriptors,
	// input attachment descriptors, framebuffer attachments, 
	static VkComponentMapping conponentMaping =
	{ 
		VK_COMPONENT_SWIZZLE_IDENTITY,
		VK_COMPONENT_SWIZZLE_IDENTITY,
		VK_COMPONENT_SWIZZLE_IDENTITY,
		VK_COMPONENT_SWIZZLE_IDENTITY
	};

	creationInfo.components = conponentMaping;
	
	CreateImageView(creationInfo);
}


TextureViewRO::~TextureViewRO()
{
}

popEnd
