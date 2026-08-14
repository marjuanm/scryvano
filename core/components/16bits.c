/*
  Scryvano - Lightweight text editor
  Original file name: 16bits.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/

/* 
  Purpose: Return created window
  Created date: 07/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 07/08/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT and gemini
*/
HWND StatusBar_CreateWindow(HWND hwndParent, LPCSTR text, BOOL simplestyle)
{
	
	RECT rc;
  static char buffer[256];

  strcpy(buffer, " ");
  strcat(buffer, text);

  GetClientRect(hwndParent, &rc);

  return CreateWindow(
    "STATIC",
    buffer,
    WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER,
    0,
    rc.bottom - 20,
    rc.right,
    20,
    hwndParent,
    0,
    appInst,
    0
  );
	
}
