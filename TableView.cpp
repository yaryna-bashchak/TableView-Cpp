#include "TableView.h"

void TableViewClass::OnCreate(HWND hwndParent, HINSTANCE hInst)
{
    hWndParent = hwndParent;

    INITCOMMONCONTROLSEX icex;
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    RECT rcClient;

    GetClientRect(hwndParent, &rcClient);

    hWndTable = CreateWindow(WC_LISTVIEW,
        L"table",
        WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_EDITLABELS | LVS_SORTASCENDING,
        0, 0,
        rcClient.right - rcClient.left,
        rcClient.bottom - rcClient.top,
        hwndParent,
        (HMENU)IDC_LISTVIEW,
        hInst,
        NULL);

    ReadFromFile();
}

void TableViewClass::ReadFromFile()
{
    // vector to test
    for (size_t r = 0; r < 3; r++)
    {
        vector<string> row;
        for (size_t c = 0; c < 4; c++)
        {
            row.push_back("1");
        }
        table.push_back(row);
    }
}

void TableViewClass::OnSize()
{
    RECT rc;
    if (hWndTable)
    {
        GetClientRect(hWndParent, &rc);
        MoveWindow(hWndTable, 0, 0, rc.right - rc.left, rc.bottom - rc.top, FALSE);
    }
}

int TableViewClass::AddColumn(int iColumn, wchar_t* text, int width)
{
    LVCOLUMN lvc;

    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.fmt = LVCFMT_LEFT;
    lvc.cx = width;
    lvc.pszText = (LPWSTR)text;
    lvc.iSubItem = iColumn;
    return ListView_InsertColumn(hWndTable, iColumn, &lvc);
}

int TableViewClass::AddRow(wchar_t* Text1, wchar_t* Text2, wchar_t* Text3)
{
    LVITEM lvi = { 0 };
    int Ret;

    lvi.mask = LVIF_TEXT;
    lvi.pszText = Text1;
    Ret = ListView_InsertItem(hWndTable, &lvi);
    if (Ret >= 0) {
        ListView_SetItemText(hWndTable, Ret, 1, Text2);
        ListView_SetItemText(hWndTable, Ret, 2, Text3);
    }
    return Ret;
}