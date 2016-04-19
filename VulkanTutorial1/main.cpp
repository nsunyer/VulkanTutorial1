#include "vulkan/vulkan.h"
#include <iostream>
#include <vector>

void main()
{
//	std::cout << "Hello World!" << std::endl << VK_API_VERSION << std::endl;

	VkApplicationInfo applicationInfo;
	VkInstanceCreateInfo instanceInfo;
	VkInstance instance;

	// Filling out application description:
	// sType is mandatory
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	// pNext is mandatory
	applicationInfo.pNext = NULL;
	// The name of our application
	applicationInfo.pApplicationName = "Tutorial 1";
	// The name of the engine (e.g: Game engine name)
	applicationInfo.pEngineName = NULL;
	// The version of the engine
	applicationInfo.engineVersion = 1;
	// The version of Vulkan we're using for this application
	applicationInfo.apiVersion = VK_API_VERSION;

	// Filling out instance description:
	// sType is mandatory
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	// pNext is mandatory
	instanceInfo.pNext = NULL;
	// flags is mandatory
	instanceInfo.flags = 0;
	// The application info structure is then passed through the instance
	instanceInfo.pApplicationInfo = &applicationInfo;
	// Don't enable and layer
	instanceInfo.enabledLayerCount = 0;
	instanceInfo.ppEnabledLayerNames = NULL;
	// Don't enable any extensions
	instanceInfo.enabledExtensionCount = 0;
	instanceInfo.ppEnabledExtensionNames = NULL;

	// Now create the desired instance
	VkResult result = vkCreateInstance(&instanceInfo, NULL, &instance);
	if (result != VK_SUCCESS) {
		fprintf(stderr, "Failed to create instance: %d\n", result);
		abort();
	}

	// Query how many devices are present in the system
	uint32_t deviceCount = 0;
	result = vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
	if (result != VK_SUCCESS) {
		fprintf(stderr, "Failed to query the number of physical devices present: %d\n", result);
		abort();
	}

	// There has to be at least one device present
	if (deviceCount == 0) {
		fprintf(stderr, "Couldn't detect any device present with Vulkan support: %d\n", result);
		abort();
	}

	// Get the physical devices
	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
	result = vkEnumeratePhysicalDevices(instance, &deviceCount, &physicalDevices[0]);
	if (result != VK_SUCCESS) {
		fprintf(stderr, "Faied to enumerate physical devices present: %d\n", result);
		abort();
	}

	// Enumerate all physical devices
	VkPhysicalDeviceProperties deviceProperties;
	for (uint32_t i = 0; i < deviceCount; i++) {
		memset(&deviceProperties, 0, sizeof deviceProperties);
		vkGetPhysicalDeviceProperties(physicalDevices[i], &deviceProperties);
		printf("Driver Version: %d\n", deviceProperties.driverVersion);
		printf("Device Name:    %s\n", deviceProperties.deviceName);
		printf("Device Type:    %d\n", deviceProperties.deviceType);
		printf("API Version:    %d.%d.%d\n",
			// See note below regarding this:
			(deviceProperties.apiVersion >> 22) & 0x3FF,
			(deviceProperties.apiVersion >> 12) & 0x3FF,
			(deviceProperties.apiVersion & 0xFFF));
	}

	// Never forget to free resources
	vkDestroyInstance(instance, NULL);

}