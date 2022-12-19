// main.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "main.h"
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hwndList;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int CreateColumn(HWND hwndLV, int iCol, wchar_t* Text, int iBreite);
int CreateItem(HWND hwndList, wchar_t* Text);
int Create2ColItem(HWND hwndList, wchar_t* Text1, wchar_t* Text2, wchar_t* Text3);
HWND CreateListView(HWND hwndParent);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    InitCommonControls();

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MAIN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAIN));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MAIN);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle,
       WS_OVERLAPPEDWINDOW,
       300, 100, 800, 600,
       nullptr, nullptr, hInstance, nullptr);

   /*HWND hWnd = CreateWindow(WC_LISTVIEW, szTitle,
       WS_VISIBLE | WS_BORDER | WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
       10, 10, 300, 100,
       nullptr, (HMENU)IDC_MAIN, hInst, 0);*/

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        hwndList = CreateListView(hWnd);
        CreateColumn(hwndList, 0, (wchar_t*)L"first", 100);
        CreateColumn(hwndList, 1, (wchar_t*)L"second", 200);
        CreateColumn(hwndList, 2, (wchar_t*)L"third", 300);
        CreateItem(hwndList, (wchar_t*)L"abc");
        Create2ColItem(hwndList, (wchar_t*)L"b", (wchar_t*)L"name", (wchar_t*)L"coords");
        CreateItem(hwndList, (wchar_t*)L"aa\tb\tc");
        Create2ColItem(hwndList, (wchar_t*)L"c", (wchar_t*)L"name", (wchar_t*)L"coords");
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int CreateColumn(HWND hwndLV, int iCol, wchar_t* Text, int iBreite)
{
    LVCOLUMN lvc;

    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.fmt = LVCFMT_LEFT;
    lvc.cx = iBreite;
    lvc.pszText = (LPWSTR)Text;
    lvc.iSubItem = iCol;
    return ListView_InsertColumn(hwndLV, iCol, &lvc);
}

int CreateItem(HWND hwndList, wchar_t* Text)
{
    LVITEM lvi = { 0 };

    lvi.mask = LVIF_TEXT;
    lvi.pszText = Text;
    return ListView_InsertItem(hwndList, &lvi);
}

int Create2ColItem(HWND hwndList, wchar_t* Text1, wchar_t* Text2, wchar_t* Text3)
{
    LVITEM lvi = { 0 };
    int Ret;

    // Ініціалізація членів LVITEM, які є спільними для всіх елементів. 
    lvi.mask = LVIF_TEXT;
    lvi.pszText = Text1;
    Ret = ListView_InsertItem(hwndList, &lvi);
    if (Ret >= 0) {
        ListView_SetItemText(hwndList, Ret, 1, Text2);
        ListView_SetItemText(hwndList, Ret, 2, Text3);
    }
    return Ret;
}

HWND CreateListView(HWND hwndParent)
{
    INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    RECT rcClient;                       // The parent window's client area.

    GetClientRect(hwndParent, &rcClient);

    // Create the list-view window in report view with label editing enabled.
    HWND hWndListView = CreateWindow(WC_LISTVIEW,
        L"test",
        WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_EDITLABELS | LVS_SORTASCENDING,
        0, 0,
        rcClient.right - rcClient.left,
        rcClient.bottom - rcClient.top,
        hwndParent,
        (HMENU)IDC_LISTVIEW,
        hInst,
        NULL);

    return (hWndListView);
}