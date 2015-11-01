#include <Windows.h>
#include "resource.h"
#include <CommCtrl.h>

BOOL CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

HWND hDlg;
HINSTANCE hInst;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmpLine, int nCmdShow)
{
    MSG msg;
    hInst = hInstance;
    hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
    ShowWindow(hDlg, nCmdShow);
    UpdateWindow(hDlg);
    while(GetMessage(&msg, 0, 0, 0))
    {        
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
TCHAR buff[256];
HICON hIcon;
HMENU hMenu;
BOOL CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {        
    case WM_INITDIALOG:
        // Загрузка иконки из ресурса
        hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));                
        // Задание иконки для диалогового окна
        SendMessage(hWnd, WM_SETICON, ICON_BIG, LPARAM(hIcon));
        
        hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
        SetMenu(hWnd, hMenu);
        
        // Заполнение списка данными
        SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, 0, LPARAM(TEXT("FIRST")));

        
        return TRUE;
    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
            case IDC_BUTTON1:
                GetDlgItemText(hDlg, IDC_EDIT1, buff, 255);
                SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, 0, LPARAM(buff));
                return TRUE;
            }
            
        }
        return TRUE;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        PostQuitMessage(0);
        return TRUE;
    }
    return FALSE;
}

