#include"function.h"

//Глобальные переменные
static CHAR str[256]{};

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MYDIALOG), 0, (DlgProc), 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg,WPARAM wParam, LPARAM lParam)
{
	int static idx{};
	static Input inp;
	switch (uMsg)
	{
	case WM_INITDIALOG:
		inp.hEdit = GetDlgItem(hWnd, IDC_MYEDIT);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
//=====================Кнопки от 1 до 9========================================
			{
		case IDC_ONE:
			idx = inp.setBuf('1', str);
			break;
		case IDC_TWO:
			idx = inp.setBuf('2', str);
			break;
		case IDC_TREE:
			idx = inp.setBuf('3', str);
			break;
		case IDC_FOUR:
			idx = inp.setBuf('4', str);
			break;
		case IDC_FIVE:
			idx = inp.setBuf('5', str);
			break;
		case IDC_SIX:
			idx = inp.setBuf('6', str);
			break;
		case IDC_SEVEN:
			idx = inp.setBuf('7', str);
			break;
		case IDC_EIGHT:
			idx = inp.setBuf('8', str);
			break;
		case IDC_NINE:
			idx = inp.setBuf('9', str);
			break;
		case IDC_ZERO:
			idx = inp.setBuf('0', str);
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
			SendMessage(inp.hEdit, WM_SETTEXT, 0, LPARAM(str));
			break;
		case IDC_PLUS:
			inp.setSign('+', str, idx);
		//	idx = setText(hEdit, '+', str);
			break;
		case IDC_MINUS:
			inp.setSign('-', str, idx);
			break;
		case IDC_MUL:
			inp.setSign('*', str, idx);
			break;
		case IDC_DIV:
			inp.setSign('/', str, idx);
			break;
		case IDC_POINT:
			if (!checkPoint(str, idx))
				inp.setSign(',', str, idx);
			break;		   
		case IDC_SIGN:	   
			inp.doSignVal(str, '-');
			break;
		case IDC_EQ:
			inp.getBuf(str);
			if (checkInput(str))
				idx = doColculations(str);
			else
				strcpy(str,"Invalid input");
			SendMessage(inp.hEdit, WM_SETTEXT, 0, LPARAM(str));
			break;
		case IDC_NULL:
			idx = 0;
			str[idx] = '\0';
			SendMessage(inp.hEdit, WM_SETTEXT, 0, LPARAM(str));
			break;
			}
//=============================================================================
//=====================Кнопки x2, 2Vx===============================================
		case IDC_EXP:
			inp.setSign('^', str, idx);
			break;

		case IDC_SQRT:
			inp.doSignVal(str, 'V');
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