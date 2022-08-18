#ifndef UNICODE
#define UNICODE
#endif

#pragma comment (lib, "comctl32")

#include <windows.h>
#include <CommCtrl.h>
#include <wchar.h>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND DoCreateTabControl(HWND hwndParent);

HINSTANCE g_hInst;
WCHAR g_szClassName[] = L"My Super Program";
HWND g_hTab;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	//const wchar_t CLASS_NAME[] = L"Sample Window Class";

	InitCommonControls();

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = g_szClassName;

	RegisterClass(&wc);

	// Create the window.

	//StateInfo *pState = new (std::nothrow) StateInfo;

	HWND hwnd = CreateWindowEx (
		0,
		g_szClassName,
		L"My Super Program",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 720, 480,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (hwnd == NULL)
	{
		return 0;
	}
	g_hInst = hInstance;

	ShowWindow(hwnd, nCmdShow);

	// Run the message loop.

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_CREATE:
		{
			g_hTab = DoCreateTabControl(hwnd);

		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));

			EndPaint(hwnd, &ps);
		}
		break;

	case WM_COMMAND:
		break;

	case WM_CLOSE:
		if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


HWND DoCreateTabControl(HWND hwndParent)
{
	RECT rcClient;
	INITCOMMONCONTROLSEX icex;
	HWND	hTab;
	TCITEM tie;
	int i;
	WCHAR achTemp[256];

	// Initialize common controls
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_TAB_CLASSES;
	InitCommonControlsEx(&icex);

	// Get the dimensions of the parent window's client area, and
	// create a tab control child window of that size.  Note that g_hInst
	// is the global instance handle.
	GetClientRect(hwndParent, &rcClient);
	hTab = CreateWindow(WC_TABCONTROL, L"",
		WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
		0, 0, rcClient.right, rcClient.bottom,
		hwndParent, NULL, g_hInst, NULL);

	if (hTab == NULL)
	{
		return NULL;
	}


	tie.mask = TCIF_TEXT; // | TCIF_IMAGE;
	tie.iImage = -1;
	tie.pszText = L"incentive";

	//achTemp = (WCHAR) L"Chad";
	TabCtrl_InsertItem(hTab,0, &tie);
	tie.pszText = L"scrap";

	tie.




	TabCtrl_InsertItem(hTab,0, &tie);
	tie.pszText = L"hallway";
	TabCtrl_InsertItem(hTab,0, &tie);

	return hTab;
}