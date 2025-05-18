#include "game_windows.h"
#include "grid_logic.h"
#include <commdlg.h> // для диалога выбора цвета
#include <commctrl.h>  // для трекбара по частоте обновления экрана

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
    wcex.lpszMenuName = NULL;
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
    wcex.lpszMenuName = NULL;
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

LRESULT CALLBACK WndProc2D(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        TCHAR buffer[256];
        LoadString(hInst, IDC_GAME_2D, buffer, sizeof(buffer) / sizeof(TCHAR));
        CreateWindowW(
            L"STATIC", buffer, WS_CHILD | WS_VISIBLE,
            50, 10, 120, 20, hWnd, NULL, hInst, NULL);
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
        CreateWindow(L"BUTTON", L"Step",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 250, 150, 30,
            hWnd, (HMENU)ID_STEP2D_BUTTON, hInst, NULL);

        // кнопки смены цвета
        CreateWindow(L"BUTTON", L"Change ALIVE",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 290, 150, 30,
            hWnd, (HMENU)ID_ALIVE_COLOR2D_BUTTON, hInst, NULL);
        CreateWindow(L"BUTTON", L"Change DEAD",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 320, 150, 30,
            hWnd, (HMENU)ID_DEAD_COLOR2D_BUTTON, hInst, NULL);
        CreateWindow(L"BUTTON", L"Change BORDER",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 350, 150, 30,
            hWnd, (HMENU)ID_BORDER_COLOR2D_BUTTON, hInst, NULL);

        // радиогруппа режима отрисовки
        CreateWindowW(L"BUTTON", L"Режим true",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
            1100, 390, 150, 30, hWnd, (HMENU)ID_RADIO_PAINT_STYLE_1_2D, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Режим OR",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            1100, 420, 150, 30, hWnd, (HMENU)ID_RADIO_PAINT_STYLE_OR_2D, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Режим XOR",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            1100, 450, 150, 30, hWnd, (HMENU)ID_RADIO_PAINT_STYLE_XOR_2D, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Режим false",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            1100, 480, 150, 30, hWnd, (HMENU)ID_RADIO_PAINT_STYLE_0_2D, hInst, NULL);
        CheckRadioButton(hWnd, ID_RADIO_PAINT_STYLE_1_2D, ID_RADIO_PAINT_STYLE_0_2D, ID_RADIO_PAINT_STYLE_1_2D);

        //чекбокс для границ
        CreateWindowW(L"BUTTON", L"Показать сетку",
            WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
            1100, 520, 150, 30, hWnd, (HMENU)ID_CHECK_BORDER_2D, hInst, NULL);
        if (cellBorder2D) CheckDlgButton(hWnd, ID_CHECK_BORDER_2D, BST_CHECKED);

        //трекбары
        hTrackbarFps2D = CreateWindowEx(
            0, TRACKBAR_CLASS, L"Trackbar",
            WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
            1100, 580, 150, 30, hWnd, (HMENU)ID_TRACK_FPS_2D, hInst, NULL);

        //инициализация трекбара
        SendMessage(hTrackbarFps2D, TBM_SETRANGE, TRUE, MAKELPARAM(1, 100)); // от 1 до 100
        SendMessage(hTrackbarFps2D, TBM_SETPOS, TRUE, fps2D);

        //текст рядом с трекбаром
        
        hTrackbar2DLabel = CreateWindow(
            L"STATIC", L"", WS_CHILD | WS_VISIBLE,
            1260, 580, 60, 20, hWnd, NULL, hInst, NULL);
        TCHAR buf[32];
        wsprintf(buf, L"FPS: %d", fps2D);
        SetWindowText(hTrackbar2DLabel, buf);

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
        {
            SetTimer(hWnd, 2, 1000/fps2D, NULL);
            timer2D = true; // храним состояние таймера
        }
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
        {
            KillTimer(hWnd, 2);
            timer2D = false; //таймер - все
        }
        break;
        case ID_STEP2D_BUTTON:
        {
            UpdateGrid2D();
            InvalidateRect(hChild2D, NULL, FALSE);
        }
        break;
        case ID_ALIVE_COLOR2D_BUTTON:
        {
            ShowColorDialog(hWnd, &colorAlive2D, &hBrushAlive2D);
        }
        break;
        case ID_DEAD_COLOR2D_BUTTON:
        {
            ShowColorDialog(hWnd, &colorDead2D, &hBrushDead2D);
        }
        case ID_BORDER_COLOR2D_BUTTON:
        {
            ShowColorDialogPen(hWnd, &colorDead2D, &hPenBorder2D);
            SelectObject(hdcMem2D, hPenBorder2D);
        }
        break;
        case ID_RADIO_PAINT_STYLE_1_2D:
            paintStyle2D = 1;
            break;
        case ID_RADIO_PAINT_STYLE_OR_2D:
            paintStyle2D = 2;
            break;
        case ID_RADIO_PAINT_STYLE_XOR_2D:
            paintStyle2D = 3;
            break;
        case ID_RADIO_PAINT_STYLE_0_2D:
            paintStyle2D = 4;
            break;
        case ID_CHECK_BORDER_2D:
        {
            cellBorder2D = !cellBorder2D;
            InvalidateRect(hChild2D, NULL, FALSE);
        }

        break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_HSCROLL:
        if ((HWND)lParam == hTrackbarFps2D) {
            fps2D = SendMessage(hTrackbarFps2D, TBM_GETPOS, 0, 0);
            TCHAR buf[32];
            wsprintf(buf, L"FPS: %d", fps2D);
            SetWindowText(hTrackbar2DLabel, buf);
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
    case WM_CLOSE:
    {
        int result = DialogBoxW(hInst, MAKEINTRESOURCE(IDD_EXIT_CONFIRM), hWnd, ExitConfirmDialogProc);
        if (result == IDYES) {
            DestroyWindow(hWnd);
        }
    }
    break;
    case WM_DESTROY:
    {   
        KillTimer(hWnd, 2);
        able_to_create_win2d = 1;
    }
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
        TCHAR buffer[256];
        LoadString(hInst, IDC_GAME_1D, buffer, sizeof(buffer) / sizeof(TCHAR));
        CreateWindowW(
            L"STATIC", buffer, WS_CHILD | WS_VISIBLE,
            50, 10, 120, 20, hWnd, NULL, hInst, NULL);
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
        CreateWindow(L"BUTTON", L"Step",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 250, 150, 30,
            hWnd, (HMENU)ID_STEP1D_BUTTON, hInst, NULL);

        // кнопки смены цвета
        CreateWindow(L"BUTTON", L"Change ALIVE",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 290, 150, 30,
            hWnd, (HMENU)ID_ALIVE_COLOR1D_BUTTON, hInst, NULL);
        CreateWindow(L"BUTTON", L"Change DEAD",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 320, 150, 30,
            hWnd, (HMENU)ID_DEAD_COLOR1D_BUTTON, hInst, NULL);
        CreateWindow(L"BUTTON", L"Change BORDER",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1100, 350, 150, 30,
            hWnd, (HMENU)ID_BORDER_COLOR1D_BUTTON, hInst, NULL);

        // радиогруппа режима отрисовки
        CreateWindowW(L"BUTTON", L"Режим true",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
            1100, 390, 150, 30, hWnd, (HMENU)ID_RADIO_PAINT_STYLE_1_1D, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Режим OR",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            1100, 420, 150, 30, hWnd, (HMENU)ID_RADIO_PAINT_STYLE_OR_1D, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Режим XOR",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            1100, 450, 150, 30, hWnd, (HMENU)ID_RADIO_PAINT_STYLE_XOR_1D, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Режим false",
            WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
            1100, 480, 150, 30, hWnd, (HMENU)ID_RADIO_PAINT_STYLE_0_1D, hInst, NULL);
        CheckRadioButton(hWnd, ID_RADIO_PAINT_STYLE_1_1D, ID_RADIO_PAINT_STYLE_0_1D, ID_RADIO_PAINT_STYLE_1_1D);

        //чекбокс для границ
        CreateWindowW(L"BUTTON", L"Показать сетку",
            WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
            1100, 520, 150, 30, hWnd, (HMENU)ID_CHECK_BORDER_1D, hInst, NULL);
        if (cellBorder1D) CheckDlgButton(hWnd, ID_CHECK_BORDER_1D, BST_CHECKED);

        //трекбары
        hTrackbarFps1D = CreateWindowEx(
            0, TRACKBAR_CLASS, L"Trackbar",
            WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
            1100, 580, 150, 30, hWnd, (HMENU)ID_TRACK_FPS_1D, hInst, NULL);

        //инициализация трекбара
        SendMessage(hTrackbarFps1D, TBM_SETRANGE, TRUE, MAKELPARAM(1, 100)); // от 1 до 100
        SendMessage(hTrackbarFps1D, TBM_SETPOS, TRUE, fps1D);

        //текст рядом с трекбаром

        hTrackbar1DLabel = CreateWindowW(
            L"STATIC", L"", WS_CHILD | WS_VISIBLE,
            1260, 580, 60, 20, hWnd, NULL, hInst, NULL);
        TCHAR buf[32];
        wsprintf(buf, L"FPS: %d", fps1D);
        SetWindowText(hTrackbar1DLabel, buf);

        // поле ввода правил c текстом
        hRule1DLabel = CreateWindowW(
            L"STATIC", L"Номер правила", WS_CHILD | WS_VISIBLE,
            1260, 50, 120, 20, hWnd, NULL, hInst, NULL);
        hRule1DEdit = CreateWindowW(
            L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
            1260, 80, 120, 30, hWnd, (HMENU)ID_RULE_1D_EDIT, hInst, NULL);
        CreateWindow(L"BUTTON", L"Ввод правила",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            1260, 120, 120, 30,
            hWnd, (HMENU)ID_RULE1D_BUTTON, hInst, NULL);
        hCurrRule1DLabel = CreateWindowW(
            L"STATIC", L"", WS_CHILD | WS_VISIBLE,
            1260, 150, 120, 40, hWnd, NULL, hInst, NULL);
        wsprintf(buf, L"Текцщее правило: %d", rule1D);
        SetWindowText(hCurrRule1DLabel, buf);

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
            SetTimer(hWnd, 1, 1000/fps1D, NULL);
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
        case ID_STEP1D_BUTTON:
        {
            UpdateGrid1D();
            InvalidateRect(hChild1D, NULL, FALSE);
        }
        break;
        case ID_ALIVE_COLOR1D_BUTTON:
        {
            ShowColorDialog(hWnd, &colorAlive1D, &hBrushAlive1D);
        }
        break;
        case ID_DEAD_COLOR1D_BUTTON:
        {
            ShowColorDialog(hWnd, &colorDead1D, &hBrushDead1D);
        }
        case ID_BORDER_COLOR1D_BUTTON:
        {
            ShowColorDialogPen(hWnd, &colorDead1D, &hPenBorder1D);
            SelectObject(hdcMem1D, hPenBorder1D);
        }
        break;
        case ID_RULE1D_BUTTON:
        {
            TCHAR buf[128] = { 0 };

            GetWindowText(hRule1DEdit, buf, 128);

            int value = 0;
            wchar_t* endPtr;
            value = (int)wcstol(buf, &endPtr, 10);

            if (endPtr == buf || *endPtr != '\0') {
                MessageBox(hWnd, L"Введите корректное число!", L"Ошибка", MB_ICONERROR);
            }
            else {
                if (value >= 0 && value < 256) {
                    rule1D = value;
                    wsprintf(buf, L"Текцщее правило: %d", rule1D);
                    SetWindowText(hCurrRule1DLabel, buf);
                }
                else MessageBox(hWnd, L"Введите корректное число!", L"Ошибка", MB_ICONERROR);
            }
        }
        break;
        case ID_RADIO_PAINT_STYLE_1_1D:
            paintStyle1D = 1;
            break;
        case ID_RADIO_PAINT_STYLE_OR_1D:
            paintStyle1D = 2;
            break;
        case ID_RADIO_PAINT_STYLE_XOR_1D:
            paintStyle1D = 3;
            break;
        case ID_RADIO_PAINT_STYLE_0_1D:
            paintStyle1D = 4;
            break;
        case ID_CHECK_BORDER_1D:
        {
            cellBorder1D = !cellBorder1D;
            InvalidateRect(hChild1D, NULL, FALSE);
        }
        break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_HSCROLL:
        if ((HWND)lParam == hTrackbarFps1D) {
            fps1D = SendMessage(hTrackbarFps1D, TBM_GETPOS, 0, 0);
            TCHAR buf[32];
            wsprintf(buf, L"FPS: %d", fps1D);
            SetWindowText(hTrackbar1DLabel, buf);
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
    case WM_CLOSE:
    {
        int result = DialogBoxW(hInst, MAKEINTRESOURCE(IDD_EXIT_CONFIRM), hWnd, ExitConfirmDialogProc);
        if (result == IDYES) {
            DestroyWindow(hWnd);
        }
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
        hBrushDead2D = CreateSolidBrush(colorDead2D);
        hBrushAlive2D = CreateSolidBrush(colorAlive2D);
        //карандашей с подключением к hdc
        hPenBorder2D = CreatePen(PS_SOLID, 2, colorBorder2D);
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

        // создание контекстного меню под добавление фигнур
        hContextMenu2D = LoadMenu(hInst, MAKEINTRESOURCE(IDR_CONTEXTMENU_2D));
        

    }
    break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam)) {
            case ID_MENU_STATIC_FIG1:
            {
                DrawFromTemplate(pointPaint2D, block);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_STATIC_FIG2:
            {
                DrawFromTemplate(pointPaint2D, beehive);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_STATIC_FIG3:
            {
                DrawFromTemplate(pointPaint2D, loaf);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_STATIC_FIG4:
            {
                DrawFromTemplate(pointPaint2D, boat);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_STATIC_FIG5:
            {
                DrawFromTemplate(pointPaint2D, tub);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_OSC_FIG1:
            {
                DrawFromTemplate(pointPaint2D, blinker);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_OSC_FIG2:
            {
                DrawFromTemplate(pointPaint2D, toad);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_OSC_FIG3:
            {
                DrawFromTemplate(pointPaint2D, beacon);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_OSC_FIG4:
            {
                DrawFromTemplate(pointPaint2D, pulsar);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_SPACE_FIG1:
            {
                DrawFromTemplate(pointPaint2D, glider);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_SPACE_FIG2:
            {
                DrawFromTemplate(pointPaint2D, lwss);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_SPACE_FIG3:
            {
                DrawFromTemplate(pointPaint2D, mwss);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            case ID_MENU_SPACE_FIG4:
            {
                DrawFromTemplate(pointPaint2D, hwss);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            break;
            default:
                break;
        }
    }
    break;
    case WM_MOUSEMOVE:
    {
        if (paintAble2D) {
            POINT pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);

            // изменение состояния клетки, в данном случае все закрасим белим
            if (paintStyle2D == 1) grid2D[(scaledScrollPosY2D + pt.y / scale2D) / cellSize2D][(scaledScrollPosX2D + pt.x / scale2D) / cellSize2D] = true;
            else if(paintStyle2D == 2) grid2D[(scaledScrollPosY2D + pt.y / scale2D) / cellSize2D][(scaledScrollPosX2D + pt.x / scale2D) / cellSize2D] = true;
            else if (paintStyle2D == 3) grid2D[(scaledScrollPosY2D + pt.y / scale2D) / cellSize2D][(scaledScrollPosX2D + pt.x / scale2D) / cellSize2D] = grid2D[(scaledScrollPosY2D + pt.y / scale2D) / cellSize2D][(scaledScrollPosX2D + pt.x / scale2D) / cellSize2D] ^ true;
            else grid2D[(scaledScrollPosY2D + pt.y / scale2D) / cellSize2D][(scaledScrollPosX2D + pt.x / scale2D) / cellSize2D] = false;
            InvalidateRect(hWnd, nullptr, FALSE);
        }
    }
    break;
    case WM_RBUTTONDOWN:
    {
        // вызов контекстного меню

        POINT pt;

        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        pointPaint2D = pt;
        // получаем координаты для отрисвоки фигуры(в понимании сетки)
        pointPaint2D.y = (scaledScrollPosY2D + pt.y / scale2D) / cellSize2D;
        pointPaint2D.x = (scaledScrollPosX2D + pt.x / scale2D) / cellSize2D;

        ClientToScreen(hWnd, &pt);

        HMENU hSubMenu2D = GetSubMenu(hContextMenu2D, 0); // берем первый POPUP

        if (hSubMenu2D) {
            SetForegroundWindow(hWnd);  // обязательно!
            TrackPopupMenu(hSubMenu2D, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
        }
    }
    break;
    case WM_LBUTTONUP:
    {
        paintAble2D = false;
    }
    break;
    case WM_LBUTTONDOWN:
    {
        if (!timer2D) {
            paintAble2D = true;

            POINT pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            // изменение состояния клетки, в данном случае все закрасим белим
            if (paintStyle2D == 1) grid2D[(scaledScrollPosY2D + pt.y / scale2D) / cellSize2D][(scaledScrollPosX2D + pt.x / scale2D) / cellSize2D] = true;
            else if (paintStyle2D == 2) grid2D[(scaledScrollPosY2D + pt.y / scale2D) / cellSize2D][(scaledScrollPosX2D + pt.x / scale2D) / cellSize2D] = true;
            else if (paintStyle2D == 3) grid2D[(scaledScrollPosY2D + pt.y / scale2D) / cellSize2D][(scaledScrollPosX2D + pt.x / scale2D) / cellSize2D] = grid2D[(scaledScrollPosY2D + pt.y / scale2D) / cellSize2D][(scaledScrollPosX2D + pt.x / scale2D) / cellSize2D] ^ true;
            else grid2D[(scaledScrollPosY2D + pt.y / scale2D) / cellSize2D][(scaledScrollPosX2D + pt.x / scale2D) / cellSize2D] = false;
            InvalidateRect(hWnd, nullptr, FALSE);
        }
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
            scale2D = min(max(scale2D, 1.0), 3.0);
            scaled2DHeight = (int)(field2DHeight / scale2D);
            scaled2DWidth = (int)(field2DWidth / scale2D);
            scaledChild2DHeight = (int)(ChildHeight2D / scale2D);
            scaledChild2DWidth = (int)(ChildWidth2D / scale2D);
            scaledScrollPosX2D = (int)(scrollPosX2D / scale2D);
            scaledScrollPosY2D = (int)(scrollPosY2D / scale2D);

            // обработка позиции скролингов

            // Установим параметры для вертикального скролла
            SCROLLINFO si_vert = { sizeof(si_vert) };
            si_vert.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
            si_vert.nMin = 0;
            si_vert.nMax = field2DHeight - 1;        // Устанавливаем максимальное значение
            si_vert.nPage = scaledChild2DHeight;        // Устанавливаем видимую область
            si_vert.nPos = 0;           // Начальная позиция

            SetScrollInfo(hWnd, SB_VERT, &si_vert, TRUE);  // Устанавливаем параметры

            // Установим параметры для горизонтального скролла
            SCROLLINFO si_horz = { sizeof(si_horz) };
            si_horz.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
            si_horz.nMin = 0;
            si_horz.nMax = field2DWidth - 1;        // Устанавливаем максимальное значение
            si_horz.nPage = scaledChild2DWidth;        // Устанавливаем видимую область
            si_horz.nPos = 0;           // Начальная позиция

            SetScrollInfo(hWnd, SB_HORZ, &si_horz, TRUE);  // Устанавливаем параметры

            InvalidateRect(hWnd, nullptr, FALSE);

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
    case WM_MOUSEMOVE:
    {
        if (paintAble1D) {
            POINT pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            int cellX = (int)((scaledScrollPosX1D + pt.x / scale1D) / cellSize1D);
            int cellY = (int)((scaledScrollPosY1D + pt.y / scale1D) / cellSize1D);
            int index = cellY * cellCount1D + cellX;
            // изменение состояния клетки, в данном случае все закрасим белим
            if (paintStyle1D == 1) grid1D[index] = true;
            else if (paintStyle1D == 2) grid1D[index] = true;
            else if (paintStyle1D == 3) grid1D[index] = grid1D[index] ^ true;
            else grid1D[index] = false;
            InvalidateRect(hWnd, nullptr, FALSE);
        }
    }
    break;
    case WM_RBUTTONDOWN:
    {
        // в будущем мб здесь добавление фигур из 1 мерной игры
    }
    break;
    case WM_LBUTTONUP:
    {
        paintAble1D = false;
    }
    break;
    case WM_LBUTTONDOWN:
    {
        if (!timer1D) {
            paintAble1D = true;

            POINT pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            int cellX = (int)((scaledScrollPosX1D + pt.x / scale1D) / cellSize1D);
            int cellY = (int)((scaledScrollPosY1D + pt.y / scale1D) / cellSize1D);
            int index = cellY * cellCount1D + cellX;
            // изменение состояния клетки, в данном случае все закрасим белим
            if (paintStyle1D == 1) grid1D[index] = true;
            else if (paintStyle1D == 2) grid1D[index] = true;
            else if (paintStyle1D == 3) grid1D[index] = grid1D[index] ^ true;
            else grid1D[index] = false;
            InvalidateRect(hWnd, nullptr, FALSE);
        }
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
            scaledScrollPosX1D = (int)(scrollPosX1D / scale1D);
            SetScrollPos(hWnd, SB_HORZ, scrollPosX1D, TRUE);
            InvalidateRect(hWnd, nullptr, FALSE);
        }
        else if (ctrlPressed) {
            scale1D += zDelta / 120 * 0.2;
            scale1D = min(max(scale1D, 1.0), 3.0);
            scaled1DHeight = (int)(field1DHeight / scale1D);
            scaled1DWidth = (int)(field1DWidth / scale1D);
            scaledChild1DHeight = (int)(ChildHeight1D / scale1D);
            scaledChild1DWidth = (int)(ChildWidth1D / scale1D);
            scaledScrollPosX1D = (int)(scrollPosX1D / scale1D);
            scaledScrollPosY1D = (int)(scrollPosY1D / scale1D);

            // обработка позиции скролингов

            // Установим параметры для вертикального скролла
            SCROLLINFO si_vert = { sizeof(si_vert) };
            si_vert.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
            si_vert.nMin = 0;
            si_vert.nMax = field1DHeight - 1;        // Устанавливаем максимальное значение
            si_vert.nPage = scaledChild1DHeight;        // Устанавливаем видимую область
            si_vert.nPos = 0;           // Начальная позиция

            SetScrollInfo(hWnd, SB_VERT, &si_vert, TRUE);  // Устанавливаем параметры

            // Установим параметры для горизонтального скролла
            SCROLLINFO si_horz = { sizeof(si_horz) };
            si_horz.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
            si_horz.nMin = 0;
            si_horz.nMax = field1DWidth - 1;        // Устанавливаем максимальное значение
            si_horz.nPage = scaledChild1DWidth;        // Устанавливаем видимую область
            si_horz.nPos = 0;           // Начальная позиция

            SetScrollInfo(hWnd, SB_HORZ, &si_horz, TRUE);  // Устанавливаем параметры

            InvalidateRect(hWnd, nullptr, FALSE);
        }
        else {
            scrollPosY1D -= zDelta / 120 * 10;
            scrollPosY1D = min(max(scrollPosY1D, 0), field1DHeight - ChildHeight1D);
            scaledScrollPosY1D = (int)(scrollPosY1D / scale1D);
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
        scaledScrollPosY1D = (int)(scrollPosY1D / scale1D);
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
        scaledScrollPosX1D = (int)(scrollPosX1D / scale1D);
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

        //переносим готовый буфер на экран
        StretchBlt(
            hdc1D,
            0, 0,
            ChildWidth1D,  // масштабируем ширину окна
            ChildHeight1D, // масштабируем высоту окна
            hdcMem1D,
            scaledScrollPosX1D, scaledScrollPosY1D,
            scaledChild1DWidth, scaledChild1DHeight,
            SRCCOPY
        );
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

void ShowColorDialog(HWND hWnd, COLORREF* color_to_change, HBRUSH* brush_to_change) {
    CHOOSECOLOR cc;

    static COLORREF acrCustClr[16];

    ZeroMemory(&cc, sizeof(cc));
    cc.lStructSize = sizeof(cc);
    cc.hwndOwner = hWnd;
    cc.lpCustColors = (LPDWORD)acrCustClr;
    cc.rgbResult = *color_to_change;
    cc.Flags = CC_FULLOPEN | CC_RGBINIT;

    if (ChooseColor(&cc) == TRUE) {
        *color_to_change = cc.rgbResult;
        if (*brush_to_change) {
            DeleteObject(*brush_to_change);
        }
        *brush_to_change = CreateSolidBrush(*color_to_change);
        InvalidateRect(hWnd, NULL, FALSE); // перерисовать окно
    }

    TCHAR msg[64];
    wsprintf(msg, L"Выбранный цвет: R=%d G=%d B=%d",
        GetRValue(*color_to_change),
        GetGValue(*color_to_change),
        GetBValue(*color_to_change));
    ShowColorInfo(hWnd, hInst, msg);
}

void ShowColorDialogPen(HWND hWnd, COLORREF* color_to_change, HPEN* pen_to_change) {
    CHOOSECOLOR cc;

    static COLORREF acrCustClr[16];

    ZeroMemory(&cc, sizeof(cc));
    cc.lStructSize = sizeof(cc);
    cc.hwndOwner = hWnd;
    cc.lpCustColors = (LPDWORD)acrCustClr;
    cc.rgbResult = *color_to_change;
    cc.Flags = CC_FULLOPEN | CC_RGBINIT;

    if (ChooseColor(&cc) == TRUE) {
        *color_to_change = cc.rgbResult;
        if (*pen_to_change) {
            DeleteObject(*pen_to_change);
        }
        *pen_to_change = CreatePen(PS_SOLID, 2, *color_to_change);
        InvalidateRect(hWnd, NULL, FALSE); // перерисовать окно
    }

    TCHAR msg[64];
    wsprintf(msg, L"Выбранный цвет: R=%d G=%d B=%d",
        GetRValue(*color_to_change),
        GetGValue(*color_to_change),
        GetBValue(*color_to_change));
    ShowColorInfo(hWnd, hInst, msg);
}

//функция обработки для диалогового окна выхода
INT_PTR CALLBACK ExitConfirmDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDYES:
        case IDNO:
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, IDNO); // по умолчанию - отказ
        return TRUE;
    }
    return FALSE;
}

//функция обрабюотки немодального диалога про цвет
INT_PTR CALLBACK ColorInfoDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        DestroyWindow(hDlg);
        hColorInfoDlg = NULL; // обязательно обнуляем!
        return TRUE;
    }
    return FALSE;
}


//Вывод информации о цвете

void ShowColorInfo(HWND hWndParent, HINSTANCE hInst, const TCHAR* msg) {
    if (!hColorInfoDlg || !IsWindow(hColorInfoDlg)) {
        hColorInfoDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_COLOR_INFO_DIALOG), hWndParent, ColorInfoDialogProc);
        ShowWindow(hColorInfoDlg, SW_SHOW);
    }
    SetDlgItemText(hColorInfoDlg, IDC_COLOR_TEXT, msg);
}
