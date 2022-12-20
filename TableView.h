#pragma once
#include "framework.h"
#include "Resource.h"
#include <vector>
#include <string>

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

using namespace std;

class TableViewClass
{
private:
	HWND hWndParent;
	HWND hWndTable;
	vector<vector<wstring>> table;
public:
	void OnCreate(HWND hwndParent, HINSTANCE hInst);
	void ReadFromFile();
	void PrintTable(vector<vector<wstring>> CurrentTable);
	void PrintHeadings(vector<wstring> headings);
	void PrintRow(vector<wstring> row);
	void OnSize();
	void SortColumn(LPARAM lParam);
};
