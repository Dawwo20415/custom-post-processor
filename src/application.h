#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include <stdio.h>          // printf, fprintf
#include <stdlib.h>         // abort
#include <GLFW/glfw3.h>

namespace CustomPostProcessor {
	class App {

	private:

		void ImguiSetIO();

	public:

		bool show_demo_window = true;
		ImVec4 clear_color;
		const char* window_name;

		App(const char name[]);
		void Setup();
		void Render();

	};
}