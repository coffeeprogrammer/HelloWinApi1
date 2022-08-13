#ifndef UNICODE
#define UNICODE
#endif

     #pragma comment (lib, "comctl32")

#include <windows.h>
//#include <Shlwapi.h>
#include <CommCtrl.h>
#include <iostream>
//#include <string.h>
#include <wchar.h>


struct StateInfo {
	//
};



inline StateInfo* GetAppState(HWND hwnd)
{
	LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	StateInfo *pState = reinterpret_cast<StateInfo*>(ptr);
	return pState;
}

#define IDC_LIST		1002
#define IDC_EDIT		1001
#define IDC_BUTTON		1003
#define IDC_LISTVIEW	1004


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
HWND CreateListView (HWND hwndParent);
HINSTANCE hInst ;
HWND hListBox;
HWND hEdit;
HWND hButton;
HWND hListView;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	const wchar_t CLASS_NAME[] = L"Sample Window Class";
	hInst = hInstance ;
	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	StateInfo *pState = new (std::nothrow) StateInfo;

	// Create the window.

	HWND hwnd = CreateWindowEx (
		0,
		CLASS_NAME,
		L"Learn to Program Windows",
		WS_OVERLAPPEDWINDOW,
		//CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		160, 160, 600, 400,
		NULL,
		NULL,
		hInstance,
		pState		// this is a data structure to manage application state.
		);

	if (hwnd == NULL)
	{
		return 0;
	}

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
	StateInfo *pState;
	if (uMsg == WM_CREATE)
	{
		CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pState = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
	}
	else
	{
		pState = GetAppState(hwnd);
	}

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CREATE:

		hListBox = CreateWindow(L"LISTBOX", NULL,
			LBS_MULTICOLUMN | LBS_HASSTRINGS | LBS_NOTIFY |
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL,		
			10, 10, 200, 800, hwnd, (HMENU) IDC_LIST, hInst, NULL);

		//hEdit = CreateWindow (L"EDIT", NULL,
		//	WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
		//	WS_BORDER | ES_LEFT | ES_MULTILINE |
		//	ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		//	220, 20, 300, 400, hwnd, (HMENU) IDC_EDIT,
		//	hInst, NULL) ;

		hEdit = CreateWindow (L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | 
			WS_BORDER | ES_LEFT,
			210, 20, 140, 20, hwnd, (HMENU) IDC_EDIT,
			hInst, NULL) ;

		hButton = CreateWindow (L"BUTTON", L"Go",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			210, 50, 140, 40, hwnd, (HMENU) IDC_BUTTON,
			hInst, NULL);

		hListView = CreateListView(hwnd);

		//SetWindowLongPtr(hListBox, GWL_WNDPROC, (LONG_PTR) ListBoxExampleProc);
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM) L"first");
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM) L"second");
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM) L"third");
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));

			EndPaint(hwnd, &ps);
		}
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_LIST:
			switch(HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				{
					MessageBox(hwnd, L"here", L"caption", MB_OK);
					break;
				}
			}
			break;
		case IDC_EDIT:
			//MessageBox(hwnd, L"edit box", L"caption", MB_OK);
			switch(HIWORD(wParam))
			{
			case EN_KILLFOCUS:
				WCHAR text[256] = {0};
				GetWindowText(hEdit, text, 256);
				MessageBox(hwnd, text, L"caption", MB_OK);
				break;
			}
			break;
		case IDC_BUTTON:
			//MessageBox(hwnd, L"button", L"caption", MB_OK);
			switch(HIWORD(wParam))
			{
			case BN_CLICKED:
				{
					HDC hdc = GetDC(hwnd);

					SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM) L"clicked button");
					LPCWSTR text = L"You must be smart, you know how to click a button";

					BOOL v = TextOut(hdc, 300, 300, text, wcslen(text));
					ReleaseDC(hwnd, hdc);
				}
				break;
			}

			break;
		}

		return 0;
	case WM_CLOSE:
		if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND CreateListView (HWND hwndParent) 
{
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	RECT rcClient;                       // The parent window's client area.

	GetClientRect (hwndParent, &rcClient); 

	// Create the list-view window in report view with label editing enabled.
/*	HWND hWndListView = CreateWindow(WC_LISTVIEW, 
		L"",
		WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
		0, 0,
		rcClient.right - rcClient.left,
		rcClient.bottom - rcClient.top,
		hwndParent,
		(HMENU)IDM_CODE_SAMPLES,
		g_hInst,
		NULL);*/ 


	HWND hWndListView = CreateWindow(WC_LISTVIEW, 
		L"",
		WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
		360, 20,
		rcClient.right - 100,
		rcClient.bottom - 100,
		hwndParent,
		(HMENU)IDC_LISTVIEW,
		hInst,
		NULL); 

	return (hWndListView);

}
