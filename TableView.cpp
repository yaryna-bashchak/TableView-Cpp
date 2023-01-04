#include "TableView.h"
#include <fstream>
#include <codecvt>
#include <algorithm>

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
        WS_VISIBLE | WS_CHILD | LVS_REPORT,
        0, 0,
        rcClient.right - rcClient.left,
        rcClient.bottom - rcClient.top,
        hwndParent,
        (HMENU)IDC_LISTVIEW,
        hInst,
        NULL);
}

void TableViewClass::ReadFromFile(wstring FileName)
{
    if (FileName != L"")
    {
        DeleteFullTable();
        table.clear();

        wstring_convert<codecvt_utf8<wchar_t>, wchar_t> convert;

        ifstream file;
        file.open(FileName);
        fileName = FileName;
    
        if (file.is_open())
        {
            int i = 0;
            while (file)
            {
                string line;  
                getline(file, line);

                if (line != "")
                {
                    vector<wstring> row;
                    string cell;
                    size_t pos = 0;
                    string d = "\t";

                    if (i != 0) row.push_back(to_wstring(i));
                    else row.push_back(L"№");

                    while ((pos = line.find(d)) != string::npos)
                    {
                        cell = line.substr(0, pos);
                        line.erase(0, pos + d.length());
                        row.push_back(convert.from_bytes(cell));
                    }
                    row.push_back(convert.from_bytes(line));

                    table.push_back(row);
                    i++;
                }
            }
            file.close();
            SetWindowText(hWndParent, (LPCWSTR)fileName.c_str());
        }

        currentTable = table;
        PrintTable(currentTable);
    }
}

void TableViewClass::WriteInFile(wstring FileName)
{
    if (FileName != L"" && !table.empty())
    {
        wstring_convert<codecvt_utf8<wchar_t>, wchar_t> convert;
        currentTable[0] = table[0];

        ofstream file;
        if (FileName == L"current") file.open(fileName);
        else
        {
            fileName = FileName;
            file.open(FileName);
        }

        if (file.is_open())
        {
            for (size_t i = 0; i < currentTable.size(); i++)
            {
                WCHAR line[256];
                vector<wstring> row = currentTable[i];

                row.erase(row.cbegin());

                swprintf_s(line, 256, L"%s", row[0].c_str());
                for (int j = 1; j < row.size(); j++)
                    swprintf_s(line, 256, L"%s\t%s", line, row[j].c_str());

                file << convert.to_bytes(line) << endl;
            }
            SetWindowText(hWndParent, (LPCWSTR)fileName.c_str());
            file.close();
        }
        
    }
}

void TableViewClass::PrintTable(vector<vector<wstring>> CurrentTable)
{
    DeleteFullTable();

    PrintHeadings(CurrentTable[0]);
    for (size_t i = 1; i < CurrentTable.size(); i++)
    {
        PrintRow(CurrentTable[i], i - 1);
    }
}

void TableViewClass::PrintHeadings(vector<wstring> headings)
{
    for (size_t i = 0; i < headings.size(); i++)
    {
        LVCOLUMN lvc;

        int width = maxWidth(i);

        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvc.fmt = LVCFMT_LEFT;
        lvc.cx = width;
        lvc.pszText = (LPWSTR)headings[i].c_str();
        lvc.iSubItem = i;
        ListView_InsertColumn(hWndTable, i, &lvc);
    }
}

void TableViewClass::PrintRow(vector<wstring> row, size_t index)
{
    LVITEM lvi = { 0 };
    int Ret;

    lvi.mask = LVIF_TEXT;
    lvi.pszText = (LPWSTR)row[0].c_str();
    lvi.iItem = index;
    Ret = ListView_InsertItem(hWndTable, &lvi);
    if (Ret >= 0) {
        for (size_t i = 1; i < row.size(); i++)
        {
            ListView_SetItemText(hWndTable, Ret, i, (LPWSTR)row[i].c_str());
        }
    }
}

void TableViewClass::DeleteFullTable()
{
    for (size_t i = currentTable.size(); i > 0; i--)
    {
        ListView_DeleteColumn(hWndTable, i - 1);
    }
    ListView_DeleteAllItems(hWndTable);
}

void TableViewClass::SortColumn(int iColumn)
{
    // changing data of lastSortedColumnAndType

    if (lastSortedColumnAndType.first == iColumn)
    {
        lastSortedColumnAndType.second = (lastSortedColumnAndType.second + 1) % 3;
        if (lastSortedColumnAndType.second == 0) lastSortedColumnAndType = make_pair(0, 1);
    }
    else
    {
        lastSortedColumnAndType = make_pair(iColumn, 1);
    }
    
    // sorting

    if (lastSortedColumnAndType.second == 0 || lastSortedColumnAndType.first == 0)
    {
        currentTable = table;
        if (lastSortedColumnAndType.second == 2)
            reverse(currentTable.begin() + 1, currentTable.end());
    }
    else
        sort(currentTable.begin() + 1, currentTable.end(),
            [&](const vector<wstring>& a, const vector<wstring>& b)
            {
                if (lastSortedColumnAndType.second == 1)
                    return a[iColumn] < b[iColumn];
                else
                    return a[iColumn] > b[iColumn];
            });

    // add symbol (↗️ or ↘️) about sort type

    currentTable[0] = table[0];
    wstring sortType = L"";
    if (lastSortedColumnAndType.second == 1) sortType = L"↗️";
    else if (lastSortedColumnAndType.second == 2) sortType = L"↘️";
    currentTable[0][lastSortedColumnAndType.first] += sortType;

    // printing new current table

    PrintTable(currentTable);
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

int TableViewClass::maxWidth(int iColumn)
{
    int MaxLength = currentTable[0][iColumn].length();
    for (size_t i = 1; i < currentTable.size(); i++)
    {
        if (currentTable[i][iColumn].length() > MaxLength)
            MaxLength = currentTable[i][iColumn].length();
    }

    int MaxWidth;
    if (MaxLength < 10) MaxWidth = MaxLength * 12;
    else MaxWidth = MaxLength * 7;

    return MaxWidth;
}