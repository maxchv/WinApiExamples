#include <Windows.h>
#include <iostream>
#pragma warning (disable: 4996)
using namespace std;


int main()
{
    // Основные типы данных
    BOOL  _bool;    //  int
    BYTE  byte;     //  unsigned char
    DWORD dword;    //  unsigned long
    WORD  word;     //  unsigned short
    INT   _int;     //  int
    UINT  uint;     //  unsigned int
    LONG  _long;    //  long
    
    // Дескрипторные типы данных
    HANDLE  h;          // Дескриптор объекта
    HBITMAP hBitmap;    // Дескриптор растрового изображения
    HBRUSH  hBrush;     // Дескриптор кисти
    HCURSOR hCursor;    // Дескриптор курсора
    HDC     hDc;        // Дескриптор контекста устройства
    HFONT   hFont;      // Дескриптор шрифта
    HICON   hIcon;      // Дескриптор иконки
    HINSTANCE hInstance;// Дескриптор экземпляра приложения
    HMENU   hMenu;      // Дескриптор меню
    HPEN    hPen;       // Дескриптор пера
    HWND    hWnd;       // Дескриптор окна
    COLORREF colRef;

    // Строковые типы данных
    char     str[30];
    wchar_t wstr[30];
    TCHAR   tstr[30];

    cout << sizeof(str) << endl;
    cout << sizeof(wstr) << endl;

    // Константные указатели
    LPCSTR  lpcString = "This is char string";
    LPCWSTR lpcwString = L"This is UNICODE string";
    cout << lpcString << endl;
    wcout << lpcwString << endl;

    // Указатели
    LPSTR   lpString = const_cast<LPSTR>(lpcString);
    LPWSTR  lpwString = const_cast<LPWSTR>(lpcwString);
    cout << lpString << endl;
    wcout << lpwString << endl;

    // Сравнение функций по работе со строками и с UNICODE
    strcpy(str, lpcString);
    wcscpy(wstr, lpcwString);
    
    cout << str << endl;
    wcout << wstr << endl;

    cout << strlen(str) << endl;
    cout << wcslen(wstr) << endl;

    // Отдавать предпочтение стоит функциям операционной системы
    cout << lstrlen(wstr) << endl;

    // Вспомогательные типы данных
    LPARAM  lParam; // long Param
    WPARAM  wParam; // word parameter
    LRESULT lResutl;// результат возвращаемый оконной процедурой

    // Венгерская нотация
    // b - логический
    // i - целое число (индекс)
    // n - целое (количество)
    // u - целое без знака
    // d - число с двойной точностью
    // sz - строка (string zero)
    // p - указатель
    // lp - длинный указатель
    // a - массив
    // lpfn - длинный указатель на функцию
    // h - дескриптор
    // cb - счетчик байт
    // С - класс

    return 0;
}