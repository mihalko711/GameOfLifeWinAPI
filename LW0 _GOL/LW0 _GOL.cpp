// LW0 _GOL.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "LW0 _GOL.h"
#include <vector>
#include <random>

#define MAX_LOADSTRING 100
#define GRID_SIZE 50 // Размер поля
#define CELL_SIZE 10 // Размер клетки

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
WCHAR szWindowClass1[MAX_LOADSTRING];           // имя класса главного окна
int able_to_create_win2d = 1;                    // флаг возможности создания окна для 2-мерной игры
int able_to_create_win1d = 1;                    // флаг возможности создания окна для 1-мерной игры
HWND hGameWnd1D, hGameWnd2D, hChild1D, hChild2D;
int scrollPosX1D = 0, scrollPosY1D = 0;                 //хранение позиций прокрутки для дочерних окон
int scrollPosX2D = 0, scrollPosY2D = 0;
int field1DWidth = 2000, field1DHeight = 2000;          // Задание размеров полей
int field2DWidth = 2000, field2DHeight = 2000;

int ChildWidth1D = 1000, ChildHeight1D = 600;           //размеры дочерних окон для отрисовки кллеток
int ChildWidth2D = 1000, ChildHeight2D = 600;
int field2D_vert_pages = 8, field2D_horz_pages = 8;     // Кол-во страниц для прокрутки полей
int field1D_vert_pages = 8, field1D_horz_pages = 8;
int cellCount1D = 100, cellCount2D = 100;               
int scaled1DWidth = field1DWidth, scaled1DHeight = field1DHeight;           // скалированные значения
int scaled2DWidth = field2DWidth, scaled2DHeight = field2DHeight;
int scaledChild1DWidth = ChildWidth1D, scaledChild1DHeight = ChildHeight1D;           // скалированные значения
int scaledChild2DWidth = ChildWidth2D, scaledChild2DHeight = ChildHeight2D;
int scaledScrollPosX1D = scrollPosX1D, scaledScrollPosY1D = scrollPosY1D;   // скалированные значения 
int scaledScrollPosX2D = scrollPosX2D, scaledScrollPosY2D = scrollPosY2D;
float scale2D = 1.0, scale1D = 1.0;
// инициализация стартовых массивов 
std::vector<bool> grid1D(cellCount1D* cellCount1D / 2, 0);
std::vector<std::vector<bool>> grid2D(cellCount2D, std::vector<bool>(cellCount2D, 0));
bool cellBorder1D = true, cellBorder2D = true; // нааличие границ клеток
//контексты устройств для отрисовки полей и контекс битмапа
HDC hdc1D, hdcMem1D, hdc2D, hdcMem2D;
HBITMAP hbmMem1D, hbmMem2D;
// кисти для раскраски живых и мертвых клеток
HBRUSH hBrushAlive1D, hBrushDead1D, hBrushAlive2D, hBrushDead2D;


//Отрисовка сетки:
void DrawGrid1D(HDC hdcMem, const std::vector<bool>& grid, int cellSize);
void DrawGrid2D(HDC hdcMem, const std::vector<std::vector<bool>>& grid, int cellSize);
//Оставшиеся функции работы с сеткой:
void UpdateGrid1D();
void UpdateGrid2D();
void ClearGrid1D();
void ClearGrid2D();
void RandomGrid1D();
void RandomGrid2D();

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM                MyRegisterClass2DGame(HINSTANCE hInstance);
ATOM                MyRegisterClass1DGame(HINSTANCE hInstance);
ATOM                RegisterChildClass1D(HINSTANCE);
ATOM                RegisterChildClass2D(HINSTANCE);
BOOL                InitInstance(HINSTANCE, int);
BOOL                InitInstance2D(HINSTANCE, int);
BOOL                InitInstance1D(HINSTANCE, int);
HWND                CreateChild2DWindow(HWND);
HWND                CreateChild1DWindow(HWND);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc1D(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc2D(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildWndProc1D(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildWndProc2D(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LW0GOL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    RegisterChildClass1D(hInstance);
    RegisterChildClass2D(hInstance);

    // проверка регистрации класса окна 2-мерной игры
    if (!MyRegisterClass2DGame(hInstance)) MessageBox(NULL, L"Ошибка регистрации главного окна", L"Ошибка", MB_ICONERROR);
    // проверка регистрации класса окна 1-мерной игры
    if (!MyRegisterClass1DGame(hInstance)) MessageBox(NULL, L"Ошибка регистрации главного окна", L"Ошибка", MB_ICONERROR);


    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LW0GOL));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    wcex.hbrBackground  = CreatePatternBrush(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1)));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LW0GOL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

    return RegisterClassExW(&wcex);
}
// класс главного окна для 2-мерной игры
ATOM MyRegisterClass2DGame(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc2D;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    wcex.hbrBackground = CreatePatternBrush(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1)));
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LW0GOL);
    wcex.lpszClassName = L"GOLClass2D";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

    ATOM result = RegisterClassExW(&wcex);
    if (result == 0) {
        DWORD err = GetLastError();
        wchar_t buf[256];
        wsprintf(buf, L"Ошибка регистрации класса: %lu", err);
        MessageBox(NULL, buf, L"Ошибка", MB_ICONERROR);
    }

    return result;
}
// класс главного окна для 1-мерной игры
ATOM MyRegisterClass1DGame(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc1D;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    wcex.hbrBackground = CreatePatternBrush(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1)));
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LW0GOL);
    wcex.lpszClassName = L"GOLClass1D";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

    ATOM result = RegisterClassExW(&wcex);
    if (result == 0) {
        DWORD err = GetLastError();
        wchar_t buf[256];
        wsprintf(buf, L"Ошибка регистрации класса: %lu", err);
        MessageBox(NULL, buf, L"Ошибка", MB_ICONERROR);
    }

    return result;
}

ATOM RegisterChildClass2D(HINSTANCE hInstance)
{
    WNDCLASSEXW wc = { 0 };

    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = ChildWndProc2D;  // обработчик для дочернего окна
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;  // если есть меню
    wc.lpszClassName = L"Child2D";  // Имя класса для дочернего окна

    return RegisterClassExW(&wc);
}

ATOM RegisterChildClass1D(HINSTANCE hInstance)
{
    WNDCLASSEXW wc = { 0 };

    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = 0;
    wc.lpfnWndProc = ChildWndProc1D;  // обработчик для дочернего окна
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;  // если есть меню
    wc.lpszClassName = L"Child1D";  // Имя класса для дочернего окна

    return RegisterClassExW(&wc);
}


//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

BOOL InitInstance2D(HINSTANCE hInstance, int nCmdShow)
{
    hGameWnd2D = CreateWindowW(L"GOLClass2D", szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hGameWnd2D)
    {
        return FALSE;
    }

    ShowWindow(hGameWnd2D, nCmdShow);
    UpdateWindow(hGameWnd2D);

    return TRUE;
}

BOOL InitInstance1D(HINSTANCE hInstance, int nCmdShow)
{
    hGameWnd1D = CreateWindowW(L"GOLClass1D", szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hGameWnd1D)
    {
        return FALSE;
    }

    ShowWindow(hGameWnd1D, nCmdShow);
    UpdateWindow(hGameWnd1D);

    return TRUE;
}

HWND CreateChild2DWindow(HWND hParent) {
    return CreateWindowEx(0, L"Child2D", NULL,
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,
        50, 50, ChildWidth2D, ChildHeight2D,
        hParent, NULL, hInst, NULL);
}

HWND CreateChild1DWindow(HWND hParent) {
    return CreateWindowEx(0, L"Child1D", NULL,
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,
        50, 50, ChildWidth1D, ChildHeight1D,
        hParent, NULL, hInst, NULL);
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // Создаём кнопки для создания окон с играми
        CreateWindow(L"BUTTON", L"2D Game of Life",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            20, 20, 150, 30,
            hWnd, (HMENU)ID_BUTTON_START2D, hInst, NULL);
        CreateWindow(L"BUTTON", L"1D Game of Life",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            20, 60, 150, 30,
            hWnd, (HMENU)ID_BUTTON_START1D, hInst, NULL);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_BUTTON_START2D:
                if (able_to_create_win2d) {
                    InitInstance2D(hInst, SW_SHOW);
                    able_to_create_win2d = 0;
                }
                break;
            case ID_BUTTON_START1D:
                if (able_to_create_win1d) {
                    InitInstance1D(hInst, SW_SHOW);
                    able_to_create_win1d = 0;
                }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WndProc2D(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hChild2D = CreateChild2DWindow(hWnd);
        // Создаём кнопки управления
        CreateWindow(L"BUTTON", L"Start",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 50, 150, 30,
            hWnd, (HMENU)ID_START2D_BUTTON, hInst, NULL);
        CreateWindow(L"BUTTON", L"Clear",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 100, 150, 30,
            hWnd, (HMENU)ID_CLEAR2D_BUTTON, hInst, NULL);
        CreateWindow(L"BUTTON", L"Random",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 150, 150, 30,
            hWnd, (HMENU)ID_RANDOM2D_BUTTON, hInst, NULL);
        CreateWindow(L"BUTTON", L"Stop",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 200, 150, 30,
            hWnd, (HMENU)ID_STOP2D_BUTTON, hInst, NULL);
    }
    break;
    case WM_MOUSEWHEEL:
    {
        //пересылка сообщения о колесике мыши в дочернее окно
        SendMessageW(hChild2D, WM_MOUSEHWHEEL, wParam, lParam);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_START2D_BUTTON:
            SetTimer(hWnd, 2, 10, NULL);
            break;
        case ID_CLEAR2D_BUTTON:
        {
            ClearGrid2D();
            InvalidateRect(hChild2D, NULL, FALSE);
        }
            break;
        case ID_RANDOM2D_BUTTON:
        {
            RandomGrid2D();
            InvalidateRect(hChild2D, NULL, FALSE);
        }
            break;
        case ID_STOP2D_BUTTON:
            KillTimer(hWnd, 2);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_TIMER:
    {
        UpdateGrid2D();
        InvalidateRect(hChild2D, NULL, FALSE);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, 2);
        able_to_create_win2d = 1;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WndProc1D(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hChild1D = CreateChild1DWindow(hWnd);
        // Создаём кнопки управления
        CreateWindow(L"BUTTON", L"Start",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 50, 150, 30,
            hWnd, (HMENU)ID_START1D_BUTTON, hInst, NULL);
        CreateWindow(L"BUTTON", L"Clear",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 100, 150, 30,
            hWnd, (HMENU)ID_CLEAR1D_BUTTON, hInst, NULL);
        CreateWindow(L"BUTTON", L"Random",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 150, 150, 30,
            hWnd, (HMENU)ID_RANDOM1D_BUTTON, hInst, NULL);
        CreateWindow(L"BUTTON", L"Stop",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 200, 150, 30,
            hWnd, (HMENU)ID_STOP1D_BUTTON, hInst, NULL);    
    }
    break;
    case WM_MOUSEWHEEL:
    {
        //пересылка сообщения о колесике мыши в дочернее окно
        SendMessageW(hChild1D, WM_MOUSEHWHEEL, wParam, lParam);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_START1D_BUTTON:
            SetTimer(hWnd, 1, 10, NULL);
            break;
        case ID_CLEAR1D_BUTTON:
        {
            ClearGrid1D();
            InvalidateRect(hChild1D, NULL, FALSE);
        }
            break;
        case ID_RANDOM1D_BUTTON:
        {
            RandomGrid1D();
            InvalidateRect(hChild1D, NULL, FALSE);
        }
            break;
        case ID_STOP1D_BUTTON:
            KillTimer(hWnd, 1);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_TIMER:
    {
        UpdateGrid1D();
        InvalidateRect(hChild1D, NULL, FALSE);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        able_to_create_win1d = 1;
        KillTimer(hWnd, 1);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ChildWndProc2D(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
    {   
        // присвавиание значений контекстам устройств для отрисовки
        hdc2D = GetDC(hWnd);
        hdcMem2D = CreateCompatibleDC(hdc2D); // буфер
        hbmMem2D = CreateCompatibleBitmap(hdc2D, field2DWidth, field2DHeight); // BitMap
        SelectObject(hdcMem2D, hbmMem2D); // подключение битмапа к DC

        ReleaseDC(hWnd, hdc2D);

        //базовая инициализация кистей:
        hBrushDead2D = CreateSolidBrush(RGB(0, 0, 0));
        hBrushAlive2D = CreateSolidBrush(RGB(255, 255, 255));
        // Установим параметры для вертикального скролла
        SCROLLINFO si_vert = { sizeof(si_vert) };
        si_vert.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
        si_vert.nMin = 0;
        si_vert.nMax = field2DHeight - 1;        // Устанавливаем максимальное значение
        si_vert.nPage = ChildHeight2D;        // Устанавливаем видимую область
        si_vert.nPos = 0;           // Начальная позиция

        SetScrollInfo(hWnd, SB_VERT, &si_vert, TRUE);  // Устанавливаем параметры

        // Установим параметры для горизонтального скролла
        SCROLLINFO si_horz = { sizeof(si_horz) };
        si_horz.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
        si_horz.nMin = 0;
        si_horz.nMax = field2DWidth - 1;        // Устанавливаем максимальное значение
        si_horz.nPage = ChildWidth2D;        // Устанавливаем видимую область
        si_horz.nPos = 0;           // Начальная позиция

        SetScrollInfo(hWnd, SB_HORZ, &si_horz, TRUE);  // Устанавливаем параметры
    }
    break;
    case WM_MOUSEHWHEEL:
    {
        // Обработка пересланного сообщения прокрутки
        int zDelta = GET_WHEEL_DELTA_WPARAM(wParam); // ±120, ±240 и т.д.

        bool ctrlPressed = (wParam & MK_CONTROL) != 0;
        bool shiftPressed = (wParam & MK_SHIFT) != 0;

        if (shiftPressed) {
            scrollPosX2D -= zDelta / 120 * 10;
            scrollPosX2D = min(max(scrollPosX2D, 0), field2DWidth - ChildWidth2D);
            scaledScrollPosX2D = (int)(scrollPosX2D / scale2D);
            SetScrollPos(hWnd, SB_HORZ, scrollPosX2D, TRUE);
            InvalidateRect(hWnd, nullptr, FALSE);
        }
        else if (ctrlPressed) {
            scale2D += zDelta / 120 * 0.2;
            scale2D = min(max(scale2D, 1.0), 2.0);
            scaled2DHeight = (int)(field2DHeight / scale2D);
            scaled2DWidth = (int)(field2DWidth / scale2D);
            scaledChild2DHeight = (int)(ChildHeight2D / scale2D);
            scaledChild2DWidth = (int)(ChildWidth2D / scale2D);
            scaledScrollPosX2D = (int)(scrollPosX2D / scale2D);
            scaledScrollPosY2D = (int)(scrollPosY2D / scale2D);
            InvalidateRect(hWnd, nullptr, FALSE);
            /*wchar_t buffer[100];
            swprintf(buffer, 100, L"Текущий масштаб: %.2fx, %d, %d, %d, %d", scale2D, scaled2DHeight, scaled2DWidth, scaledScrollPosX2D, scaledScrollPosY2D);
            MessageBox(NULL, buffer, L"Масштаб", MB_OK | MB_ICONINFORMATION);*/

        }
        else {
            scrollPosY2D -= zDelta / 120 * 10;
            scrollPosY2D = min(max(scrollPosY2D, 0), field2DHeight - ChildHeight2D);
            scaledScrollPosY2D = (int)(scrollPosY2D / scale2D);
            SetScrollPos(hWnd, SB_VERT, scrollPosY2D, TRUE);
            InvalidateRect(hWnd, nullptr, FALSE);
        }
    }
    break;
    case WM_VSCROLL: 
    {
        int scrollCode = LOWORD(wParam); // получаем тип действия
        int position = HIWORD(wParam); // получение позиции ползунка(при возможности)

        // обработка в зависимости от произведенного действия
        switch (scrollCode)
        {
        //прокрутка на строку вверх
        case SB_LINEUP: scrollPosY2D -= field2DHeight / 10; break;
        //прокрутка на строку вниз
        case SB_LINEDOWN: scrollPosY2D += field2DHeight / 10; break;
        //прокрутка на страницу вверх
        case SB_PAGEUP: scrollPosY2D -= field2DHeight / field2D_vert_pages; break;
        //прокрутка на страницу вниз
        case SB_PAGEDOWN: scrollPosY2D += field2DHeight / field2D_vert_pages; break;
        //перетаскивание ползунка
        case SB_THUMBPOSITION: scrollPosY2D = HIWORD(wParam); break;
        // ползунок отпущен
        case SB_THUMBTRACK:
        break;
        // ползунок сверху
        case SB_TOP:
        break;
        // ползунок снизу
        case SB_BOTTOM:
        break;
        // конец прокрутки
        case SB_ENDSCROLL:
        break;
        }
        scrollPosY2D = min(max(scrollPosY2D, 0), field2DHeight - ChildHeight2D);
        scaledScrollPosY2D = (int)(scrollPosY2D / scale2D);
        SetScrollPos(hWnd, SB_VERT, scrollPosY2D, TRUE);
        InvalidateRect(hWnd, nullptr, FALSE);
    }
    break;
    case WM_HSCROLL: 
    {
        int scrollCode = LOWORD(wParam); // получаем тип действия
        int position = HIWORD(wParam); // получение позиции ползунка(при возможности)

        // обработка в зависимости от произведенного действия
        switch (scrollCode)
        {
        //прокрутка на строку вверх
        case SB_LINELEFT: scrollPosX2D -= field2DWidth / 10; break;
        //прокрутка на строку вниз
        case SB_LINERIGHT: scrollPosX2D += field2DWidth / 10; break;
        //прокрутка на страницу вверх
        case SB_PAGELEFT: scrollPosX2D -= field2DWidth / field2D_horz_pages; break;
        //прокрутка на страницу вниз
        case SB_PAGERIGHT: scrollPosX2D += field2DWidth / field2D_horz_pages; break;
        //перетаскивание ползунка
        case SB_THUMBPOSITION: scrollPosX2D = HIWORD(wParam); break;
        // ползунок отпущен
        case SB_THUMBTRACK:
            break;
        // конец прокрутки
        case SB_ENDSCROLL:
            break;
        }
        scrollPosX2D = min(max(scrollPosX2D, 0), field2DWidth - ChildWidth2D);
        scaledScrollPosX2D = (int)(scrollPosX2D / scale2D);
        SetScrollPos(hWnd, SB_HORZ, scrollPosX2D, TRUE);
        InvalidateRect(hWnd, nullptr, FALSE);
    }
    break;
    case WM_PAINT: 
    {
        PAINTSTRUCT ps;
        hdc2D = BeginPaint(hWnd, &ps);

        DrawGrid2D(hdcMem2D, grid2D, field2DHeight / cellCount2D);
        TextOut(hdcMem2D, 10, 10, L"Игровое поле 2D", 18);
        //переносим готовый буфер на экран
        //BitBlt(hdc2D, 0, 0, ChildWidth2D, ChildHeight2D, hdcMem2D, scrollPosX2D, scrollPosY2D, SRCCOPY);
        StretchBlt(
            hdc2D,
            0, 0,
            ChildWidth2D,  // масштабируем ширину окна
            ChildHeight2D, // масштабируем высоту окна
            hdcMem2D,
            scaledScrollPosX2D, scaledScrollPosY2D,
            scaledChild2DWidth, scaledChild2DHeight,
            SRCCOPY
        );


        EndPaint(hWnd, &ps);
    }
    break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK ChildWndProc1D(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
    {
        // присвавиание значений контекстам устройств для отрисовки
        hdc1D = GetDC(hWnd);
        hdcMem1D = CreateCompatibleDC(hdc1D); // буфер
        hbmMem1D = CreateCompatibleBitmap(hdc1D, field1DWidth, field1DHeight); // BitMap
        SelectObject(hdcMem1D, hbmMem1D); // подключение битмапа к DC

        ReleaseDC(hWnd, hdc1D);

        //базовая инициализация кистей:
        hBrushDead1D = CreateSolidBrush(RGB(0, 0, 0));
        hBrushAlive1D = CreateSolidBrush(RGB(255, 255, 255));

        // Установим параметры для вертикального скролла
        SCROLLINFO si_vert = { sizeof(si_vert) };
        si_vert.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
        si_vert.nMin = 0;
        si_vert.nMax = field1DHeight - 1;        // Устанавливаем максимальное значение
        si_vert.nPage = ChildHeight1D;        // Устанавливаем видимую область
        si_vert.nPos = 0;           // Начальная позиция

        SetScrollInfo(hWnd, SB_VERT, &si_vert, TRUE);  // Устанавливаем параметры

        // Установим параметры для горизонтального скролла
        SCROLLINFO si_horz = { sizeof(si_horz) };
        si_horz.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
        si_horz.nMin = 0;
        si_horz.nMax = field1DWidth - 1;        // Устанавливаем максимальное значение
        si_horz.nPage = ChildWidth1D;        // Устанавливаем видимую область
        si_horz.nPos = 0;           // Начальная позиция

        SetScrollInfo(hWnd, SB_HORZ, &si_horz, TRUE);  // Устанавливаем параметры
    }
    break;
    case WM_MOUSEHWHEEL:
    {
        // Обработка пересланного сообщения прокрутки
        int zDelta = GET_WHEEL_DELTA_WPARAM(wParam); // ±120, ±240 и т.д.

        bool ctrlPressed = (wParam & MK_CONTROL) != 0;
        bool shiftPressed = (wParam & MK_SHIFT) != 0;

        if (shiftPressed) {
            scrollPosX1D -= zDelta / 120 * 10;
            scrollPosX1D = min(max(scrollPosX1D, 0), field1DWidth - ChildWidth1D);
            SetScrollPos(hWnd, SB_HORZ, scrollPosX1D, TRUE);
            InvalidateRect(hWnd, nullptr, FALSE);
        }
        else if (ctrlPressed) {

        }
        else {
            scrollPosY1D -= zDelta / 120 * 10;
            scrollPosY1D = min(max(scrollPosY1D, 0), field1DHeight - ChildHeight1D);
            SetScrollPos(hWnd, SB_VERT, scrollPosY1D, TRUE);
            InvalidateRect(hWnd, nullptr, FALSE);
        }
    }
    break;
    case WM_VSCROLL:
    {
        int scrollCode = LOWORD(wParam); // получаем тип действия
        int position = HIWORD(wParam); // получение позиции ползунка(при возможности)

        // обработка в зависимости от произведенного действия
        switch (scrollCode)
        {
            //прокрутка на строку вверх
        case SB_LINEUP: scrollPosY1D -= field1DHeight / 10; break;
            //прокрутка на строку вниз
        case SB_LINEDOWN: scrollPosY1D += field1DHeight / 10; break;
            //прокрутка на страницу вверх
        case SB_PAGEUP: scrollPosY1D -= field1DHeight / field1D_vert_pages; break;
            //прокрутка на страницу вниз
        case SB_PAGEDOWN: scrollPosY1D += field1DHeight / field1D_vert_pages; break;
            //перетаскивание ползунка
        case SB_THUMBPOSITION: scrollPosY1D = HIWORD(wParam); break;
            // ползунок отпущен
        case SB_THUMBTRACK:
            break;
            // ползунок сверху
        case SB_TOP:
            break;
            // ползунок снизу
        case SB_BOTTOM:
            break;
            // конец прокрутки
        case SB_ENDSCROLL:
            break;
        }
        scrollPosY1D = min(max(scrollPosY1D, 0), field1DHeight - ChildHeight1D);
        SetScrollPos(hWnd, SB_VERT, scrollPosY1D, TRUE);
        InvalidateRect(hWnd, nullptr, FALSE); // не перерисовываем фон,  т.к. используем буферизацию
    }
    break;
    case WM_HSCROLL:
    {
        int scrollCode = LOWORD(wParam); // получаем тип действия
        int position = HIWORD(wParam); // получение позиции ползунка(при возможности)

        // обработка в зависимости от произведенного действия
        switch (scrollCode)
        {
            //прокрутка на строку вверх
        case SB_LINELEFT: scrollPosX1D -= field1DWidth / 10; break;
            //прокрутка на строку вниз
        case SB_LINERIGHT: scrollPosX1D += field1DWidth / 10; break;
            //прокрутка на страницу вверх
        case SB_PAGELEFT: scrollPosX1D -= field1DWidth / field1D_horz_pages; break;
            //прокрутка на страницу вниз
        case SB_PAGERIGHT: scrollPosX1D += field1DWidth / field1D_horz_pages; break;
            //перетаскивание ползунка
        case SB_THUMBPOSITION: scrollPosX1D = HIWORD(wParam); break;
            // ползунок отпущен
        case SB_THUMBTRACK:
            break;
            // конец прокрутки
        case SB_ENDSCROLL:
            break;
        }
        scrollPosX1D = min(max(scrollPosX1D, 0), field1DWidth - ChildWidth1D);
        SetScrollPos(hWnd, SB_HORZ, scrollPosX1D, TRUE);
        InvalidateRect(hWnd, nullptr, FALSE); // не перерисовываем фон,  т.к. используем буферизацию
    }
    break;
    case WM_PAINT: 
    {
        PAINTSTRUCT ps;
        hdc1D = BeginPaint(hWnd, &ps);
        RECT fullRect = { 0, 0, field1DWidth, field1DHeight };
        FillRect(hdcMem1D, &fullRect, (HBRUSH)(COLOR_WINDOW + 100));
        
        DrawGrid1D(hdcMem1D, grid1D, field1DHeight / cellCount1D);
        TextOut(hdcMem1D, 10, 10, L"Игровое поле 1D", 18);

        //переносим готовый буфер на экран
        BitBlt(hdc1D, 0, 0, ChildWidth1D, ChildHeight1D, hdcMem1D, scrollPosX1D, scrollPosY1D, SRCCOPY);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
    {
        DeleteObject(hbmMem1D);
        DeleteDC(hdcMem1D);
    }
    break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);   
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
void DrawGrid1D(HDC hdcMem, const std::vector<bool>& grid, int cellSize) {
    for (size_t i = 0; i < grid.size(); i++) {
        RECT cellRect = {
            (LONG)((i % cellCount1D) * cellSize ), (LONG)(2 * (i / cellCount1D) * cellSize),
            (LONG)((i % cellCount1D + 1) * cellSize), (LONG)((2 * (i / cellCount1D) + 1) * cellSize)
        };

        FillRect(hdcMem, &cellRect, grid[i] ? hBrushAlive1D : hBrushDead1D);

        if (cellBorder1D) {
            // граница
            MoveToEx(hdcMem, cellRect.left, cellRect.top, NULL);
            LineTo(hdcMem, cellRect.right, cellRect.top);
            LineTo(hdcMem, cellRect.right, cellRect.bottom);
            LineTo(hdcMem, cellRect.left, cellRect.bottom);
            LineTo(hdcMem, cellRect.left, cellRect.top);
        }
    }
}
void DrawGrid2D(HDC hdcMem, const std::vector<std::vector<bool>>& grid, int cellSize) {
    for (int x = 0; x < cellCount2D; x++) {
        for (int y = 0; y < cellCount2D; y++) {
            RECT cellRect = {
                y * cellSize,
                x * cellSize,
                (y + 1) * cellSize,
                (x + 1) * cellSize
            };

            FillRect(hdcMem, &cellRect, grid[x][y] ? hBrushAlive2D : hBrushDead2D);

            if (cellBorder2D) {
                // граница
                MoveToEx(hdcMem, cellRect.left, cellRect.top, NULL);
                LineTo(hdcMem, cellRect.right, cellRect.top);
                LineTo(hdcMem, cellRect.right, cellRect.bottom);
                LineTo(hdcMem, cellRect.left, cellRect.bottom);
                LineTo(hdcMem, cellRect.left, cellRect.top);
            }
        }
    }
}

void UpdateGrid1D() {
    std::vector<bool> newGrid1D = grid1D;

    if (grid1D[0] && grid1D[1]) {
        newGrid1D[0] = true;
    }

    if (grid1D[grid1D.size() - 1] && grid1D[grid1D.size() - 2]) {
        newGrid1D[grid1D.size() - 1] = true;
    }
    // тут пока упрощеннгое правило, в будущем добавлю все правила
    for (size_t i = 1; i < grid1D.size() - 1; i++) {
        int liveNeighbors = grid1D[i - 1] + grid1D[i + 1];
        if (grid1D[i]) {
            if (liveNeighbors == 0 || liveNeighbors == 1) newGrid1D[i] = true;
            else newGrid1D[i] = false;
        }
        else if (!grid1D[i] && liveNeighbors == 2) {
            newGrid1D[i] = true;
        }
    }

    grid1D = newGrid1D;
}

void UpdateGrid2D() {
    std::vector<std::vector<bool>> newGrid2D = grid2D;
    int grid2Dheight = grid2D.size();
    int grid2Dwidth = grid2D[0].size();
    for (size_t i = 0; i < grid2D.size(); i++) {
        for (size_t j = 0; j < grid2D[i].size(); j++) {
            int liveNeighbors = 0;

            for (int x = -1; (x <= 1); x++) {
                for (int y = -1; (y <= 1); y++) {
                    if ((x == 0) && (y == 0)) continue;

                    if (i + x >= 0 && i + x < grid2Dheight && j + y >= 0 && j + y < grid2Dwidth && grid2D[i + x][j + y]) liveNeighbors++;
                }
            }

            if (grid2D[i][j]) {
                if(liveNeighbors < 2 || liveNeighbors > 3) 
                    newGrid2D[i][j] = false;
            }
            else if (liveNeighbors == 3) newGrid2D[i][j] = true;
        }
    }

    grid2D = newGrid2D;
}

void ClearGrid1D() {
    for (size_t i = 0; i < grid1D.size(); i++) {
        grid1D[i] = false;
    }
}

void ClearGrid2D() {
    for (size_t i = 0; i < grid2D.size(); i++) {
        for (size_t j = 0; j < grid2D[i].size(); j++) {
            grid2D[i][j] = false;
        }
    }
}

void RandomGrid1D() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);

    for (size_t i = 0; i < grid1D.size(); i++) {
        grid1D[i] = distrib(gen);
    }
}

void RandomGrid2D() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);

    for (size_t i = 0; i < grid2D.size(); i++) {
        for (size_t j = 0; j < grid2D[i].size(); j++) {
            grid2D[i][j] = distrib(gen);
        }
    }
}