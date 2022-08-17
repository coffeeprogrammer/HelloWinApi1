#ifndef UNICODE
#define UNICODE
#endif

#pragma comment (lib, "comctl32")

/*
https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/winui/controls/common/vlistvw
*/

#include <windows.h>
#include <windows.h>
#include <CommCtrl.h>
//#include <iostream>
#include <wchar.h>

HINSTANCE g_hInst;
WCHAR g_szClassName[] = L"My Super Program";
HWND hListView;
HWND hMainColEdit, hCol1Edit, hCol2Edit, hCol3Edit, hCol4Edit;
HWND hButtonGo;

#define ITEM_COUNT   100000

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL InitListView(HWND hwndListView);
BOOL InsertListViewItems(HWND hwndListView);
// void ResizeListView(HWND hwndListView, HWND hwndParent);
HWND CreateListView(HINSTANCE hInstance, HWND hwndParent);
void InsertListViewItems();

#define ID_LISTVIEW  2000
#define IDI_DISK		104
#define ID_BUTTONGO		103

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	InitCommonControls();

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	//StateInfo *pState = new (std::nothrow) StateInfo;

	HWND hwnd = CreateWindowEx (
		0,
		CLASS_NAME,
		L"Learn to Program Windows",
		WS_OVERLAPPEDWINDOW,
		//CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, 720, 480,
		NULL,
		NULL,
		hInstance,
		//pState		// this is a data structure to manage application state.
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
/*
	//StateInfo *pState;
	if (uMsg == WM_CREATE)
	{
		//CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		//pState = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
		//SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
	}
	else
	{
		//pState = GetAppState(hwnd);
	}
*/
	switch (uMsg)
	{
	case WM_CREATE:
		{


			hListView = CreateListView(g_hInst, hwnd);
			InitListView(hListView);

			DWORD dwButtonStyle = WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON;

			hButtonGo =	CreateWindowEx(NULL, L"BUTTON", L"Go", dwButtonStyle,
				20, 360, 120, 60,
				hwnd, (HMENU) ID_BUTTONGO, g_hInst, NULL);

			DWORD dwEditStyle =  WS_VISIBLE | WS_CHILD | WS_BORDER;

			hMainColEdit = CreateWindowEx (NULL, L"EDIT", NULL, dwEditStyle,
				160, 360, 140, 20,
				hwnd, NULL, g_hInst, NULL);

			//CreateWindowEx (NULL, L"EDIT", NULL, dwEditStyle,
			//	160, 390, 140, 20,
			//	hwnd, NULL, g_hInst, NULL); //

			hCol1Edit = CreateWindowEx (NULL, L"EDIT", NULL, dwEditStyle,
				320, 360, 140, 20,
				hwnd, NULL, g_hInst, NULL);

			hCol2Edit = CreateWindowEx (NULL, L"EDIT", NULL, dwEditStyle,
				320, 390, 140, 20,
				hwnd, NULL, g_hInst, NULL);

			hCol3Edit = CreateWindowEx (NULL, L"EDIT", NULL, dwEditStyle,
				480, 360, 140, 20,
				hwnd, NULL, g_hInst, NULL);

			hCol4Edit = CreateWindowEx (NULL, L"EDIT", NULL, dwEditStyle,
				480, 390, 140, 20,
				hwnd, NULL, g_hInst, NULL);




		}
		
		return 0;
	case WM_NOTIFY:
		//return ListViewNotify(hwnd, lParam);
		return 0;
	case WM_SIZE:
		// ResizeListView(hListView, hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
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
		case ID_BUTTONGO:
			switch(HIWORD(wParam))
			{
			case BN_CLICKED:
				{
					//MessageBox(hwnd, L"here", L"caption", MB_OK);
					InsertListViewItems();
					break;
				}
			}
			break;
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


BOOL InitListView(HWND hwndListView)
{
	LV_COLUMN lvColumn;
	int i;
	WCHAR	szString[5][20] = {TEXT("Main Column"), TEXT("Column 1"), TEXT("Column 2"), TEXT("Column 3"), TEXT("Column 4")};

	//empty the list
	ListView_DeleteAllItems(hwndListView);

	// initialize the columns
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 120;
	for(i = 0; i < 5; i++)
	{
		lvColumn.pszText = szString[i];
		ListView_InsertColumn(hwndListView, i, &lvColumn);
	}

	InsertListViewItems(hwndListView);

	return TRUE;
}


BOOL InsertListViewItems(HWND hwndListView)
{
	// empty the list
	ListView_DeleteAllItems(hwndListView);

	// set the number of items in the list
	ListView_SetItemCount(hwndListView, ITEM_COUNT);

	return TRUE;
}



BOOL InsertListViewItems(HWND hWndListView, int cItems)
{
	LVITEM lvI;

	// initialize LVITEM members that are common to all items.
	lvI.pszText		= LPSTR_TEXTCALLBACK;	// Sends an LVN_GETDISPINFO message
	lvI.mask		= LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvI.stateMask	= 0;
	lvI.iSubItem	= 0;
	lvI.state		= 0;

	// initialize LVITEM members that are different for each item.
	for (int index = 0; index < cItems; index++)
	{
		lvI.iItem	= index;
		lvI.iImage	= index;

		// Insert items into the list.
		if (ListView_InsertItem(hWndListView, &lvI) == -1)
			return FALSE;
	}
	return TRUE;
}

void HandleWM_NOTIFY(LPARAM lParam)
{
	//NMLVDISPINFO* plvdi;

	switch (((LPNMHDR) lParam)->code)
	{

	case LVN_GETDISPINFO:
	break;
	}
	return;
}


HWND CreateListView(HINSTANCE hInstance, HWND hwndParent)
{
	DWORD	dwStyle;
	HWND	hwndListView;
	HIMAGELIST	himlSmall;
	HIMAGELIST	himlLarge;
	BOOL	bSuccess = TRUE;

	dwStyle =
		//WS_TABSTOP | 
		WS_CHILD | 
		//WS_BORDER | 
		WS_VISIBLE |
		LVS_AUTOARRANGE |
		LVS_REPORT | 
		LVS_OWNERDATA;

	hwndListView = CreateWindowEx(
				//WS_EX_CLIENTEDGE,          // ex style
				NULL,
				WC_LISTVIEW,               // class name - defined in commctrl.h
				TEXT(""),				// dummy text
				dwStyle,                   // style
				10,                         // x position
				10,                         // y position
				620,                         // width
				320,                         // height
				hwndParent,                // parent
				(HMENU)ID_LISTVIEW,        // ID
				g_hInst,                   // instance
				NULL);                     // no extra data);

	if(!hwndListView)
		return NULL;

	// ResizeListView(hwndListView, hwndParent);

	//set the image lists
	himlSmall = ImageList_Create(16, 16, ILC_COLORDDB | ILC_MASK, 1 ,0);
	himlLarge = ImageList_Create(32, 32, ILC_COLORDDB | ILC_MASK, 1, 0);

	if (himlSmall && himlLarge)
	{
		HICON hIcon;

		// set up the small image list.
		//hIcon = LoadImage(g_hInst, MAKEINTRESOURCE(IDI_DISK), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_DISK), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		ImageList_AddIcon(himlSmall, hIcon);

		// set up the large image list
		hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_DISK));
		ImageList_AddIcon(himlLarge, hIcon);

		ListView_SetImageList(hwndListView, himlSmall, LVSIL_SMALL);
		ListView_SetImageList(hwndListView, himlLarge, LVSIL_NORMAL);

	}
	return hwndListView;
}


//void ResizeListView(HWND hwndListView, HWND hwndParent)
//{
//	RECT rc;
//
//	GetClientRect(hwndParent, &rc);
//
//	MoveWindow(hwndListView,
//		rc.left,
//		rc.top,
//		rc.right - rc.left,
//		rc.bottom - rc.top,
//		TRUE);
//}


void InsertListViewItems()
{

	TCHAR colMain[128], col1[128], col2[128], col3[128], col4[128];
	GetWindowText(hMainColEdit, colMain, 128);
	GetWindowText(hCol1Edit, col1, 128);
	GetWindowText(hCol2Edit, col2, 128);
	GetWindowText(hCol3Edit, col3, 128);
	GetWindowText(hCol4Edit, col4, 128);
	//MessageBox(NULL, L"here", L"caption", MB_OK);

	LPLVITEM lvI;
	ZeroMemory(lvI, sizeof(LPLVITEM));

	lvI->pszText = colMain;

	ListView_InsertItem(hListView, lvI);


}

