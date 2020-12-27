#ifndef _DEC_INSTANCE_
#define _DEC_INSTANCE_

#include "header.h"
#include "utils.h"

popBegin

class Instance
{
public:
	Instance(funcVulkanExtensions& vulkanExtension, BOOL needValidateLayer);	
	~Instance();
	inline const VkInstance GetInstance() const { return m_Instance; }
	inline const VkPhysicalDevice GetPhysicalDevice() const { return m_PhysicalDevice; }
	inline const VkSurfaceKHR GetWindowSurface() const { return m_Surface; }
	inline const Vector<const CHAR*>& GetExtensionNames() const { return m_RequireVulkanExtensionNames; }
	inline const Vector<const CHAR*>& GetValidateLayerNames() const { return m_ValidateLayerNames; }
	inline const Vector<VkDeviceQueueCreateInfo>& GetDeviceQueueCreateInfos() const { return m_QueueCreateInfos; }
	inline const VkPhysicalDeviceFeatures& GetPhysicalDeviceFeatures() const { return m_DeviceFeatures; }
	S32 GetGraphicsFamilyIndex() const;
	S32 GetComputeFamilyIndex() const;
	S32 GetPresentFamilyIndex() const;

private:
	void CreateInstance(BOOL needValidateLayer);
	void CreatePhysicalDevice();
	void CreateQueueCreateInfo();
	void CheckRequiredExtension();
	BOOL FoundRequiredLayer();

	VkInstance m_Instance;
	VkSurfaceKHR m_Surface;
	VkPhysicalDevice m_PhysicalDevice;
	funcVulkanExtensions m_FuncVulkanExtension;
	Vector<const CHAR*> m_RequireVulkanExtensionNames;
	Vector<const CHAR*> m_ValidateLayerNames;
	Vector<VkDeviceQueueCreateInfo> m_QueueCreateInfos;
	VkPhysicalDeviceFeatures m_DeviceFeatures;
	QueueFamilyIndices m_QueueFamilyIndices;
};

popEnd

#endif // _DEC_INSTANCE_
