#if 1

#include "vulkandefine.h"
#include <GLFW/glfw3.h>

static GLFWwindow* window = nullptr;
#define WIDTH pop1080pWidth
#define HEIGHT pop1080pHeight

void initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

static void GetVulkanExtensions(std::vector<const CHAR*>& extensions)
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	for (uint32_t i = 0; i < glfwExtensionCount; i++)
	{
		extensions.push_back(glfwExtensions[i]);
	}
}

static VkResult CreateVulkanSurface(VkInstance instance, VkSurfaceKHR& surface)
{
	return glfwCreateWindowSurface(instance, window, nullptr, &surface);
}

void TestClearColor(const Dec::Device& device)
{
	Dec::SwapChain swapchain(device);
	Dec::Queue queue(device, Dec::QueueType::QUEUE_TYPE_GRAPHICS, 0);
	Dec::CommandAllocator commandAllocator(device, Dec::QueueType::QUEUE_TYPE_GRAPHICS);
	Dec::GraphicsCommandList commandlist(device, commandAllocator);
	Dec::GpuFence gpuFence(device);

	while (true)
	{
		swapchain.Acquire();
		commandlist.Begin();

		commandlist.End();


		/*queue.Submit();*/
		swapchain.Present(queue);
	}
}

int main()
{
	initWindow();

	BOOL isValidateLayer = false;
#if defined(Debug)
	isValidateLayer = true;
#endif

	Dec::Instance instance(GetVulkanExtensions, CreateVulkanSurface, isValidateLayer);
	Dec::Device device(instance);
	
	TestClearColor(device);
	return 0;
}

#endif