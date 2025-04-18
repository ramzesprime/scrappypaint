#include "framework.h"
#include "sexy.h"

#define MAX_LOADSTRING 100
#define BTN_1 1001
#define BTN_2 1002
#define BTN_3 1003
#define BTN_4 1004
#define BTN_5 1005
#define BTN_6 1006

bool isThick = false;
int g_x = -1;
int g_y = -1;
int GLOBALSEX = 0;
int BRUSH_COLOR = 0;
bool isDrawing = false;
int prev_x = -1, prev_y = -1;
bool clear = false;


HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                 
WCHAR szWindowClass[MAX_LOADSTRING];            

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SEXY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SEXY));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

void myself_clear() {

}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SEXY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SEXY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    

   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   CreateWindowW(L"STATIC",         
       L"PAINT BY SMARTEST PYTHON DEVELOPER EVER",            
       WS_VISIBLE | WS_CHILD,        
       400, 20, 150, 60,              
       hWnd,                         
       NULL,                         
       hInst, NULL);

   CreateWindowW(L"BUTTON",             
       L"RED",      
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       10, 250, 120, 30,    
       hWnd,                 
       (HMENU)BTN_1,   
       hInst, nullptr);    

   CreateWindowW(L"BUTTON",        
       L"BLUE",         
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       10, 290, 120, 30,       
       hWnd,              
       (HMENU)BTN_2,   
       hInst, nullptr);     

   CreateWindowW(L"BUTTON",
       L"YELLOW",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       10, 330, 120, 30,
       hWnd,
       (HMENU)BTN_3,
       hInst, nullptr);

   CreateWindowW(L"BUTTON",
       L"increase brush",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       10, 370, 120, 30,
       hWnd,
       (HMENU)BTN_4,
       hInst, nullptr);

   CreateWindowW(L"BUTTON",
       L"lower brush",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       10, 410, 120, 30,
       hWnd,
       (HMENU)BTN_5,
       hInst, nullptr);

   CreateWindowW(L"BUTTON",
       L"clear",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       10, 450, 120, 30,
       hWnd,
       (HMENU)BTN_6,
       hInst, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


    switch (message)
    {
    break;
    case WM_LBUTTONDOWN:
        isDrawing = true;
        prev_x = LOWORD(lParam);
        prev_y = HIWORD(lParam);
        break;

    case WM_LBUTTONUP:
        isDrawing = false;
        break;

    case WM_MOUSEMOVE:
    {
        if (isDrawing)
        {
            HDC hdc = GetDC(hWnd);


            int sex = (isThick) ? 10 : 6;


            HPEN pen;
            switch (BRUSH_COLOR)
            {
            case 1:
                pen = CreatePen(PS_SOLID, sex, RGB(255, 0, 0)); break;
            case 2:
                pen = CreatePen(PS_SOLID, sex, RGB(0, 0, 255)); break;
            case 3:
                pen = CreatePen(PS_SOLID, sex, RGB(255, 255, 0)); break;
            default:
                pen = CreatePen(PS_SOLID, sex, RGB(0, 0, 0)); break;
            }

            HPEN oldPen = (HPEN)SelectObject(hdc, pen);

            int curr_x = LOWORD(lParam);
            int curr_y = HIWORD(lParam);


            RECT rect;
            GetClientRect(hWnd, &rect);
            InflateRect(&rect, -170, -169);

            if (curr_x < rect.left) curr_x = rect.left;
            if (curr_x > rect.right) curr_x = rect.right;
            if (curr_y < rect.top) curr_y = rect.top;
            if (curr_y > rect.bottom) curr_y = rect.bottom;


            MoveToEx(hdc, prev_x, prev_y, NULL);
            LineTo(hdc, curr_x, curr_y);

            SelectObject(hdc, oldPen);
            DeleteObject(pen);
            ReleaseDC(hWnd, hdc);

            prev_x = curr_x;
            prev_y = curr_y;
        }
    }
    

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case BTN_1:
                
                BRUSH_COLOR = 1;
                break;
            case BTN_2:
                
                BRUSH_COLOR = 2;
                break;
            case BTN_3:
                
                BRUSH_COLOR = 3;
                break;
            case BTN_4:
                isThick = false;
                BRUSH_COLOR = 3;
                break;
            case BTN_5:
                isThick = true;
                BRUSH_COLOR = 3;
                break;
            case BTN_6:
                clear = true;
                InvalidateRect(hWnd, NULL, TRUE);
                break;

            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    
   
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
    {
        
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        if (clear == true) {
            RECT rect;
            GetClientRect(hWnd, &rect); 

            HBRUSH brush = CreateSolidBrush(RGB(255, 255, 0)); 
            HDC hdc = GetDC(hWnd);

            FillRect(hdc, &rect, brush);

            DeleteObject(brush);

            HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0)); 
            HGDIOBJ oldPen = SelectObject(hdc, pen);

            MoveToEx(hdc, rect.left, rect.top, NULL);
            LineTo(hdc, rect.right - 1, rect.top);
            LineTo(hdc, rect.right - 1, rect.bottom - 1);
            LineTo(hdc, rect.left, rect.bottom - 1);
            LineTo(hdc, rect.left, rect.top);

           
            SelectObject(hdc, oldPen);
            DeleteObject(pen);

            ReleaseDC(hWnd, hdc);
        }


        if (g_x >= 0 && g_y >= 0)
        {
            HBRUSH brush = NULL;

            switch (BRUSH_COLOR) {
            case 1:
                brush = CreateSolidBrush(RGB(255, 0, 0));
                break;
            case 2:
                brush = CreateSolidBrush(RGB(0, 0, 255)); 
                break;
            case 3:
                brush = CreateSolidBrush(RGB(255, 255, 0));
                break;
            default:
                brush = CreateSolidBrush(RGB(0, 0, 0)); 
                break;
            }

            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
            Ellipse(hdc, g_x - 10, g_y - 10, g_x + 10, g_y + 10);
            SelectObject(hdc, oldBrush);
            DeleteObject(brush);
        }

        RECT rect;
        GetClientRect(hWnd, &rect); 

        InflateRect(&rect, -170, -169);
        HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0)); 
        HGDIOBJ oldPen = SelectObject(hdc, pen);
        MoveToEx(hdc, rect.left, rect.top, NULL);
        LineTo(hdc, rect.right - 1, rect.top);
        LineTo(hdc, rect.right - 1, rect.bottom - 1);
        LineTo(hdc, rect.left, rect.bottom - 1);
        LineTo(hdc, rect.left, rect.top);
        SelectObject(hdc, oldPen);
        DeleteObject(pen);

        EndPaint(hWnd, &ps);
        
    }
    break;


    
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

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
