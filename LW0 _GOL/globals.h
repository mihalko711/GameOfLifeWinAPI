#pragma once

#include <windows.h>
#include <vector>

#define MAX_LOADSTRING 100
#define GRID_SIZE 50 // Размер поля
#define CELL_SIZE 10 // Размер клетки

extern INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Глобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
extern WCHAR szWindowClass1[MAX_LOADSTRING];           // имя класса главного окна

// Флаги создания окон
extern int able_to_create_win2d;
extern int able_to_create_win1d;

// Основные HWND
extern HWND hGameWnd1D, hGameWnd2D, hChild1D, hChild2D;

// Позиции прокрутки
extern int scrollPosX1D, scrollPosY1D;
extern int scrollPosX2D, scrollPosY2D;

// Размеры полей
extern int field1DWidth, field1DHeight;
extern int field2DWidth, field2DHeight;

// Размеры дочерних окон
extern int ChildWidth1D, ChildHeight1D;
extern int ChildWidth2D, ChildHeight2D;

// Страницы прокрутки
extern int field1D_vert_pages, field1D_horz_pages;
extern int field2D_vert_pages, field2D_horz_pages;

// Количество клеток
extern int cellCount1D, cellCount2D;

//Размер клеток
extern int cellSize2D, cellSize1D;

// Скалированные значения
extern int scaled1DWidth, scaled1DHeight;
extern int scaled2DWidth, scaled2DHeight;

extern int scaledChild1DWidth, scaledChild1DHeight;
extern int scaledChild2DWidth, scaledChild2DHeight;

extern int scaledScrollPosX1D, scaledScrollPosY1D;
extern int scaledScrollPosX2D, scaledScrollPosY2D;

// Масштаб
extern float scale1D, scale2D;

// Игровые поля
extern std::vector<bool> grid1D;
extern std::vector<std::vector<bool>> grid2D;

// Отрисовка границ клеток
extern bool cellBorder1D, cellBorder2D;

// Контексты отрисовки
extern HDC hdc1D, hdcMem1D, hdc2D, hdcMem2D;
extern HBITMAP hbmMem1D, hbmMem2D;

// Кисти
extern HBRUSH hBrushAlive1D, hBrushDead1D;
extern HBRUSH hBrushAlive2D, hBrushDead2D;
//Карандаши
extern HPEN hPenBorder2D, hPenBorder1D;

// Флаги для возможности рисования на полях
extern bool paintAble1D, paintAble2D;
// Флаги о таймерах
extern bool timer2D, timer1D;

// Дефолтные цвета клеток
extern COLORREF colorAlive2D, colorDead2D, colorBorder2D, colorAlive1D, colorDead1D , colorBorder1D;

// стиль рисвоания 1 - true, 2 - OR, 3 - XOR, 4 - FALSE
extern int paintStyle2D, paintStyle1D;


//контекстные меню
extern HMENU hContextMenu2D, hContextMenu1D;

// точка начала отрисовки фигур:

extern POINT pointPaint2D, pointPaint1D;


extern HWND hColorInfoDlg;

//Номер правила для одномерной игры
extern HWND hEditRule1D;

//кадрорв в секунду для отрисовки
extern int fps1D, fps2D;

//трекбары для fps
extern HWND hTrackbarFps1D, hTrackbarFps2D;

//лейблы для трекбара
extern HWND hTrackbar1DLabel, hTrackbar2DLabel;

//лейбл для правила 1-мерной игры
extern HWND hRule1DLabel, hRule1DEdit, hCurrRule1DLabel;

//правило для игры
extern int rule1D;