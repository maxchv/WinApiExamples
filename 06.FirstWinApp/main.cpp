#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("WindowsApp");

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCommandLine,
                   int nCommandShow)
{
    
    //MessageBox(NULL, TEXT("Work"), TEXT("Is it work?"), MB_OK);
    // Создать дескриптор окна
    HWND hMainWind;

    // Описать класс окна
    WNDCLASSEX wc; 
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW; // CS - Class Style
    wc.lpfnWndProc = WindowProc;
    wc.cbWndExtra = 0;
    wc.cbClsExtra = 0;
    // Экземпляр приложения
    wc.hInstance = hInstance;
    // Загружамем стандартную иконку
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    // Малая иконка
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    // Курсор
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // Цвет фона окна
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    // Меню нет
    wc.lpszMenuName = NULL;
    // Имя класса окна
    wc.lpszClassName = szClassWindow;
    

    // Регистрировать класс
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("Не получилось зарегестрировать класс"), 
            TEXT("Ошибка"), MB_OK | MB_ICONERROR);
        return NULL;
    }

    // Создать окно
    hMainWind = CreateWindow(szClassWindow, 
                             TEXT("Simple App"), 
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             NULL,
                             NULL,
                             hInstance,
                             NULL);
    if(!hMainWind)
    {
         MessageBox(NULL, TEXT("Не получилось создать окно"), 
            TEXT("Ошибка"), MB_OK | MB_ICONERROR);
        return NULL;
    }

    // Показать окно на экран
    ShowWindow(hMainWind, nCommandShow);
    UpdateWindow(hMainWind); // перерисовка окна

    MSG lpMsg;
    while (GetMessage(&lpMsg, NULL, 0, 0))
    {
        TranslateMessage(&lpMsg);   //  Трансляция сообщений
        DispatchMessage(&lpMsg);    //  Диспетчеризация сообщений
    }

    // Возвратить результат при неудаче или при выходе
    return lpMsg.wParam;
}

LPARAM CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hDC; // Дескриптор ориентации текста на экране
    PAINTSTRUCT ps; // структура определяющая клиентскую область (размеры, цвет и т.д.)
    RECT rect; // размер клиентской области
    COLORREF colorText = RGB(255, 0, 0); // цвет текста
    switch (uMessage)
    {
    case WM_CREATE:
        break;
    case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rect);
        SetTextColor(hDC, colorText);
        DrawText(hDC, TEXT("Text"), -1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:    // Сообщение о завершении программы
        PostQuitMessage(0); // Посылка сообщения WM_QUIT
        break;
    default:
        return DefWindowProc(hWnd, uMessage, wParam, lParam);
        break;
    }
    return 0;
}
