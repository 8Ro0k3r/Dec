#include "textureresource.h"
#include "device.h"
#include "gpumemorylayout.h"
#include "gpumemoryheap.h"

popBegin

VkImageUsageFlagBits ImageUsageToVulkan(ImageBindFlage usage)
{
	static const VkImageUsageFlagBits imageUsageFlagBitsLUT[] =
	{
		VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
		VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
		VK_IMAGE_USAGE_STORAGE_BIT,
		VK_IMAGE_USAGE_SAMPLED_BIT,
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
		VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		VkImageUsageFlagBits((U32)VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
		(U32)VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
	};

	popAssert((U32)usage > popArraySize(imageUsageFlagBitsLUT));
	return imageUsageFlagBitsLUT[(U32)usage];
}

VkSampleCountFlagBits SampleToVulkan(SampleCount sampleNum)
{
	static const VkSampleCountFlagBits sampleCountFlagBitsLUT[] =
	{
		VK_SAMPLE_COUNT_1_BIT,
		VK_SAMPLE_COUNT_2_BIT,
		VK_SAMPLE_COUNT_4_BIT,
		VK_SAMPLE_COUNT_8_BIT,
		VK_SAMPLE_COUNT_16_BIT
	};

	popAssert((U32)sampleNum > popArraySize(sampleCountFlagBitsLUT));
	return sampleCountFlagBitsLUT[(U32)sampleNum];
}

VkImageLayout ImageLayoutToVulkan(ImageBindFlage usage)
{
	static const VkImageLayout imageLayoutLUT[] =
	{
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		VK_IMAGE_LAYOUT_UNDEFINED,					// TODO
		VK_IMAGE_LAYOUT_UNDEFINED,					// TODO
		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
		VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
		VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
		VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	};

	popAssert((U32)usage > popArraySize(imageLayoutLUT));
	return imageLayoutLUT[(U32)usage];
}

VkImageTiling TilingModeToVulkan(TilingMode mode)
{
	static const VkImageTiling imageTilingLUT[] =
	{
		 VK_IMAGE_TILING_LINEAR,
		  VK_IMAGE_TILING_OPTIMAL
	};

	popAssert((U32)mode > popArraySize(imageTilingLUT));
	return imageTilingLUT[(U32)mode];
}

VkImageType TextureTypeToVulkan(TextureType type)
{
	static const VkImageType imageTypeLUT[] =
	{
		 VK_IMAGE_TYPE_1D,
		 VK_IMAGE_TYPE_2D,
		 VK_IMAGE_TYPE_3D,
	};

	popAssert((U32)type > popArraySize(imageTypeLUT));
	return imageTypeLUT[(U32)type];
}


TextureResource::TextureResource(const Device& device, const GPUMemoryLayout& memoryLayout, 
	const TextureCreation& textureCreation)
	: m_Device(device)
	, m_Format(textureCreation.Format)
	, m_ImageType(textureCreation.Type)
	, m_Width(textureCreation.Width)
	, m_Height(textureCreation.Height)
	, m_Level(textureCreation.Level)
	, m_ArraySize(textureCreation.ArraySize)
{
	VkImageCreateInfo imageInfo = {};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = TextureTypeToVulkan(textureCreation.Type);
	imageInfo.extent.width = textureCreation.Width;
	imageInfo.extent.height = textureCreation.Height;
	imageInfo.extent.depth = textureCreation.Depth;
	imageInfo.mipLevels = textureCreation.Level;
	imageInfo.arrayLayers = textureCreation.ArraySize;
	imageInfo.format = textureCreation.Format;					// TODO
	imageInfo.tiling = TilingModeToVulkan(textureCreation.Tiling);
	imageInfo.initialLayout = ImageLayoutToVulkan(textureCreation.Usage);
	imageInfo.usage = ImageUsageToVulkan(textureCreation.Usage);
	imageInfo.samples = SampleToVulkan(textureCreation.Sample);
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;						// TODO

	popCallAPI(vkCreateImage(device.GetDevice(), &imageInfo, nullptr, &m_Image));

	const GPUMemoryHeap& heap = memoryLayout.GetPool();
	vkBindImageMemory(device.GetDevice(), m_Image, heap.GetMemoryHeap(), memoryLayout.GetOffset());
}


TextureResource::~TextureResource()
{
	vkDestroyImage(m_Device.GetDevice(), m_Image, nullptr);
}

popEnd
