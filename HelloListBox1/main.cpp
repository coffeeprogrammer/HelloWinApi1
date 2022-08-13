#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <iostream>

struct StateInfo {
	//
};



inline StateInfo* GetAppState(HWND hwnd)
{
	LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	StateInfo *pState = reinterpret_cast<StateInfo*>(ptr);
	return pState;
}

#define IDC_LIST	1002

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
HINSTANCE hInst ;
HWND hListBox;


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
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
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
					MessageBox(hwnd, L"here", L"caption", MB_OKCANCEL);
					break;
				}

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

INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:
		{
			// Add items to list
			for (int i = 0; i < 5; i++)
			{
				int pos = (int)SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM) TEXT("Chad"));
				SendMessage(hListBox, LB_SETITEMDATA, pos, (LPARAM) i);
			}
		}
		SetFocus(hListBox);
		return TRUE;
	case LB_ADDSTRING:
		return TRUE;

	}
	//case WM_COMMAND:
	//	switch (LOWORD(wParam))
	//	{

	//	case IDOK:

	//	}
}
