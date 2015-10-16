// 07.UsingMouse.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "07.UsingMouse.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szTitle[MAX_LOADSTRING];					// ����� ������ ���������
TCHAR szWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���������� ��� �����.
	MSG msg;
	HACCEL hAccelTable;

	// ������������� ���������� �����
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY07USINGMOUSE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY07USINGMOUSE));

	// ���� ��������� ���������:
	while (GetMessage(&msg, NULL, 0, 0))
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
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
    // CS_DBLCLKS - ��� ������������ ��������� ������� ������
    wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY07USINGMOUSE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY07USINGMOUSE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
//
//

//  ��������� 
TCHAR *msg_left = TEXT("����� ������ ������");
TCHAR *msg_middle = TEXT("������� ������ ������");
TCHAR *msg_right = TEXT("������ ������ ������");

#ifdef UNICODE
wstringstream buff;
#else
stringstream buff;
#endif

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
    
    int x, y;    
    DWORD style;    // ����� ����

	switch (message)
	{
    // ��������� ��� �������� ����
    case WM_CREATE:
        // ����� ��������� ����� ���� ����� ������� SetClassLong
        style = GetClassLong(hWnd, GCL_STYLE); 
        SetClassLong(hWnd, GCL_STYLE, style | CS_DBLCLKS);
        break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
    // ������� ������� ����� ������ ����
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam); // ���������� ����
        y = HIWORD(lParam);
        hdc = GetDC(hWnd);  // ������� ����������
        TextOut(hdc, x, y, msg_left, lstrlen(msg_left));
        ReleaseDC(hWnd, hdc);
        break;
    // ������� ������� ������� ������ ����
    case WM_MBUTTONDOWN:
        x = LOWORD(lParam); // ���������� ����
        y = HIWORD(lParam);
        hdc = GetDC(hWnd);  // ������� ����������
        TextOut(hdc, x, y, msg_middle, lstrlen(msg_middle));
        ReleaseDC(hWnd, hdc);
        break;
    // ������� ������� ������ ������ ����
    case WM_RBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        hdc = GetDC(hWnd);
        TextOut(hdc, x, y, msg_right, lstrlen(msg_right));
        ReleaseDC(hWnd, hdc);
        break;
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_LBUTTONUP:
        InvalidateRect(hWnd, NULL, true); // �������������� ���� ��� ���������� ����
        break;
    // ������� ���� ����������� ���� � ����� ������ ����� ���������� ���� 
    // CS_DBLCLICK
    case WM_RBUTTONDBLCLK:
        buff.str(TEXT(""));
        buff.clear();
        buff << TEXT("������� ���� ������ ������� ����");
        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_LBUTTONDBLCLK:
        buff.str(TEXT(""));
        buff.clear();
        buff << TEXT("������� ���� ����� ������� ����");
        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_MOUSEMOVE:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        buff.str(TEXT(""));
        buff.clear();
        buff << TEXT("X: ") << x << TEXT(" Y: ") << y;
        SetWindowText(hWnd, buff.str().data());
        break;
    case WM_MOUSEWHEEL:
        buff.str(TEXT(""));
        buff.clear();
        buff << TEXT("����� �������");
        InvalidateRect(hWnd, NULL, true);
        break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 0, 0, buff.str().data(), buff.str().size());
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���������� ��������� ��� ���� "� ���������".
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
