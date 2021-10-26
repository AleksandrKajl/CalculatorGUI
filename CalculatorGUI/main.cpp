#include"function.h"

//Глобальные переменные
static CHAR str[256]{};
char mes[] = "Invalid input";
static HWND hEdit;


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
			idx = setText(hEdit, '1', str);
			break;
		case IDC_TWO:
			idx = setText(hEdit, '2', str);
			break;
		case IDC_TREE:
			idx = setText(hEdit, '3', str);
			break;
		case IDC_FOUR:
			idx = setText(hEdit, '4', str);
			break;
		case IDC_FIVE:
			idx = setText(hEdit, '5', str);
			break;
		case IDC_SIX:
			idx = setText(hEdit, '6', str);
			break;
		case IDC_SEVEN:
			idx = setText(hEdit, '7', str);
			break;
		case IDC_EIGHT:
			idx = setText(hEdit, '8', str);
			break;
		case IDC_NINE:
			idx = setText(hEdit, '9', str);
			break;
		case IDC_ZERO:
			idx = setText(hEdit, '0', str);
			break;
			}
//=============================================================================
//=====================Кнопки <--, +, -, /, *, =, ',', +/-, C================== 
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
			setSign(hEdit, '+', str, idx);
		//	idx = setText(hEdit, '+', str);
			break;
		case IDC_MINUS:
			setSign(hEdit, '-', str, idx);
			break;
		case IDC_MUL:
			setSign(hEdit, '*', str, idx);
			break;
		case IDC_DIV:
			setSign(hEdit, '/', str, idx);
			break;
		case IDC_POINT:
			if (!checkPoint(str, idx))
				setSign(hEdit, ',', str, idx);
			break;
		case IDC_SIGN:
			doSignNumb(hEdit, str);
			break;
		case IDC_EQ:
			getText(hEdit, str);
			if (checkInput(str))
				idx = doColculations(str);
			else
				strCopy(str, mes);
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str));
			break;
		case IDC_NULL:
			idx = 0;
			str[idx] = '\0';
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str));
			break;
			}
//=============================================================================
//=====================Кнопки x2===============================================
		case IDC_EXP:
			setSign(hEdit, '^', str,idx);
//			setText(hEdit, '2', str);
			break;
//=============================================================================
		}
		break;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return FALSE;
	}

	return FALSE;
}