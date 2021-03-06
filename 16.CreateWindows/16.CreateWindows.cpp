// 16.CreateWindows.cpp: ���������� ����� ����� ��� ����������.
//
#include "stdafx.h"
#include "16.CreateWindows.h"

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
    LoadString(hInstance, IDC_MY16CREATEWINDOWS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY16CREATEWINDOWS));

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

enum class WinType
{
    Static,
    StaticBitmap,
    Button,
    CheckBox,
    RadioButton,
    Edit,
    ComboBox
};


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
    openfilename.lpstrFileTitle = TEXT("");
    openfilename.Flags = OFN_FILEMUSTEXIST;
    if (GetOpenFileName(&openfilename))
    {	
        hBitmap = (HBITMAP) LoadImage(NULL, szFileName, IMAGE_BITMAP,
            0, 0, LR_LOADFROMFILE);
    }

    return hBitmap;
}

// https://en.wikibooks.org/wiki/Windows_Programming/User_Interface_Controls
#define ID_MYBUTTON 1
#define ID_MYCHECHBOX 2
#define ID_BLUE 3
#define ID_YELLOW 4
#define ID_ORANGE 5

HWND NewWindow(WinType type, POINT p, HWND hWnd)
{
    HWND h = NULL;
    switch (type)
    {
    case WinType::Static:
        h = CreateWindow(TEXT("STATIC"),
            TEXT("Static Winodw"),
            // Window Style (WS_*) plus Static Style (SS_*)
            // https://msdn.microsoft.com/en-us/library/windows/desktop/bb760773%28v=vs.85%29.aspx
            WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT,
            p.x, p.y,100, 30, hWnd, NULL, hInst, NULL);
        // Change static text
        SendMessage(h ,                         /*HWND*/        /*Label*/
            WM_SETTEXT,                         /*UINT*/        /*Message*/
            NULL,                               /*WPARAM*/      /*Unused*/
            (LPARAM) TEXT("Hello Static"));     /*LPARAM*/      /*Text*/
        // Alternative change text
        SetWindowText(h, TEXT("It is simple static"));
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
            // Window Style (WS_*) plus Button Style (BS_*)
            WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON,
            p.x, p.y,100, 30, hWnd, (HMENU)ID_MYBUTTON, hInst, NULL);
        // change text on button
        SendMessage(h, WM_SETTEXT, NULL, (LPARAM) TEXT("It is button"));
        // alternative change text
        SetWindowText(h, TEXT("Btn"));
        break;
    case WinType::CheckBox:
        h = CreateWindow(TEXT("BUTTON"), TEXT("Check box"),
            WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
            p.x, p.y, 100, 30, hWnd, (HMENU)ID_MYCHECHBOX, hInst, NULL);

        break;
    case WinType::RadioButton:
        CreateWindow(TEXT("button"), TEXT("Choose colour"), 
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            p.x, p.y, 120, 110, hWnd, (HMENU) 0, hInst, NULL);
        CreateWindow(L"button", L"Blue",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            p.x + 10, p.y + 20, 100, 30, hWnd, (HMENU) ID_BLUE , hInst, NULL);
        CreateWindow(L"button", L"Yellow",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            p.x + 10, p.y + 45, 100, 30, hWnd, (HMENU) ID_YELLOW , hInst, NULL);
        CreateWindow(L"button", L"Orange",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            p.x + 10, p.y + 70, 100, 30, hWnd, (HMENU) ID_ORANGE , hInst, NULL);
        break;
    case WinType::Edit:
        h = CreateWindow(TEXT("EDIT"),
            TEXT("Edit Winodw"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL | WS_VSCROLL | ES_MULTILINE,
            p.x, p.y,300, 250, hWnd, NULL, hInst, NULL);
        // Set the text.
        SendMessage(h, WM_SETTEXT, 0, (LPARAM)"Hello");
        {
            // Get the text.
            LRESULT iTextSize = SendMessage(h, EM_GETLIMITTEXT, 0, 0);
            TCHAR *szText = new TCHAR[iTextSize];
            SendMessage(h, WM_GETTEXT, iTextSize, (LPARAM)szText);
        }
        // Alternative set text
        SetWindowText(h, TEXT("Edit box"));
        {
            // and get text
            int len = GetWindowTextLength(h);
            std::unique_ptr<TCHAR> text(new TCHAR[len + 1]);
            GetWindowText(h, text.get(), len+1);
            MessageBox(NULL, text.get(), TEXT(""), 0);
        }
        break;

    case WinType::ComboBox:
        h = CreateWindow(TEXT("COMBOBOX"), TEXT(""),
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
            p.x, p.y, 150, 150, hWnd, NULL, hInst, NULL);
        // Add a list of strings to the combo box.

        SendMessage(
            h,                            // The handle of the combo box
            CB_ADDSTRING,                 // Tells the combo box to append this string to its list
            0,                            // Not used, ignored.
            (LPARAM) TEXT("Item A")       // The string to add.
            );

        SendMessage(h, CB_ADDSTRING, 0, (LPARAM) TEXT("Item B"));
        SendMessage(h, CB_ADDSTRING, 0, (LPARAM) TEXT("Item C"));
        SendMessage(h, CB_ADDSTRING, 0, (LPARAM) TEXT("Item D"));
        SendMessage(h, CB_ADDSTRING, 0, (LPARAM) TEXT("Item E"));

        // Select the default item to be "Item C".
        SendMessage(
            h,                            // The handle of the combo b,
            CB_SETCURSEL,                 // Tells the combo box to select the specified index
            2,                            // The index of the item to select (starting at zero)
            0                             // Not used, ignored.
            );
        break;
    default:
        break;
    }
    return h;
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

HWND hStat = NULL;
HWND hStatBitmap = NULL;
HWND hEdit = NULL;
HWND hButton = NULL;
HWND hRadio = NULL;
HWND hCheckBox = NULL;
HWND hCombo = NULL;
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
            case WinType::RadioButton:
                hRadio = NewWindow(WinType::RadioButton, p, hWnd);
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
        // ��������� ����� � ����:
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
            //MessageBox(hWnd, TEXT("Create Static"), TEXT(""), 0);
            is_creating = true;     
            type_of_creation = WinType::StaticBitmap;
            break;
        case ID_COMBOBOX:
            //MessageBox(hWnd, TEXT("Create ComboBox"), TEXT(""), 0);
            is_creating = true;     
            type_of_creation = WinType::ComboBox;
            break;
        case ID_BUTTON:
            is_creating = true;     
            type_of_creation = WinType::Button;
            //MessageBox(hWnd, TEXT("Create Button"), TEXT(""), 0);
            break;
        case ID_RADIOBUTTON:
            is_creating = true;     
            type_of_creation = WinType::RadioButton;
            //MessageBox(hWnd, TEXT("Create Button"), TEXT(""), 0);
            break;
        case ID_CHECKBOX:
            is_creating = true;     
            type_of_creation = WinType::CheckBox;
            //MessageBox(hWnd, TEXT("Create Button"), TEXT(""), 0);
            break;
        case ID_MYCHECHBOX:
            {
                bool is_check = IsDlgButtonChecked(hWnd, ID_MYCHECHBOX);
                if(is_check)
                {
                    CheckDlgButton(hWnd, ID_MYCHECHBOX, BST_UNCHECKED);                    
                }
                else 
                {
                    CheckDlgButton(hWnd, ID_MYCHECHBOX, BST_CHECKED);
                }                
            }
            break;
        case ID_BLUE:
             MessageBox(hWnd, TEXT("Blue"), TEXT(""), 0);
            break;
        case ID_YELLOW:
            MessageBox(hWnd, TEXT("Yellow"), TEXT(""), 0);
            break;
        case ID_ORANGE:
            MessageBox(hWnd, TEXT("Orange"), TEXT(""), 0);
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
        // TODO: �������� ����� ��� ���������...
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
