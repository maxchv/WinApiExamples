#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("WindowsApp");

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCommandLine,
                   int nCommandShow)
{
    
    //MessageBox(NULL, TEXT("Work"), TEXT("Is it work?"), MB_OK);
    // ������� ���������� ����
    HWND hMainWind;

    // ������� ����� ����
    WNDCLASSEX wc; 
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW; // CS - Class Style
    wc.lpfnWndProc = WindowProc;
    wc.cbWndExtra = 0;
    wc.cbClsExtra = 0;
    // ��������� ����������
    wc.hInstance = hInstance;
    // ���������� ����������� ������
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    // ����� ������
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    // ������
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // ���� ���� ����
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    // ���� ���
    wc.lpszMenuName = NULL;
    // ��� ������ ����
    wc.lpszClassName = szClassWindow;
    

    // �������������� �����
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, TEXT("�� ���������� ���������������� �����"), 
            TEXT("������"), MB_OK | MB_ICONERROR);
        return NULL;
    }

    // ������� ����
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
         MessageBox(NULL, TEXT("�� ���������� ������� ����"), 
            TEXT("������"), MB_OK | MB_ICONERROR);
        return NULL;
    }

    // �������� ���� �� �����
    ShowWindow(hMainWind, nCommandShow);
    UpdateWindow(hMainWind); // ����������� ����

    MSG lpMsg;
    while (GetMessage(&lpMsg, NULL, 0, 0))
    {
        TranslateMessage(&lpMsg);   //  ���������� ���������
        DispatchMessage(&lpMsg);    //  ��������������� ���������
    }

    // ���������� ��������� ��� ������� ��� ��� ������
    return lpMsg.wParam;
}

LPARAM CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    
    switch (uMessage)
    {
    case WM_DESTROY:    // ��������� � ���������� ���������
        PostQuitMessage(0); // ������� ��������� WM_QUIT
        break;
    default:
        return DefWindowProc(hWnd, uMessage, wParam, lParam);
        break;
    }
    return 0;
}
