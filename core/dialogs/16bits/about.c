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
  Last modified date: 23/08/2026
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
  char translated[MEDIUM_BUFFER];
  HBITMAP hBmp, hOldBmp;
  int parentWidth, parentHeight;
	int dlgWidth, dlgHeight, fontHeight;
	int bordersWidth, bordersHeight, status;
	HWND hParent, hStatic, hBtn, hCtrl;
	RECT rcParent, rect, rcCtrl, rcDlgOrigin;

  switch(msg)
  {
		
		case WM_INITDIALOG:
    {
			
			hParent = (HWND)lParam;
			
			// set window title
			
			if(stricmp(conf.language, "en") == 0)
				strncpy(translated, "About of Scryvano", sizeof(translated) - 1);
			else
			{
				
				status = readINIkey("about_dialog", "caption", translated, sizeof(translated), translatefile);
			  if(status == FALSE) strncpy(translated, "About of Scryvano", sizeof(translated) - 1);
				
			}

			SetWindowText(hDlg, translated);
			
			// set close button title
			
			if(stricmp(conf.language, "en") == 0)
				strncpy(translated, "Close", sizeof(translated) - 1);
			else
			{
				
				status = readINIkey("about_dialog", "close", translated, sizeof(translated), translatefile);
			  if(status == FALSE) strncpy(translated, "Close", sizeof(translated) - 1);
				
			}
			
			SetDlgItemText(hDlg, IDD_BUTTON_ABOUT, translated);
			
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
            
			// set vertical align
			SetWindowPos(hStatic, 0, pt.x, pt.y - 10, width, fontHeight, SWP_NOZORDER | SWP_NOACTIVATE);

      // formating about text to dialog
      sprintf(bufferText, "V. %s - %s %s", PROJECT_VERSION, PROJECT_YEAR, TEAM_NAME);
      SetDlgItemText(hDlg, IDD_TEXT_ABOUT, bufferText);
						
			// align vertical text in the button
			
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

			// adjust dialog sizes
	
			rcDlgOrigin.left = 0;
			rcDlgOrigin.top = 0;
			rcDlgOrigin.right = 172;  // size from .rc
			rcDlgOrigin.bottom = 147; // size from .rc
			
			MapDialogRect(hDlg, &rcDlgOrigin);

			// calculate borders
			
			bordersWidth = GetSystemMetrics(SM_CXDLGFRAME) * 2;
			bordersHeight  = (GetSystemMetrics(SM_CYDLGFRAME) * 2) + GetSystemMetrics(SM_CYCAPTION);

			// adjust dialog sizes
			
			dlgWidth  = (rcDlgOrigin.right - rcDlgOrigin.left) + bordersWidth;
			dlgHeight = (rcDlgOrigin.bottom - rcDlgOrigin.top) + bordersHeight;
			
			// center dialog on the parent
			
      if(hParent == 0)
        hParent = GetDesktopWindow();

      GetWindowRect(hParent, &rcParent);
      parentWidth  = rcParent.right - rcParent.left;
      parentHeight = rcParent.bottom - rcParent.top;

      x = rcParent.left + (parentWidth - dlgWidth) / 2;
      y = rcParent.top + (parentHeight - dlgHeight) / 2;

      // patch to dialog size
      SetWindowPos(hDlg, 0, x, y, dlgWidth, dlgHeight, SWP_NOZORDER);

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
