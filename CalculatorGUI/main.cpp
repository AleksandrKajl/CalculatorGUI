#include<windows.h>
#include"function.h"
#include"resource.h"

HWND hEdit;
CHAR s_text[256]{};
double result{};

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);



int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MYDIALOG), 0, (DlgProc), 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg,WPARAM wParam, LPARAM lParam)
{
	int static idx{};
	switch (uMsg)
	{
	case WM_INITDIALOG:
		hEdit = GetDlgItem(hWnd, IDC_MYEDIT);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
//=====================Кнопки от 1 до 9========================================
			{
		case IDC_ONE:
			s_text[idx] = '1';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_TWO:
			s_text[idx] = '2';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_TREE:
			s_text[idx] = '3';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_FOUR:
			s_text[idx] = '4';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_FIVE:
			s_text[idx] = '5';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_SIX:
			s_text[idx] = '6';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_SEVEN:
			s_text[idx] = '7';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_EIGHT:
			s_text[idx] = '8';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_NINE:
			s_text[idx] = '9';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
			}
//=============================================================================
//=====================Функциональные кнопки===================================
			{
		case IDC_BACKSPACE:
			--idx;
			if (idx < 0)
			{
				idx = 0;
				break;
			}
			s_text[idx] = '\0';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			break;
		case IDC_PLUS:
			s_text[idx] = '+';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_MINUS:
			s_text[idx] = '-';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_MUL:
			s_text[idx] = '*';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_DIV:
			s_text[idx] = '/';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(s_text));
			++idx;
			break;
		case IDC_EQ:
			result = doColculations(s_text);
			break;
			}
//=============================================================================
		}
		break;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return FALSE;
	}

	return FALSE;
}