#pragma once
#include "vulkan/vulkan.h"
#include <iostream>
#include <vector>

class Renderer
{
public:
	Renderer();
	~Renderer();

private:
	void _InitInstance();
	void _DeInitInstance();

	void _InitDevice();
	void _DeInitDevice();

	VkInstance instance;
};

