#pragma once

#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_dx9.h"
#include <d3d9.h>
#include <tchar.h>
#include "psapi.h"

class ImGuiHeaderClass {
public:
	void SetImGuiLayout(ImGuiStyle& style);
	void RenderImguiMenu();
};

extern ImGuiHeaderClass CImGuiHeader;

