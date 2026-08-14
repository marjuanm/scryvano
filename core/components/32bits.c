/*
  Scryvano - Lightweight text editor
  Original file name: 32bits.c
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
	LPCSTR res;
	char buffer[256]; 
	
	strcpy(buffer, " ");
	strcat(buffer, text);
	res = buffer;
	
	GetClientRect(hwndParent, &rc);
	
	if(simplestyle == TRUE)
	  return CreateWindow(
			"STATIC",
			res,
			WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP | SS_CENTERIMAGE,
			0,
			rc.bottom - 20,
			rc.right,
			20,
			hwndParent,
			NULL,
			appInst,
			NULL);
	else
		return CreateWindow(
			STATUSCLASSNAME,
			res,
			WS_CHILD | WS_VISIBLE,
			0,
			0,
			0,
			0,
			hwndParent,
			NULL,
			appInst,
			NULL);
		
}
