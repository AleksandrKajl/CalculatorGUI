#include"calculator.h"
#include"input.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MYDIALOG), 0, (DlgProc), 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg,WPARAM wParam, LPARAM lParam)
{
	static Input inp;
	static Calculator calc;
	switch (uMsg)
	{
	case WM_INITDIALOG:
		inp.hEdit = GetDlgItem(hWnd, IDC_MYEDIT);
		inp.setBuf('0');
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
//=====================Кнопки от 1 до 9========================================
			{
		case IDC_ONE:
			inp.setBuf('1');
			break;
		case IDC_TWO:
			inp.setBuf('2');
			break;
		case IDC_TREE:
			inp.setBuf('3');
			break;
		case IDC_FOUR:
			inp.setBuf('4');
			break;		
		case IDC_FIVE:	
			inp.setBuf('5');
			break;		
		case IDC_SIX:	
			inp.setBuf('6');
			break;		
		case IDC_SEVEN:	
			inp.setBuf('7');
			break;		
		case IDC_EIGHT:	
			inp.setBuf('8');
			break;		
		case IDC_NINE:	
			inp.setBuf('9');
			break;		
		case IDC_ZERO:
			if (inp.idx > inp.idxSign+1 && inp.input[inp.idxSign + 1] == '0' && inp.input[inp.idxSign + 2] != ',')
				break;
			inp.setBuf('0');
			break;
			}
//=============================================================================
//=====================Кнопки <--, +, -, /, *, =, ',', +/-, C================== 
			{
		case IDC_BACKSPACE:
			if(inp.idx > 1)
				inp.idx--;
			else
				inp.input[0] = '0';

			inp.input[inp.idx] = '\0';
			SendMessage(inp.hEdit, WM_SETTEXT, 0, LPARAM(inp.input.c_str()));
			break;
		case IDC_PLUS:
			inp.setSign('+');
			break;
		case IDC_MINUS:
			inp.setSign('-');
			break;
		case IDC_MUL:
			inp.setSign('*');
			break;
		case IDC_DIV:
			inp.setSign('/');
			break;
		case IDC_POINT:
			if (!inp.checkPoint(inp.idx))
				inp.setSign(',');
			break;		   
		case IDC_SIGN:	   
			inp.doSignVal('-');
			break;
		case IDC_EQ:
			//Отправляет сообщение окну, минуя очередь
			inp.idx = SendMessage(inp.hEdit, WM_GETTEXT, 256, (LPARAM)inp.input.c_str());
			if (inp.checkInput())
				inp.idx = calc.doColculations(inp.input);
			else
				inp.input="Invalid input";
			SendMessage(inp.hEdit, WM_SETTEXT, 0, LPARAM(inp.input.c_str()));
			break;
		case IDC_NULL:
			inp.idxSign = 0;
			inp.idx = 1;
			inp.input[0] = '0';
			inp.input[1] = '\0';
			SendMessage(inp.hEdit, WM_SETTEXT, 0, LPARAM(inp.input.c_str()));
			break;
			}
//=============================================================================
//=====================Кнопки x2, 2Vx, mod, % ===============================================
		case IDC_EXP:
			inp.setSign('^');
			break;

		case IDC_SQRT:
			inp.doSignVal('V');
			break;

		case IDC_MOD:
			inp.setSign('%');
			break;

		case IDC_PER:

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