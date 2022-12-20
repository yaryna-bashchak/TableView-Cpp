#pragma once
#include "framework.h"
#include "Resource.h"

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

class TableViewClass
{
private:
	HWND hWndParent;
	HWND hWndTable;
public:
	void OnCreate(HWND hwndParent, HINSTANCE hInst);
	void OnSize();
	int AddColumn(int iColumn, wchar_t* text, int width);
	int AddRow(wchar_t* Text1, wchar_t* Text2, wchar_t* Text3);
};
