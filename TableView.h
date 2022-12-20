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
	vector<vector<string>> table{};
public:
	void OnCreate(HWND hwndParent, HINSTANCE hInst);
	void ReadFromFile();
	void OnSize();
	int AddColumn(int iColumn, wchar_t* text, int width);
	int AddRow(wchar_t* Text1, wchar_t* Text2, wchar_t* Text3);
};
