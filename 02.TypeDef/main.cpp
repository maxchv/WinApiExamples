#include <Windows.h>
#include <iostream>
#pragma warning (disable: 4996)
using namespace std;


int main()
{
    // �������� ���� ������
    BOOL  _bool;    //  int
    BYTE  byte;     //  unsigned char
    DWORD dword;    //  unsigned long
    WORD  word;     //  unsigned short
    INT   _int;     //  int
    UINT  uint;     //  unsigned int
    LONG  _long;    //  long
    
    // ������������� ���� ������
    HANDLE  h;          // ���������� �������
    HBITMAP hBitmap;    // ���������� ���������� �����������
    HBRUSH  hBrush;     // ���������� �����
    HCURSOR hCursor;    // ���������� �������
    HDC     hDc;        // ���������� ��������� ����������
    HFONT   hFont;      // ���������� ������
    HICON   hIcon;      // ���������� ������
    HINSTANCE hInstance;// ���������� ���������� ����������
    HMENU   hMenu;      // ���������� ����
    HPEN    hPen;       // ���������� ����
    HWND    hWnd;       // ���������� ����
    COLORREF colRef;

    // ��������� ���� ������
    char     str[30];
    wchar_t wstr[30];
    TCHAR   tstr[30];

    cout << sizeof(str) << endl;
    cout << sizeof(wstr) << endl;

    // ����������� ���������
    LPCSTR  lpcString = "This is char string";
    LPCWSTR lpcwString = L"This is UNICODE string";
    cout << lpcString << endl;
    wcout << lpcwString << endl;

    // ���������
    LPSTR   lpString = const_cast<LPSTR>(lpcString);
    LPWSTR  lpwString = const_cast<LPWSTR>(lpcwString);
    cout << lpString << endl;
    wcout << lpwString << endl;

    // ��������� ������� �� ������ �� �������� � � UNICODE
    strcpy(str, lpcString);
    wcscpy(wstr, lpcwString);
    
    cout << str << endl;
    wcout << wstr << endl;

    cout << strlen(str) << endl;
    cout << wcslen(wstr) << endl;

    // �������� ������������ ����� �������� ������������ �������
    cout << lstrlen(wstr) << endl;

    // ��������������� ���� ������
    LPARAM  lParam; // long Param
    WPARAM  wParam; // word parameter
    LRESULT lResutl;// ��������� ������������ ������� ����������

    // ���������� �������
    // b - ����������
    // i - ����� ����� (������)
    // n - ����� (����������)
    // u - ����� ��� �����
    // d - ����� � ������� ���������
    // sz - ������ (string zero)
    // p - ���������
    // lp - ������� ���������
    // a - ������
    // lpfn - ������� ��������� �� �������
    // h - ����������
    // cb - ������� ����
    // � - �����

    return 0;
}