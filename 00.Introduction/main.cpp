#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance,     // Дискриптор окна
                   HINSTANCE hPrevInstance, // Не используется
                   LPSTR lpCmdLine,         // Аргументы командной строки
                   int nCmdShow)            // 
{
    MessageBox( NULL, 
                L"Привет, Мир", 
                L"Диалоговое окно", 
                MB_OK);
    return 0;
}