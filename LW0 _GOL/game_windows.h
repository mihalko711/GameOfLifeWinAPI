#pragma once

#include "globals.h"
#include "resource.h"
#include "framework.h"

ATOM                MyRegisterClass2DGame(HINSTANCE hInstance);
ATOM                MyRegisterClass1DGame(HINSTANCE hInstance);
ATOM                RegisterChildClass1D(HINSTANCE);
ATOM                RegisterChildClass2D(HINSTANCE);

BOOL                InitInstance2D(HINSTANCE, int);
BOOL                InitInstance1D(HINSTANCE, int);
HWND                CreateChild2DWindow(HWND);
HWND                CreateChild1DWindow(HWND);

LRESULT CALLBACK    WndProc1D(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc2D(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildWndProc1D(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildWndProc2D(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK ExitConfirmDialogProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK ColorInfoDialogProc(HWND, UINT, WPARAM, LPARAM);

// диалог выбора цвета
void ShowColorDialog(HWND, COLORREF*, HBRUSH*);
void ShowColorDialogPen(HWND, COLORREF*, HPEN*);
void ShowColorInfo(HWND, HINSTANCE, const TCHAR*);