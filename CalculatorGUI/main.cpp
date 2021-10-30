#include"function.h"

//Глобальные переменные
//static CHAR str[256]{};

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MYDIALOG), 0, (DlgProc), 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg,WPARAM wParam, LPARAM lParam)
{
	//int static idx{};
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
			inp.setBuf('1', inp.input);
			break;
		case IDC_TWO:
			inp.setBuf('2', inp.input);
			break;
		case IDC_TREE:
			inp.setBuf('3', inp.input);
			break;
		case IDC_FOUR:
			inp.setBuf('4', inp.input);
			break;				  
		case IDC_FIVE:			  
			inp.setBuf('5', inp.input);
			break;				  
		case IDC_SIX:			  
			inp.setBuf('6', inp.input);
			break;				  
		case IDC_SEVEN:			  
			inp.setBuf('7', inp.input);
			break;				  
		case IDC_EIGHT:			  
			inp.setBuf('8', inp.input);
			break;				  
		case IDC_NINE:			  
			inp.setBuf('9', inp.input);
			break;				  
		case IDC_ZERO:			  
			inp.setBuf('0', inp.input);
			break;
			}
//=============================================================================
//=====================Кнопки <--, +, -, /, *, =, ',', +/-, C================== 
			{
		case IDC_BACKSPACE:
			inp.idx--;
			if (inp.idx < 0)
			{
				inp.idx = 0;
				break;
			}
			inp.input[inp.idx] = '\0';
			SendMessage(inp.hEdit, WM_SETTEXT, 0, LPARAM(inp.input));
			break;
		case IDC_PLUS:
			inp.setSign('+', inp.input, inp.idx);
			break;
		case IDC_MINUS:
			inp.setSign('-', inp.input, inp.idx);
			break;
		case IDC_MUL:
			inp.setSign('*', inp.input, inp.idx);
			break;
		case IDC_DIV:
			inp.setSign('/', inp.input, inp.idx);
			break;
		case IDC_POINT:
			if (!checkPoint(inp.input, inp.idx))
				inp.setSign(',', inp.input, inp.idx);
			break;		   
		case IDC_SIGN:	   
			inp.doSignVal(inp.input, '-');
			break;
		case IDC_EQ:
			inp.getBuf(inp.input);
			if (checkInput(inp.input))
				inp.idx = doColculations(inp.input);
			else
				strcpy(inp.input,"Invalid input");
			SendMessage(inp.hEdit, WM_SETTEXT, 0, LPARAM(inp.input));
			break;
		case IDC_NULL:
			inp.idx = 0;
			inp.input[inp.idx] = '\0';
			SendMessage(inp.hEdit, WM_SETTEXT, 0, LPARAM(inp.input));
			break;
			}
//=============================================================================
//=====================Кнопки x2, 2Vx===============================================
		case IDC_EXP:
			inp.setSign('^', inp.input, inp.idx);
			break;

		case IDC_SQRT:
			inp.doSignVal(inp.input, 'V');
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