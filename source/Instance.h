#ifndef _DEC_INSTANCE_
#define _DEC_INSTANCE_

#include "header.h"
#include "utils.h"

popBegin

class Instance
{
public:
	Instance(funcVulkanExtensions extensionFunc, funVulkanCreateSurface surfaceFunc, BOOL enableValidateLayer = false);
	~Instance();
	inline const VkInstance GetInstance() const { return m_Instance; }
	inline const VkPhysicalDevice GetPhysicalDevice() const { return m_PhysicalDevice; }
	inline const VkSurfaceKHR GetWindowSurface() const { return m_Surface; }
	inline const Vector<const CHAR*>& GetExtensionNames() const { return m_RequireVulkanExtensionNames; }
	inline const Vector<VkDeviceQueueCreateInfo>& GetDeviceQueueCreateInfos() const { return m_QueueCreateInfos; }
	inline const VkPhysicalDeviceFeatures& GetPhysicalDeviceFeatures() const { return m_DeviceFeatures; }
	inline U32 GetQueueFamilyIndex(QueueType type) const 
	{ 
		return type == QueueType::QUEUE_TYPE_GRAPHICS ? m_QueueFamilyIndices.GraphicsFamily.value() :
			type == QueueType::QUEUE_TYPE_COMPUTE ? m_QueueFamilyIndices.ComputeFamily.value() :
			m_QueueFamilyIndices.CopyFamily.value();
	}
	inline BOOL IsEnableValidateLayer() const { return m_EnableValidateLayer; }
private:
	void InitFunc();
	void CreateInstance();
	void CreatePhysicalDevice();
	void CreateSurface();
	void CreateQueueCreateInfo();
	void CheckRequiredExtension();
	BOOL FoundRequiredLayer();

	VkInstance m_Instance;
	VkSurfaceKHR m_Surface;
	VkPhysicalDevice m_PhysicalDevice;
	funcVulkanExtensions m_FuncVulkanExtension;
	funVulkanCreateSurface m_FuncVulkanCreateSurface;
	VkDebugUtilsMessengerCreateInfoEXT m_DebugUtilsMessengerCreateInfoEXT;
	VkDebugUtilsMessengerEXT m_DebugMessenger;
	PFN_vkCreateDebugUtilsMessengerEXT m_FuncCreateDebugUtilsMessengerEXT;
	PFN_vkDestroyDebugUtilsMessengerEXT m_FuncDestroyDebugUtilsMessengerEXT;
	Vector<const CHAR*> m_RequireVulkanExtensionNames;
	Vector<VkDeviceQueueCreateInfo> m_QueueCreateInfos;
	VkPhysicalDeviceFeatures m_DeviceFeatures;
	QueueFamilyIndices m_QueueFamilyIndices;
	BOOL m_EnableValidateLayer;
};

popEnd

#endif // _DEC_INSTANCE_
