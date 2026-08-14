/*
Scryvano - Lightweight text editor
Original file name: 16bits.c
Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/

/*
Purpose: Create about dialog
Created date: 08/08/2026
Created by username: Juan Manuel Mar Hdz.
Last modified date: 08/08/2026
Last modified username: Juan Manuel Mar Hdz.
Thanks to chatGPT and gemini
*/
BOOL FAR PASCAL _export AboutDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	POINT pt;
  BITMAP bmp;
	HFONT hFont;
  HDC hdcMem;
  int x, y, width;
  char bufferText[128];
  HBITMAP hBmp, hOldBmp;
  int parentWidth, parentHeight;
	RECT rcParent, rcDlg, rect, rcCtrl;
  int dlgWidth, dlgHeight, fontHeight;
	HWND hParent, hStatic, hBtn, hCtrl;
  
  switch(msg)
  {
    
    case WM_INITDIALOG:
    {
			
			hParent = (HWND)lParam;

      // adjust text field to font size
      hFont = getDefaultFont();

      if(hFont != 0)
        SendDlgItemMessage(hDlg, IDD_TEXT_ABOUT, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

      fontHeight = getDefaultFontHeight();
      hStatic = GetDlgItem(hDlg, IDD_TEXT_ABOUT);
      GetWindowRect(hStatic, &rect);

      pt.x = rect.left;
      pt.y = rect.top;

      ScreenToClient(hDlg, &pt);
      width = rect.right - rect.left;
            
			//adjust description section position
			SetWindowPos(hStatic, 0, pt.x, pt.y - 10, width, fontHeight, SWP_NOZORDER | SWP_NOACTIVATE);

      // set version to text
      sprintf(bufferText, "V. %s - %s %s", PROJECT_VERSION, PROJECT_YEAR, TEAM_NAME);
      SetDlgItemText(hDlg, IDD_TEXT_ABOUT, bufferText);
						
			// adjust button section position
			hBtn = GetDlgItem(hDlg, IDD_BUTTON_ABOUT);

			if(hBtn != 0)
			{
    
				GetWindowRect(hBtn, &rect);
				pt.x = rect.left;
				pt.y = rect.top;

				ScreenToClient(hDlg, &pt);
				width = rect.right - rect.left;
				fontHeight = rect.bottom - rect.top;
				SetWindowPos(hBtn, 0, pt.x, pt.y - 10, width, fontHeight, SWP_NOZORDER | SWP_NOACTIVATE);

			}
			
			// center on parent
      if(hParent == 0)
        hParent = GetDesktopWindow();

      GetWindowRect(hParent, &rcParent);
      GetWindowRect(hDlg, &rcDlg);

      parentWidth  = rcParent.right - rcParent.left;
      parentHeight = rcParent.bottom - rcParent.top;

      dlgWidth  = rcDlg.right - rcDlg.left;
      dlgHeight = rcDlg.bottom - rcDlg.top;

      x = rcParent.left + (parentWidth - dlgWidth) / 2;
      y = rcParent.top + (parentHeight - dlgHeight) / 2;

      SetWindowPos(hDlg, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

      return TRUE;
    		
		}

		case WM_CTLCOLOR:
		{
    
			hCtrl = (HWND)LOWORD(lParam);

			if(hCtrl == GetDlgItem(hDlg, IDD_PICTURE_ABOUT))
			{
			
				hBmp = LoadBitmap(appInst, MAKEINTRESOURCE(IDB_LOGO));

				if(hBmp != 0)
				{
				
					GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp);
					GetClientRect(hCtrl, &rcCtrl); // frame coordinates
				
					hdcMem = CreateCompatibleDC((HDC)wParam);
					hOldBmp = SelectObject(hdcMem, hBmp);

					// prevent color distorsion
					SetStretchBltMode((HDC)wParam, COLORONCOLOR);

					// strech bitmap to frame
					StretchBlt(
						(HDC)wParam, 
						0, 0, 
						rcCtrl.right, rcCtrl.bottom, // frame size
						hdcMem, 
						0, 0, 
						bmp.bmWidth, bmp.bmHeight,
						SRCCOPY
					);

					SelectObject(hdcMem, hOldBmp);
					DeleteDC(hdcMem);
					DeleteObject(hBmp);

					return (LRESULT)GetStockObject(NULL_BRUSH);
        
				}
			
			}
		
			break;

		}

		case WM_COMMAND:
		{
		
			if(wParam == IDOK || wParam == IDCANCEL || wParam == IDD_BUTTON_ABOUT)
			{
			
				EndDialog(hDlg, TRUE);
				return TRUE;
    
			}
		
			break;
        
		}
    
	}

  return FALSE;

}
