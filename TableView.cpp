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
        WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
        0, 0,
        rcClient.right - rcClient.left,
        rcClient.bottom - rcClient.top,
        hwndParent,
        (HMENU)IDC_LISTVIEW,
        hInst,
        NULL);
}

void TableViewClass::ReadFromFile()
{
    // vector to test

    for (size_t r = 0; r < 3; r++)
    {
        vector<wstring> row;
        for (size_t c = 0; c < 4; c++)
        {
            row.push_back(L"hello");
        }
        table.push_back(row);
    }

    currentTable = table;
    PrintTable(currentTable);
}


void TableViewClass::PrintTable(vector<vector<wstring>> CurrentTable)
{
    PrintHeadings(CurrentTable[0]);
    for (size_t i = 1; i < CurrentTable.size(); i++)
    {
        PrintRow(CurrentTable[i]);
    }
}

void TableViewClass::PrintHeadings(vector<wstring> headings)
{
    int width = 200;

    for (size_t i = 0; i < headings.size(); i++)
    {
        LVCOLUMN lvc;

        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvc.fmt = LVCFMT_LEFT;
        lvc.cx = width;
        lvc.pszText = (LPWSTR)headings[0].c_str();
        lvc.iSubItem = i;
        ListView_InsertColumn(hWndTable, i, &lvc);
    }
}

void TableViewClass::PrintRow(vector<wstring> row)
{
    LVITEM lvi = { 0 };
    int Ret;

    lvi.mask = LVIF_TEXT;
    lvi.pszText = (LPWSTR)row[0].c_str();
    Ret = ListView_InsertItem(hWndTable, &lvi);
    if (Ret >= 0) {
        for (size_t i = 1; i < row.size(); i++)
        {
            ListView_SetItemText(hWndTable, Ret, i, (LPWSTR)row[i].c_str());
        }
    }
}

void TableViewClass::SortColumn(LPARAM lParam)
{
    
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
