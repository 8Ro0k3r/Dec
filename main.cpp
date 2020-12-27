#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"

#define WIDTH 1080
#define HEIGHT 720

class HelloTriangleApplication
{
public:
	void run()
	{
		initWindow();
		//initialize VulkanLibary
		initVulkan();
		//loop of render
		mainLoop();

		cleanUp();
	}
private:

	void initWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void createInstance()
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "VulkanApplication";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	}

	void initVulkan()
	{
		createInstance();
	}

	void mainLoop()
	{
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	void cleanUp()
	{

	}

private:
	GLFWwindow* window;
};


int main()
{
	HelloTriangleApplication app;

	app.run();

	return -1;
}