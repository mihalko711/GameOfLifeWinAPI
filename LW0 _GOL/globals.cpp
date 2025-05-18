#include "globals.h"

int able_to_create_win2d = 1;                    // флаг возможности создани€ окна дл€ 2-мерной игры
int able_to_create_win1d = 1;                    // флаг возможности создани€ окна дл€ 1-мерной игры
HWND hGameWnd1D, hGameWnd2D, hChild1D, hChild2D;
int scrollPosX1D = 0, scrollPosY1D = 0;                 //хранение позиций прокрутки дл€ дочерних окон
int scrollPosX2D = 0, scrollPosY2D = 0;
int field1DWidth = 2000, field1DHeight = 2000;          // «адание размеров полей
int field2DWidth = 2000, field2DHeight = 2000;

int ChildWidth1D = 1000, ChildHeight1D = 600;           //размеры дочерних окон дл€ отрисовки кллеток
int ChildWidth2D = 1000, ChildHeight2D = 600;
int field2D_vert_pages = 8, field2D_horz_pages = 8;     //  ол-во страниц дл€ прокрутки полей
int field1D_vert_pages = 8, field1D_horz_pages = 8;
int cellCount1D = 100, cellCount2D = 100;
int cellSize2D = field2DHeight / cellCount2D, cellSize1D = field1DWidth / cellCount1D;
int scaled1DWidth = field1DWidth, scaled1DHeight = field1DHeight;           // скалированные значени€
int scaled2DWidth = field2DWidth, scaled2DHeight = field2DHeight;
int scaledChild1DWidth = ChildWidth1D, scaledChild1DHeight = ChildHeight1D;           // скалированные значени€
int scaledChild2DWidth = ChildWidth2D, scaledChild2DHeight = ChildHeight2D;
int scaledScrollPosX1D = scrollPosX1D, scaledScrollPosY1D = scrollPosY1D;   // скалированные значени€ 
int scaledScrollPosX2D = scrollPosX2D, scaledScrollPosY2D = scrollPosY2D;
float scale2D = 1.0, scale1D = 1.0;
// инициализаци€ стартовых массивов 
std::vector<bool> grid1D(cellCount1D * cellCount1D, 0);
std::vector<std::vector<bool>> grid2D(cellCount2D, std::vector<bool>(cellCount2D, 0));
bool cellBorder1D = true, cellBorder2D = true; // нааличие границ клеток
//контексты устройств дл€ отрисовки полей и контекс битмапа
HDC hdc1D, hdcMem1D, hdc2D, hdcMem2D;
HBITMAP hbmMem1D, hbmMem2D;
// кисти дл€ раскраски живых и мертвых клеток
HBRUSH hBrushAlive1D, hBrushDead1D, hBrushAlive2D, hBrushDead2D;
// карандаши
HPEN hPenBorder2D, hPenBorder1D;
// ‘лаги дл€ возможности рисовани€ на пол€х
bool paintAble1D = false, paintAble2D = false;

// ‘лаги дл€ таймеров
bool timer2D = false, timer1D = false;

// ÷вета клеток
COLORREF colorAlive2D = RGB(255, 255, 255), colorDead2D = RGB(0, 0, 0), colorBorder2D = RGB(0, 0, 0), colorAlive1D = RGB(255, 255, 255), colorDead1D = RGB(0, 0, 0), colorBorder1D = RGB(0, 0, 0);

// стиль рисвоани€ 1 - true, 2 - OR, 3 - XOR, 4 - FALSE
int paintStyle2D = 1, paintStyle1D = 1;

//контекстные меню
HMENU hContextMenu2D, hContextMenu1D;

// точка начала отрисовки фигур:

POINT pointPaint2D, pointPaint1D;

//немодальное окно с ифной о выбранном цвете

HWND hColorInfoDlg = NULL;


//номер правила дл€ одномерной игры
HWND hEditRule1D;

//кадрорв в секунду дл€ отрисовки
int fps1D = 10, fps2D = 10;

//трекбары дл€ fps
HWND hTrackbarFps1D, hTrackbarFps2D;

//лейблы дл€ трекбара
HWND hTrackbar1DLabel, hTrackbar2DLabel;

//лейбл дл€ правила 1-мерной игры
HWND hRule1DLabel, hRule1DEdit, hCurrRule1DLabel;

//правило дл€ игры
int rule1D = 0;