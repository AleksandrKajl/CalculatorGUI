#include "input.h"
#include "calculator.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MYDIALOG), 0, (DLGPROC)(DlgProc), 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg,WPARAM wParam, LPARAM lParam)
{
	static Input input;
	static Calculator calculator;
	switch (uMsg)
	{
	case WM_INITDIALOG:
		input.hEdit = GetDlgItem(hWnd, IDC_MYEDIT);
		input.setBuf('0');
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
//=====================Кнопки от 1 до 9========================================
			{
		case IDC_ONE:
			input.setBuf('1');
			break;
		case IDC_TWO:
			input.setBuf('2');
			break;
		case IDC_TREE:
			input.setBuf('3');
			break;
		case IDC_FOUR:
			input.setBuf('4');
			break;		
		case IDC_FIVE:	
			input.setBuf('5');
			break;		
		case IDC_SIX:	
			input.setBuf('6');
			break;		
		case IDC_SEVEN:	
			input.setBuf('7');
			break;		
		case IDC_EIGHT:	
			input.setBuf('8');
			break;		
		case IDC_NINE:	
			input.setBuf('9');
			break;		
		case IDC_ZERO:
			//!Баг с повторным нажатием нуля после цифры
			if (input.idx > input.idxSign+1 && input.input[input.idxSign + 1] == '0' && input.input[input.idxSign + 2] != ',')
				break;
			input.setBuf('0');
			break;
			}
//=============================================================================
//=====================Кнопки <--, +, -, /, *, =, ',', +/-, C================== 
			{
		case IDC_BACKSPACE:
			if(input.idx > 1)
				input.idx--;
			else
				input.input[0] = '0';

			input.input[input.idx] = '\0';
			SendMessage(input.hEdit, WM_SETTEXT, 0, LPARAM(input.input));
			break;
		case IDC_PLUS:
			input.setSign('+');
			break;
		case IDC_MINUS:
			input.setSign('-');
			break;
		case IDC_MUL:
			input.setSign('*');
			break;
		case IDC_DIV:
			input.setSign('/');
			break;
		case IDC_POINT:
			if (!input.checkPoint(input.idx))
				input.setSign(',');
			break;		   
		case IDC_SIGN:	   
			input.doSignVal('-');
			break;
		case IDC_EQ:
			//Отправляет сообщение окну, минуя очередь
			input.idx = SendMessage(input.hEdit, WM_GETTEXT, 256, (LPARAM)input.input);
			if (input.checkInput())
				input.idx = calculator.doColculations(input.input);
			else
				strcpy(input.input,"Invalid input");
			SendMessage(input.hEdit, WM_SETTEXT, 0, LPARAM(input.input));
			break;
		case IDC_NULL:
			input.idxSign = 0;
			input.idx = 1;
			input.input[0] = '0';
			input.input[1] = '\0';
			SendMessage(input.hEdit, WM_SETTEXT, 0, LPARAM(input.input));
			break;
			}
//=============================================================================
//=====================Кнопки x2, 2Vx, mod, % ===============================================
		case IDC_EXP:
			input.setSign('^');
			break;

		case IDC_SQRT:
			input.doSignVal('V');
			break;

		case IDC_MOD:
			input.setSign('%');
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