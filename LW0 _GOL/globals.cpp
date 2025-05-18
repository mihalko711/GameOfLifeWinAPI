#include "globals.h"

int able_to_create_win2d = 1;                    // ���� ����������� �������� ���� ��� 2-������ ����
int able_to_create_win1d = 1;                    // ���� ����������� �������� ���� ��� 1-������ ����
HWND hGameWnd1D, hGameWnd2D, hChild1D, hChild2D;
int scrollPosX1D = 0, scrollPosY1D = 0;                 //�������� ������� ��������� ��� �������� ����
int scrollPosX2D = 0, scrollPosY2D = 0;
int field1DWidth = 2000, field1DHeight = 2000;          // ������� �������� �����
int field2DWidth = 2000, field2DHeight = 2000;

int ChildWidth1D = 1000, ChildHeight1D = 600;           //������� �������� ���� ��� ��������� �������
int ChildWidth2D = 1000, ChildHeight2D = 600;
int field2D_vert_pages = 8, field2D_horz_pages = 8;     // ���-�� ������� ��� ��������� �����
int field1D_vert_pages = 8, field1D_horz_pages = 8;
int cellCount1D = 100, cellCount2D = 100;
int cellSize2D = field2DHeight / cellCount2D, cellSize1D = field1DWidth / cellCount1D;
int scaled1DWidth = field1DWidth, scaled1DHeight = field1DHeight;           // ������������� ��������
int scaled2DWidth = field2DWidth, scaled2DHeight = field2DHeight;
int scaledChild1DWidth = ChildWidth1D, scaledChild1DHeight = ChildHeight1D;           // ������������� ��������
int scaledChild2DWidth = ChildWidth2D, scaledChild2DHeight = ChildHeight2D;
int scaledScrollPosX1D = scrollPosX1D, scaledScrollPosY1D = scrollPosY1D;   // ������������� �������� 
int scaledScrollPosX2D = scrollPosX2D, scaledScrollPosY2D = scrollPosY2D;
float scale2D = 1.0, scale1D = 1.0;
// ������������� ��������� �������� 
std::vector<bool> grid1D(cellCount1D * cellCount1D, 0);
std::vector<std::vector<bool>> grid2D(cellCount2D, std::vector<bool>(cellCount2D, 0));
bool cellBorder1D = true, cellBorder2D = true; // �������� ������ ������
//��������� ��������� ��� ��������� ����� � ������� �������
HDC hdc1D, hdcMem1D, hdc2D, hdcMem2D;
HBITMAP hbmMem1D, hbmMem2D;
// ����� ��� ��������� ����� � ������� ������
HBRUSH hBrushAlive1D, hBrushDead1D, hBrushAlive2D, hBrushDead2D;
// ���������
HPEN hPenBorder2D, hPenBorder1D;
// ����� ��� ����������� ��������� �� �����
bool paintAble1D = false, paintAble2D = false;

// ����� ��� ��������
bool timer2D = false, timer1D = false;

// ����� ������
COLORREF colorAlive2D = RGB(255, 255, 255), colorDead2D = RGB(0, 0, 0), colorBorder2D = RGB(0, 0, 0), colorAlive1D = RGB(255, 255, 255), colorDead1D = RGB(0, 0, 0), colorBorder1D = RGB(0, 0, 0);

// ����� ��������� 1 - true, 2 - OR, 3 - XOR, 4 - FALSE
int paintStyle2D = 1, paintStyle1D = 1;

//����������� ����
HMENU hContextMenu2D, hContextMenu1D;

// ����� ������ ��������� �����:

POINT pointPaint2D, pointPaint1D;

//����������� ���� � ����� � ��������� �����

HWND hColorInfoDlg = NULL;


//����� ������� ��� ���������� ����
HWND hEditRule1D;

//������� � ������� ��� ���������
int fps1D = 10, fps2D = 10;

//�������� ��� fps
HWND hTrackbarFps1D, hTrackbarFps2D;

//������ ��� ��������
HWND hTrackbar1DLabel, hTrackbar2DLabel;

//����� ��� ������� 1-������ ����
HWND hRule1DLabel, hRule1DEdit, hCurrRule1DLabel;

//������� ��� ����
int rule1D = 0;