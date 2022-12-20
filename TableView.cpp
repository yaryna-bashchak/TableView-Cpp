#include "TableView.h"
#include <fstream>
#include <codecvt>

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
    table = {};
    ListView_DeleteAllItems(hWndTable);

    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> convert;

    ifstream file;
    file.open("Table.txt");
    
    if (file.is_open())
    {
        while (file)
        {
            string line;
            getline(file, line);
        }
        file.close();
    }

    currentTable = table;
    PrintTable(currentTable);
}

void TableViewClass::WriteInFile()
{
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> convert;

    fstream file;
    file.open("Table.txt");
    for (size_t i = 0; i < currentTable.size(); i++)
    {
        //auto str = line.c_str();
        WCHAR line[256];
        vector<wstring> row = currentTable[i];

        swprintf_s(line, 256, L"%s", row[0].c_str());
        for (int j = 1; j < currentTable[i].size(); j++)
            swprintf_s(line, 256, L"%s\t%s", line, row[i].c_str());

        file << convert.to_bytes(line) << endl;
    }
    file.close();
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
        lvc.pszText = (LPWSTR)headings[i].c_str();
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
