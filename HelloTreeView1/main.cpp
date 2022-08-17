#ifndef UNICODE
#define UNICODE
#endif

#pragma comment (lib, "comctl32")

#include <Windows.h>
#include <CommCtrl.h>


#define ID_FILE_EXIT                    40001
#define ID_FILE_OPEN                    40002
#define ID_FILE_SAVEAS                  40003
#define ID_FILE_NEW                     40004


HINSTANCE hInst ;
const wchar_t g_szClassName[] = L"myWindowClass";


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	WNDCLASSEX wc = { };
	HWND hwnd;
	MSG Msg;
	hInst = hInstance ;

	InitCommonControls();

	wc.cbSize		= sizeof(WNDCLASSEX);
	//wc.style		= 0;
	wc.lpfnWndProc	= WndProc;
	//wc.cbClsExtra	= 0;
	//wc.cbWndExtra	= 0;
	wc.hInstance	= hInstance;
	//wc.hIcon		= LoadIcon(NULL, IDI_APPLICATION);
	//wc.hCursor		= LoadCursor(NULL, IDC_ARROW);
	//wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//wc.lpszMenuName
	wc.lpszClassName	= g_szClassName;
	//wc.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		0,
		g_szClassName,
		L"My Super Program",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, 480, 320,
		NULL, NULL, hInstance, NULL);



	if(hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{


	switch(msg)
	{
	case WM_CREATE:
		{
			HWND hTreeView;
			RECT rcClient;
			GetClientRect(hwnd, &rcClient);


			hTreeView = CreateWindowEx(NULL, WC_TREEVIEW, TEXT("Tree View"),
				WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES,
				0, 0, rcClient.right, rcClient.bottom, hwnd, NULL, hInst, NULL);


		}
		break;
	case WM_SIZE:
		{

		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_COMMAND:
		//switch(LOWORD(wParam))
		//{

		//}
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}