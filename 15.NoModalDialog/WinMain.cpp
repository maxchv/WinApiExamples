#include <Windows.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrewInstance,
                     LPSTR lpszCmdLine,
                     int nCmdShow)
{
    MSG msg;
    HWND dlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);

    ShowWindow(dlg, nCmdShow);

    while(GetMessage(&msg, 0, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
    switch (msg)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        case IDCANCEL:
            DestroyWindow(hWnd);
            break;
        case IDC_BUTTON1:            
            if(h)
            {
                SendMessage(h, WM_CLOSE, NULL, NULL);
            }
            break;
         case IDC_BUTTON2:            
            if(h)
            {
                PostMessage(h, WM_CLOSE, NULL, NULL);
            }
            break;
        case IDC_BUTTON3:            
            if(h)
            {
                SendMessage(h, WM_QUIT, NULL, NULL);
            }
            break;
         case IDC_BUTTON4:            
            if(h)
            {
                PostMessage(h, WM_QUIT, NULL, NULL);
            }
            break;
        default:
            break;
        }
        return TRUE;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        return TRUE;
    case WM_DESTROY:
        PostQuitMessage(0);
        return TRUE;
    }
    return FALSE;
}