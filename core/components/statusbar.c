/*
  Scryvano - Lightweight text editor
  Original file name: statusbar.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/

/* 
  Purpose: Create the status bar
  Created date: 07/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 07/08/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
HWND StatusBar_Create(HWND hwndParent, LPCSTR text, BOOL simplestyle)
{

  RECT rc;
	HFONT hFont;
	HWND hStatus = 0;

  GetClientRect(hwndParent, &rc);
	
	hStatus = StatusBar_CreateWindow(hwndParent, text, simplestyle);
	hFont = getDefaultFont();
	
	SendMessage(hStatus, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

  return hStatus;

}

/* 
  Purpose: Set text to status bar
  Created date: 07/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 07/08/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
void StatusBar_SetText(HWND hStatus, LPCSTR text)
{

  if(hStatus != 0)
    SetWindowText(hStatus, text);

}

/* 
  Purpose: Resize status bar
  Created date: 07/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 07/08/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
void StatusBar_Resize(HWND hwndParent, HWND hStatus)
{

  RECT rc;

  if(hStatus == 0) return;
  GetClientRect(hwndParent, &rc);
  MoveWindow(hStatus, 0, rc.bottom - 20, rc.right, 20, TRUE);

}
