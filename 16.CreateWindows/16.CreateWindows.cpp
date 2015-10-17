// 16.CreateWindows.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "16.CreateWindows.h"
#include <commdlg.h>
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: разместите код здесь.
    MSG msg;
    HACCEL hAccelTable;

    // Инициализация глобальных строк
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_MY16CREATEWINDOWS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY16CREATEWINDOWS));

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= WndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY16CREATEWINDOWS));
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY16CREATEWINDOWS);
    wcex.lpszClassName	= szWindowClass;
    wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;

    hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

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

enum class WinType
{
    Static,
	StaticBitmap,
    Button,
	CheckBox,
    Edit,
    ComboBox
};


// https://en.wikibooks.org/wiki/Windows_Programming/User_Interface_Controls
#define ID_MYBUTTON 1

HBITMAP GetBitmap(HWND hWndParent)
{
	HBITMAP hBitmap = NULL;
	OPENFILENAME openfilename = { 0 };
	TCHAR szFileName[_MAX_PATH] = TEXT("");
	openfilename.lStructSize = sizeof(OPENFILENAME);
	openfilename.hwndOwner = hWndParent;
	openfilename.lpstrFile = szFileName;
	openfilename.lpstrFilter = TEXT("Bitmap images (*.bmp)\0*.bmp\0\0");
	openfilename.lpstrDefExt = TEXT("bmp");
	openfilename.nMaxFile = _MAX_FNAME;
	openfilename.lpstrFileTitle = TEXT("Укажите файл картинки");
	openfilename.Flags = OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&openfilename))
	{	
		hBitmap = (HBITMAP) LoadImage(NULL, szFileName, IMAGE_BITMAP,
					0, 0, LR_LOADFROMFILE);
	}
	
	return hBitmap;
}

HWND NewWindow(WinType type, POINT p, HWND hWnd)
{
    HWND h = NULL;
    switch (type)
    {
    case WinType::Static:
        h = CreateWindow(TEXT("STATIC"),
            TEXT("Static Winodw"),
			// Static style
			// https://msdn.microsoft.com/en-US/library/9h0ay857(v=vs.80).aspx
            WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT,
            p.x, p.y,100, 30, hWnd, NULL, hInst, NULL);
		// Set text
        SendMessage(h ,						/*HWND*/        /*Label*/
            WM_SETTEXT,						/*UINT*/        /*Message*/
            NULL,							/*WPARAM*/      /*Unused*/
            (LPARAM) TEXT("Hello Static")); /*LPARAM*/      /*Text*/
		// Set text
		SetWindowText(h, TEXT("Static text"));
        break;
	case WinType::StaticBitmap:
	{
		// http://zetcode.com/gui/winapi/controls/
		HBITMAP hBitmap = GetBitmap(hWnd);
		if (hBitmap)
		{			
			h = CreateWindow(TEXT("STATIC"), TEXT(""),
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_BITMAP,
				p.x, p.y, 300, 300, hWnd, NULL, hInst, NULL);
			SendMessage(h, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
		}
	}		
		break;
    case WinType::Button:
        h = CreateWindow(TEXT("BUTTON"),
            TEXT("Button"),
			// Button styles
			// https://msdn.microsoft.com/en-US/library/tf9hd91s(v=vs.80).aspx
            WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
            p.x, p.y,100, 30, hWnd, (HMENU)ID_MYBUTTON, hInst, NULL);
        break;
	case WinType::CheckBox:
	{
		h = CreateWindow(TEXT("BUTTON"), TEXT("CheckBox"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CHECKBOX,
			p.x, p.y, 100, 30, hWnd, (HMENU)3, hInst, NULL);
		// Set check
		CheckDlgButton(h, 3, BST_CHECKED);
		// Get is checked
		bool checked = IsDlgButtonChecked(h, 3);
	}
		break;
    case WinType::Edit:
        h = CreateWindow(TEXT("EDIT"),
            TEXT("Edit Winodw"),
			// Edit style
			// https://msdn.microsoft.com/en-US/library/6e36b89f(v=vs.80).aspx
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL | WS_VSCROLL | ES_MULTILINE,
            p.x, p.y,300, 250, hWnd, NULL, hInst, NULL);
        // Set the text.
        SendMessage(h, WM_SETTEXT, 0, (LPARAM)"Hello");
        {
        // Get the text.
        LRESULT iTextSize = SendMessage(h, EM_GETLIMITTEXT, 0, 0);
        char *szText = new char[iTextSize];
        SendMessage(h, WM_GETTEXT, iTextSize, (LPARAM)szText);
        }
        break;
    case WinType::ComboBox:
        h = CreateWindow(TEXT("COMBOBOX"), TEXT(""),
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS | CBS_AUTOHSCROLL,
            p.x, p.y, 150, 150, hWnd, NULL, hInst, NULL);
        // Add a list of strings to the combo box.

        SendMessage(
                    h,                            // The handle of the combo box
                    CB_ADDSTRING,                 // Tells the combo box to append this string to its list
                    0,                            // Not used, ignored.
                    (LPARAM) TEXT("Item A")             // The string to add.
            );

        SendMessage(h, CB_ADDSTRING, 0, (LPARAM) TEXT("Item B"));
        SendMessage(h, CB_ADDSTRING, 0, (LPARAM) TEXT("Item C"));
        SendMessage(h, CB_ADDSTRING, 0, (LPARAM) TEXT("Item D"));
        SendMessage(h, CB_ADDSTRING, 0, (LPARAM) TEXT("Item E"));
                
        // Select the default item to be "Item C".
        SendMessage(
                    h,                            // The handle of the combo b,
                    CB_SETCURSEL,                 // Tells the combo box to select the specified index
                    4,                            // The index of the item to select (starting at zero)
                    0                             // Not used, ignored.
            );
        break;
    default:
        break;
    }
    return h;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//

HWND hStat = NULL;
HWND hStatBitmap = NULL;
HWND hEdit = NULL;
HWND hButton = NULL;
HWND hCombo = NULL;
HWND hCheckBox = NULL;
bool is_creating = false;
WinType type_of_creation;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {    	
    case WM_LBUTTONDOWN:
        if(is_creating)
        {
            POINT p;
            p.x = LOWORD(lParam);
            p.y = HIWORD(lParam);
            switch (type_of_creation)
            {
            case WinType::Static:
                hStat = NewWindow(WinType::Static, p, hWnd);
                break;
			case WinType::StaticBitmap:
				hStatBitmap = NewWindow(WinType::StaticBitmap, p, hWnd);
				break;
            case WinType::Button:
                hButton = NewWindow(WinType::Button, p, hWnd);
                break;
			case WinType::CheckBox:
				hCheckBox = NewWindow(WinType::CheckBox, p, hWnd);
				break;
            case WinType::Edit:
                hEdit = NewWindow(WinType::Edit, p, hWnd);
                break;
            case WinType::ComboBox:
                hCombo = NewWindow(WinType::ComboBox, p, hWnd);
                break;
            default:
                break;
            }            
            is_creating = false;
        }
        break;
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_STAIC:
            //MessageBox(hWnd, TEXT("Create Static"), TEXT(""), 0);
            is_creating = true;     
            type_of_creation = WinType::Static;
            break;
		case ID_STATICBITMAP:
			is_creating = true;
			type_of_creation = WinType::StaticBitmap;
			break;
        case ID_COMBOBOX:
            //MessageBox(hWnd, TEXT("Create ComboBox"), TEXT(""), 0);
            is_creating = true;     
            type_of_creation = WinType::ComboBox;
            break;
		case ID_CHECKBX:
			is_creating = true;
			type_of_creation = WinType::CheckBox;
			break;
        case ID_BUTTON:
            is_creating = true;     
            type_of_creation = WinType::Button;
            //MessageBox(hWnd, TEXT("Create Button"), TEXT(""), 0);
            break;
        case ID_MYBUTTON:
            MessageBox(hWnd, TEXT("Button Pushed"), TEXT(""), 0);
            break;
        case ID_EDIT:
            is_creating = true;     
            type_of_creation = WinType::Edit;
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        // TODO: добавьте любой код отрисовки...
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

// Обработчик сообщений для окна "О программе".
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
