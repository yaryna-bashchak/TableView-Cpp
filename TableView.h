#pragma once
#include "framework.h"
#include "Resource.h"
#include <vector>
#include <string>
#include <utility>

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

using namespace std;

class TableViewClass
{
private:
	HWND hWndParent;
	HWND hWndTable;
	pair<int, int> lastSortedColumnAndType = make_pair(0, 1);
	vector<vector<wstring>> table;
	vector<vector<wstring>> currentTable;
public:
	void OnCreate(HWND hwndParent, HINSTANCE hInst);
	void ReadFromFile();
	void WriteInFile();
	void PrintTable(vector<vector<wstring>> CurrentTable);
	void PrintHeadings(vector<wstring> headings);
	void PrintRow(vector<wstring> row, size_t index);
	void DeleteFullTable();
	void OnSize();
	void SortColumn(int iColumn);
};
