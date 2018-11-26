#include "CurlClass.h"
#include "ImGuiHeader.h"
#include "SGlobal.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")

void StartThreads();

static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern void eraseAllSubStr(std::string & mainStr, const std::string & toErase);
WNDCLASS CreateWindowClass(HINSTANCE hInstance);







/*int main() {
std::vector<std::thread> threads;

std::cout << "increase global counter with 10 threads...\n";
for (int i = 1; i <= 200; ++i)
threads.push_back(std::thread(ThreadExecuteCurl));
ShouldStart = TRUE;

threads[1].join();

}*/

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

WNDCLASS CreateWindowClass(HINSTANCE hInstance) {
	WNDCLASS wcWndC = { 0 };
	wcWndC.style = CS_HREDRAW | CS_VREDRAW;
	wcWndC.lpfnWndProc = (WNDPROC)WndProc;
	wcWndC.hInstance = hInstance;
	wcWndC.hCursor = LoadCursor(NULL, IDC_ARROW); // <-- Cursor
	wcWndC.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
	wcWndC.lpszClassName = "Sebastian";
	wcWndC.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
	return wcWndC;

}

void eraseAllSubStr(std::string & mainStr, const std::string & toErase)
{
	size_t pos = std::string::npos;

	// Search for the substring in string in a loop untill nothing is found
	while ((pos = mainStr.find(toErase)) != std::string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
}




int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wcWnd = CreateWindowClass(hInstance);
	if (!RegisterClass(&wcWnd)) // Improve MessageBox
	{
		MessageBox(NULL,
			"Call to RegisterClass failed!",
			"Sebastian Error",
			MB_OK);

		return TRUE;
	}

	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect); // разрешение экрана
	int x = screen_rect.right / 2 - 200;
	int y = screen_rect.bottom / 2 - 200;

	HWND hWnd = CreateWindow("Sebastian", "Sebastian", WS_POPUP, x, y, 400, 400, NULL, NULL, hInstance, NULL);

	// Initialize Direct3D
	LPDIRECT3D9 pD3D;
	if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		UnregisterClass(_T("Sebastian"), hInstance);
		return 0;
	}
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; // Present with vsync
															//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // Present without vsync, maximum unthrottled framerate

															// Create the D3DDevice
	if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
	{
		pD3D->Release();
		UnregisterClass(_T("Sebastian"), hInstance);
		return 0;
	}

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplDX9_Init(hWnd, g_pd3dDevice);

	ImGuiStyle& style = ImGui::GetStyle();
	ImFont* font = ImGui::GetFont();

	CImGuiHeader.SetImGuiLayout(style);
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (msg.message != WM_QUIT)
	{
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		ImGui_ImplDX9_NewFrame();

		DWORD dwFlag = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

		static bool open = true;

		if (!open)
			ExitProcess(0);

		ImGui::Begin("Sebastian", &open, ImVec2(400, 400), 1.0f, dwFlag);
		{
			CImGuiHeader.RenderImguiMenu();
		}
		ImGui::End();

		ImGui::EndFrame();
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*255.0f), (int)(clear_color.y*255.0f), (int)(clear_color.z*255.0f), (int)(clear_color.w*255.0f));
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}
		HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

		// Handle loss of D3D9 device
		if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			g_pd3dDevice->Reset(&g_d3dpp);
			ImGui_ImplDX9_CreateDeviceObjects();
		}


	}
	

	ImGui_ImplDX9_Shutdown();
	ImGui::DestroyContext();

	if (g_pd3dDevice) g_pd3dDevice->Release();
	if (pD3D) pD3D->Release();
	DestroyWindow(hWnd);
	UnregisterClass(_T("Sebastian"), hInstance);

	return 0;

}




