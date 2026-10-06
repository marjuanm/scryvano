/*
  Scryvano - Lightweight text editor
  Original file name: 32bits.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/

/* 
  Purpose: Create about dialog
  Created date: 07/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 28/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT and gemini
*/
INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    
	POINT pt;
	HFONT hFont;
	HBITMAP hBmp;
	int x, y, width;
	char bufferText[MEDIUM_BUFFER];
	char translated[MEDIUM_BUFFER];
	int parentWidth, parentHeight;
	int pictureWidth, pictureHeight;
	int dlgWidth, dlgHeight, fontHeight;
	HWND hParent, hStatic, hPicture, hBtn;
	int bordersWidth, bordersHeight, status;
	RECT rcParent, rect, rcDlgOrigin, rcPicture;

	switch(msg)
	{
	
		case WM_INITDIALOG:

			hParent = (HWND)lParam;

			// set window title

			if(stricmp(conf.language, "en") == 0)
				strncpy(translated, "About of Scryvano", sizeof(translated) - 1);
			else
			{
			
				status = readINIkey("about_dialog", "caption", translated, sizeof(translated), translatefile);
				if(status == FALSE) strncpy(translated, "About of Scryvano", sizeof(translated) - 1);
			
			}

			translated[sizeof(translated) - 1] = '\0';
			SetWindowText(hDlg, translated);

			// set close button title

			if(stricmp(conf.language, "en") == 0)
				strncpy(translated, "Close", sizeof(translated) - 1);
			else
			{
			
				status = readINIkey("about_dialog", "close", translated, sizeof(translated), translatefile);
				if(status == FALSE) strncpy(translated, "Close", sizeof(translated) - 1);
			
			}

			translated[sizeof(translated) - 1] = '\0';
			SetDlgItemText(hDlg, IDC_BUTTON_ABOUT, translated);

			// adjust text field to font size

			hFont = getDefaultFont();
			if(hFont != NULL) SendDlgItemMessage(hDlg, IDC_TEXT_ABOUT, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			fontHeight = getDefaultFontHeight();

			hStatic = GetDlgItem(hDlg, IDC_TEXT_ABOUT);

			if(hStatic != NULL)
			{
			
				GetWindowRect(hStatic, &rect);

				pt.x = rect.left;
				pt.y = rect.top;

				ScreenToClient(hDlg, &pt);
				width = rect.right - rect.left;

				// set vertical align
				SetWindowPos(hStatic, NULL, pt.x, pt.y - 10, width, fontHeight, SWP_NOZORDER | SWP_NOACTIVATE);
			
			}
			
			// set font to button
			
			hBtn = GetDlgItem(hDlg, IDC_BUTTON_ABOUT);
			if(hBtn != NULL) SendDlgItemMessage(hDlg, IDC_BUTTON_ABOUT, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		
			// set picture to static control

			hPicture = GetDlgItem(hDlg, IDC_PICTURE_ABOUT);

			if(hPicture != NULL)
			{
			
				/*
				* Get the real size of the picture control.
				* This prevents the bitmap from being forced to
				* an arbitrary size that does not match the dialog.
				*/

				GetWindowRect(hPicture, &rcPicture);

				pictureWidth  = rcPicture.right - rcPicture.left;
				pictureHeight = rcPicture.bottom - rcPicture.top;

				hBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_LOGO), IMAGE_BITMAP, pictureWidth, pictureHeight, LR_CREATEDIBSECTION);
			
				if(hBmp != NULL) 
					SendDlgItemMessage(hDlg, IDC_PICTURE_ABOUT, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
			
			}

			// formatting about text to dialog

			snprintf(bufferText, sizeof(bufferText), "V. %s - %s %s", PROJECT_VERSION, PROJECT_YEAR, TEAM_NAME);
			SetDlgItemText(hDlg, IDC_TEXT_ABOUT, bufferText);

			// restore font after changing text

			if(hFont != NULL)
				SendDlgItemMessage(hDlg, IDC_TEXT_ABOUT, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		
			// adjust dialog size
			//
			// These values correspond to the dialog dimensions
			// defined in the .dlg/.rc resource.

			rcDlgOrigin.left   = 0;
			rcDlgOrigin.top    = 0;
			rcDlgOrigin.right  = 172;
			rcDlgOrigin.bottom = 147;

			MapDialogRect(hDlg, &rcDlgOrigin);

			// calculate dialog borders

			bordersWidth = GetSystemMetrics(SM_CXDLGFRAME) * 2;
			bordersHeight = (GetSystemMetrics(SM_CYDLGFRAME) * 2) + GetSystemMetrics(SM_CYCAPTION);

			// calculate final dialog size

			dlgWidth = (rcDlgOrigin.right - rcDlgOrigin.left) + bordersWidth;
			dlgHeight = (rcDlgOrigin.bottom - rcDlgOrigin.top) + bordersHeight;

			// center dialog on parent

			if(hParent == NULL)
				hParent = GetDesktopWindow();

			GetWindowRect(hParent, &rcParent);

			parentWidth = rcParent.right - rcParent.left;
			parentHeight = rcParent.bottom - rcParent.top;
			x = rcParent.left + (parentWidth - dlgWidth) / 2;
			y = rcParent.top + (parentHeight - dlgHeight) / 2;

			// force dialog size
			SetWindowPos(hDlg, NULL, x, y, dlgWidth, dlgHeight, SWP_NOZORDER);

			return TRUE;

    case WM_COMMAND:
          
			if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == IDC_BUTTON_ABOUT)
      {
						
				EndDialog(hDlg, 0);
        return TRUE;
            
			}
          
			break;
    
	}

  return FALSE;

}
