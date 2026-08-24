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
  Last modified date: 23/08/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT and gemini
*/
INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    
	POINT pt;
	HFONT hFont;
	HBITMAP hBmp;
	int x, y, width;
	HWND hParent, hStatic;
	RECT rcParent, rcDlg, rect;
	char bufferText[MEDIUM_BUFFER];
	char translated[MEDIUM_BUFFER];
	int dlgWidth, dlgHeight, fontHeight;
	int parentWidth, parentHeight, status;
  
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
			
			if(hFont != NULL) 
				SendDlgItemMessage(hDlg, IDD_TEXT_ABOUT, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
			
			fontHeight = getDefaultFontHeight();
			
			hStatic = GetDlgItem(hDlg, IDD_TEXT_ABOUT);
			GetWindowRect(hStatic, &rect);
			
			pt.x = rect.left;
			pt.y = rect.top;
			
			ScreenToClient(hDlg, &pt);
			width = rect.right - rect.left;
			SetWindowPos(hStatic, NULL, pt.x, pt.y, width, fontHeight, SWP_NOZORDER | SWP_NOACTIVATE);
			
			// set picture to static text
			
			hBmp = (HBITMAP)LoadImage(
        GetModuleHandle(NULL), 
        MAKEINTRESOURCE(IDB_LOGO), 
        IMAGE_BITMAP, 
        234, 150, 
        LR_CREATEDIBSECTION
			);

			if(hBmp != NULL) 
				SendDlgItemMessage(hDlg, IDD_PICTURE_ABOUT, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
			
			// set version to text
			
			snprintf(bufferText, sizeof(bufferText), "V. %s - %s %s", PROJECT_VERSION, PROJECT_YEAR, TEAM_NAME);
			SetDlgItemText(hDlg, IDD_TEXT_ABOUT, bufferText);
			
			if(hFont != NULL) 
			  SendDlgItemMessage(hDlg, IDD_TEXT_ABOUT, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

			// center on parent
			
			if(hParent == NULL)
        hParent = GetDesktopWindow();

      GetWindowRect(hParent, &rcParent);
      GetWindowRect(hDlg, &rcDlg);

      parentWidth  = rcParent.right - rcParent.left;
      parentHeight = rcParent.bottom - rcParent.top;

      dlgWidth  = rcDlg.right - rcDlg.left;
      dlgHeight = rcDlg.bottom - rcDlg.top;

      x = rcParent.left + (parentWidth - dlgWidth) / 2;
      y = rcParent.top  + (parentHeight - dlgHeight) / 2;

      SetWindowPos(hDlg, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			
      return TRUE;

    case WM_COMMAND:
          
			if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == IDD_BUTTON_ABOUT)
      {
						
				EndDialog(hDlg, 0);
        return TRUE;
            
			}
          
			break;
    
	}

  return FALSE;

}
