#pragma once

#include <windows.h>
#include <vector>

#define MAX_LOADSTRING 100
#define GRID_SIZE 50 // ������ ����
#define CELL_SIZE 10 // ������ ������

extern INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// ���������� ����������:
extern HINSTANCE hInst;                                // ������� ���������
extern WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
extern WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
extern WCHAR szWindowClass1[MAX_LOADSTRING];           // ��� ������ �������� ����

// ����� �������� ����
extern int able_to_create_win2d;
extern int able_to_create_win1d;

// �������� HWND
extern HWND hGameWnd1D, hGameWnd2D, hChild1D, hChild2D;

// ������� ���������
extern int scrollPosX1D, scrollPosY1D;
extern int scrollPosX2D, scrollPosY2D;

// ������� �����
extern int field1DWidth, field1DHeight;
extern int field2DWidth, field2DHeight;

// ������� �������� ����
extern int ChildWidth1D, ChildHeight1D;
extern int ChildWidth2D, ChildHeight2D;

// �������� ���������
extern int field1D_vert_pages, field1D_horz_pages;
extern int field2D_vert_pages, field2D_horz_pages;

// ���������� ������
extern int cellCount1D, cellCount2D;

//������ ������
extern int cellSize2D, cellSize1D;

// ������������� ��������
extern int scaled1DWidth, scaled1DHeight;
extern int scaled2DWidth, scaled2DHeight;

extern int scaledChild1DWidth, scaledChild1DHeight;
extern int scaledChild2DWidth, scaledChild2DHeight;

extern int scaledScrollPosX1D, scaledScrollPosY1D;
extern int scaledScrollPosX2D, scaledScrollPosY2D;

// �������
extern float scale1D, scale2D;

// ������� ����
extern std::vector<bool> grid1D;
extern std::vector<std::vector<bool>> grid2D;

// ��������� ������ ������
extern bool cellBorder1D, cellBorder2D;

// ��������� ���������
extern HDC hdc1D, hdcMem1D, hdc2D, hdcMem2D;
extern HBITMAP hbmMem1D, hbmMem2D;

// �����
extern HBRUSH hBrushAlive1D, hBrushDead1D;
extern HBRUSH hBrushAlive2D, hBrushDead2D;
//���������
extern HPEN hPenBorder2D, hPenBorder1D;

// ����� ��� ����������� ��������� �� �����
extern bool paintAble1D, paintAble2D;
// ����� � ��������
extern bool timer2D, timer1D;

// ��������� ����� ������
extern COLORREF colorAlive2D, colorDead2D, colorBorder2D, colorAlive1D, colorDead1D , colorBorder1D;

// ����� ��������� 1 - true, 2 - OR, 3 - XOR, 4 - FALSE
extern int paintStyle2D, paintStyle1D;


//����������� ����
extern HMENU hContextMenu2D, hContextMenu1D;

// ����� ������ ��������� �����:

extern POINT pointPaint2D, pointPaint1D;


extern HWND hColorInfoDlg;

//����� ������� ��� ���������� ����
extern HWND hEditRule1D;

//������� � ������� ��� ���������
extern int fps1D, fps2D;

//�������� ��� fps
extern HWND hTrackbarFps1D, hTrackbarFps2D;

//������ ��� ��������
extern HWND hTrackbar1DLabel, hTrackbar2DLabel;

//����� ��� ������� 1-������ ����
extern HWND hRule1DLabel, hRule1DEdit, hCurrRule1DLabel;

//������� ��� ����
extern int rule1D;