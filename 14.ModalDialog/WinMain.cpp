#include "resource.h"
#include <Windows.h>

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrewInstance,
                     LPSTR lpszCmdLine,
                     int nCmdShow)
{
    hInst = hInstance;
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

HWND btn;
HWND stat;
BOOL CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        stat = CreateWindow(TEXT("Static"), TEXT(""), 
            WS_CHILD | WS_BORDER | WS_VISIBLE,
            10, 10, 100, 50, hWnd, NULL, hInst, NULL);
        btn = CreateWindow(TEXT("Button"), TEXT("Button"),
            WS_CHILD | WS_BORDER | SS_CENTER | WS_VISIBLE, 
            10, 70, 100, 50, hWnd, (HMENU)101, hInst, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 101:
            //MessageBox(hWnd, TEXT("Catch"), TEXT(""), 0);
            SetWindowText(stat, TEXT("test"));
            break;
        case IDOK:
            EndDialog(hWnd, 0);
            break;
        default:
            break;
        }
        break;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    default:
        return FALSE;
    }
    return FALSE;
}