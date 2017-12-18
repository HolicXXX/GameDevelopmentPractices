// SNAKE.cpp : ����Ӧ�ó������ڵ㡣
//
//�ߵ��ƶ��ٶ�  ֡��  �ƶ��߼�

#include "stdafx.h"
#include "SNAKE_WIN32.h"
#include "FOOD.h"
#include "SNAKE.h"
#include <time.h>
#include <algorithm>
#pragma comment( lib, "msimg32.lib" )

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������
HWND hWnd;
RECT windowRect;
bool isInit = 1;
TOWARD snakeTwd = DOWN;

// �˴���ģ���а����ĺ�����ǰ������: 
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

    // TODO: �ڴ˷��ô��롣

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SNAKE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SNAKE));

    MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	HDC hdc;
	SNAKE* snake;
	FOOD* food;
	LARGE_INTEGER begin, end, freq;
	QueryPerformanceCounter(&begin);
	QueryPerformanceFrequency(&freq);

    // ����Ϣѭ��: 
	while (msg.message != WM_QUIT)
    {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			if (isInit)
			{
				hdc = GetDC(hWnd);

				HDC cacheDC = CreateCompatibleDC(hdc);
				HBITMAP caheBmp = CreateCompatibleBitmap(hdc, windowRect.right - windowRect.left, windowRect.bottom - windowRect.left);
				SelectObject(cacheDC, caheBmp);
				HBRUSH b_bg = CreateSolidBrush(RGB(255, 255, 255));
				SelectObject(cacheDC, b_bg);
				FillRect(cacheDC, &windowRect, b_bg);
				DeleteObject(b_bg);
				DeleteObject(caheBmp);

				//��
				snake = new SNAKE(windowRect);
				snake->showSnake(cacheDC);

				//ʳ��
				food = new FOOD(windowRect);
				food->showFood(cacheDC);

				StretchBlt(hdc, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.left, cacheDC, 0, 0, windowRect.right, windowRect.bottom, SRCCOPY);
				DeleteObject(cacheDC);
				ReleaseDC(hWnd, hdc);
				isInit = 0;
			}
			else
			{
				QueryPerformanceCounter(&end);
				if ((double)(end.QuadPart - begin.QuadPart) / (double)freq.QuadPart >= 1.0f / 60)
				{
					snake->move(snakeTwd);

					hdc = GetDC(hWnd);

					HDC cacheDC = CreateCompatibleDC(hdc);
					HBITMAP caheBmp = CreateCompatibleBitmap(hdc, windowRect.right - windowRect.left, windowRect.bottom - windowRect.left);
					SelectObject(cacheDC, caheBmp);
					HBRUSH b_bg = CreateSolidBrush(RGB(255, 255, 255));
					SelectObject(cacheDC, b_bg);
					FillRect(cacheDC, &windowRect, b_bg);
					DeleteObject(b_bg);
					DeleteObject(caheBmp);

					double toFood = sqrt(pow((food->xFood() - snake->xhead()), 2) + pow((food->yFood() - snake->yhead()), 2));
					if (toFood < 12)
					{
						snake->eatFood(food->color());
						delete food;
						HBRUSH b_cleanFood = CreateSolidBrush(RGB(255, 255, 255));
						SelectObject(cacheDC, b_cleanFood);
						FillRect(cacheDC, &windowRect, b_cleanFood);
						DeleteObject(b_cleanFood);
						food = new FOOD(windowRect);
					}
					if (snake->isCrush())
					{
						MessageBox(hWnd, _T("Game over!"), _T("Tip"), 0);
						DestroyWindow(hWnd);
					}

					//��
					snake->showSnake(cacheDC);

					//ʳ��
					food->showFood(cacheDC);

					StretchBlt(hdc, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.left, cacheDC, 0, 0, windowRect.right, windowRect.bottom, SRCCOPY);
					DeleteObject(cacheDC);
					ReleaseDC(hWnd, hdc);
					QueryPerformanceCounter(&begin);
				}
			}
		}
    }

    return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SNAKE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SNAKE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		srand(time(0));
		GetClientRect(hWnd, &windowRect);
	}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
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
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_LEFT:
				{
					if (snakeTwd == RIGHT)
					{
						break;
					}
					snakeTwd = LEFT;
				}
				break;
			case VK_UP:
				{
					if (snakeTwd == DOWN)
					{
						break;
					}
					snakeTwd = UP;
				}
			break;
			case VK_RIGHT:
				{
					if (snakeTwd == LEFT)
					{
						break;
					}
					snakeTwd = RIGHT;
				}
			break;
			case VK_DOWN:
				{
					if (snakeTwd == UP)
					{
						break;
					}
					snakeTwd = DOWN;
				}
			break;
			}
		}
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// �����ڡ������Ϣ�������
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
