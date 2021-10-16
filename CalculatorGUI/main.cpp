#include"function.h"


CHAR str[256]{};
HWND hEdit;

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
			setText(hEdit, '1', str, idx);
			break;
		case IDC_TWO:
			setText(hEdit, '2', str, idx);
			break;
		case IDC_TREE:
			setText(hEdit, '3', str, idx);
			break;
		case IDC_FOUR:
			setText(hEdit, '4', str, idx);
			break;
		case IDC_FIVE:
			setText(hEdit, '5', str, idx);
			break;
		case IDC_SIX:
			setText(hEdit, '6', str, idx);
			break;
		case IDC_SEVEN:
			setText(hEdit, '7', str, idx);
			break;
		case IDC_EIGHT:
			setText(hEdit, '8', str, idx);
			break;
		case IDC_NINE:
			setText(hEdit, '9', str, idx);
			break;
		case IDC_ZERO:
			setText(hEdit, '0', str, idx);
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
			str[idx] = '\0';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str));
			break;
		case IDC_PLUS:
			setText(hEdit, '+', str, idx);
			break;
		case IDC_MINUS:
			setText(hEdit, '-', str, idx);
			break;
		case IDC_MUL:
			setText(hEdit, '*', str, idx);
			break;
		case IDC_DIV:
			setText(hEdit, '/', str, idx);
			break;
		case IDC_POINT:
			setText(hEdit, ',', str, idx);
			break;
		case IDC_SIGN:
			doSignNumb(hEdit, str);
			break;
		case IDC_EQ:
			getText(hEdit, str);
			idx = doColculations(str);
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str));
			break;
		case IDC_NULL:
			idx = 0;
			str[idx] = '\0';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str));
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