// LW0 _GOL.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "LW0 _GOL.h"
#include "grid_logic.h"
#include "globals.h"
#include "game_windows.h"


HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
WCHAR szWindowClass1[MAX_LOADSTRING];           // имя класса главного окна


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);




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
            case IDM_1D:
            if (able_to_create_win1d) {
                InitInstance1D(hInst, SW_SHOW);
                able_to_create_win1d = 0;
            }
            break;
            case IDM_2D:
            if (able_to_create_win2d) {
                InitInstance2D(hInst, SW_SHOW);
                able_to_create_win2d = 0;
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

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {

        HBITMAP hBmp = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
        SendDlgItemMessage(hDlg, IDC_STATIC_LOGO, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);

        HWND hCombo = GetDlgItem(hDlg, IDC_COMBO1);
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"2D: Классические паттерны");
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"1D: Автоматы Вольфрама");

        SendMessage(hCombo, CB_SETCURSEL, 0, 0); // выбрать первый пункт по умолчанию
        PostMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_COMBO1, CBN_SELCHANGE), (LPARAM)hCombo); // вручную вызвать обработку

        SetDlgItemText(hDlg, IDC_DESCRIPTION,
            L"Игра «Жизнь» — это клеточный автомат, придуманный математиком Джоном Конвеем в 1970 году.\r\n"
            L"Это простая, но глубокая модель, демонстрирующая, как сложное поведение может возникать из простых правил.\r\n"
            L"\r\n"
            L"Программа реализует двухмерную и одномерную версии автомата.\r\n"
            L"Вы можете размещать шаблоны (например, \"глайдеры\" или \"осцилляторы\") и наблюдать за их эволюцией.\r\n"
            L"Также доступно ручное редактирование, изменение скорости обновления и переключение правил.\r\n"
            L"\r\n"
            L"Особенности:\r\n"
            L"• 2D-режим с классическими паттернами\r\n"
            L"• 1D-режим с автоматами Вольфрама (правила 0–255)\r\n"
            L"• Возможность паузы и пошагового режима\r\n"
            L"• Контекстное меню и пользовательский интерфейс Windows\r\n"
            L"\r\n"
            L"Автор: Михаил Чирков.\r\n"
            L"GitHub: github.com/mihalko711\r\n"
            L"Telegram: @mihalko711"
        );

        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            if (LOWORD(wParam) == IDC_COMBO1 && HIWORD(wParam) == CBN_SELCHANGE) {
                
            }

            case IDC_COMBO1:
                if (HIWORD(wParam) == CBN_SELCHANGE) {
                    int sel = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                    HWND hList = GetDlgItem(hDlg, IDC_LIST1);
                    HWND hCombo = GetDlgItem(hDlg, IDC_COMBO1);
                    int index = (int)SendMessage(hCombo, CB_GETCURSEL, 0, 0);

                    SendMessage(hList, LB_RESETCONTENT, 0, 0);

                    switch (index) {
                    case 0:
                        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Статические фигуры");
                        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Осциллирующие фигуры");
                        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Космические корабли");
                        break;
                    case 1:
                        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Правила");
                        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Rule 30");
                        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Rule 90");
                        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"Rule 110");
                        break;
                    }
                }
                break;

            case IDC_LIST1:
                if (HIWORD(wParam) == LBN_SELCHANGE) {
                    int sel = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);
                    // обработка выбора sel
                }
                break;

            case IDOK:
            case IDCANCEL:
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;

    }
    return (INT_PTR)FALSE;
}
