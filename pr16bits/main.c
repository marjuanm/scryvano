/*
  Scryvano - Lightweight text editor
  Original file name: main.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/

#include <io.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "../dialogs/about.h"

#include "../includes/constants.h"
#include "../includes/structures.h"
#include "../includes/core.h"
#include "../includes/configuration.h"
#include "../includes/dialogs/16bits.h"
#include "../includes/fs-operations/file.h"
#include "../includes/components/statusbar.h"

#include "../core/16bits.c"
#include "../core/configuration.c"
#include "../core/fs-operations/file.c"

#include "../core/components/16bits.c"
#include "../core/dialogs/16bits/about.c"
#include "../core/components/statusbar.c"

HMENU mnuMenu;

HMENU mnuFile, mnuEdit, mnuFind, mnuView;
HMENU mnuCharacter, mnuParagraph, mnuDocument;
HMENU mnuExecute, mnuPlugins, mnuWindow, mnuHelp;

HMENU mnuAbout;

HWND sbMain;

LRESULT FAR PASCAL WndProc(HWND, UINT, WPARAM, LPARAM);

/* 
  Purpose: Create the main window
  Created date: 05/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 13/08/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	int len;
	char *end;
	char *p, *start;
	WNDCLASS wc;
  MSG msg;
	HWND hwnd;
	
	int sw, sh, w, h, x, y;

  // initialize path
	
	GetModuleFileName(hInstance, currentpath, sizeof(currentpath));
	p = strrchr(currentpath, '\\');
	if(p != NULL) *(p + 1) = '\0';
	
	strcpy(confpath, currentpath);
	strcat(confpath, "scryvano.cfg");
	
	// load initial file in the parameter list
	
	if(lpCmdLine != NULL && lpCmdLine[0] != '\0')
  {
		
		start = lpCmdLine;
    
    // jump initial spaces
    
    while(*start == ' ' || *start == '\t')
			start++;

    if(*start == '"')
    {
			
			// parameter with commas
			
			start++;
			end = strchr(start, '"');

      if(end != NULL)
      {
				
				len = end - start;
				if(len >= MEDIUM_BUFFER) len = MEDIUM_BUFFER - 1;
				strncpy(initialfile, start, len);
				initialfile[len] = '\0';
            
			}
        
		}
    else
    {
			
			// parameter without commas
			
			end = start;
			while(*end != '\0' && *end != ' ' && *end != '\t') end++;
			len = end - start;
			if(len >= MEDIUM_BUFFER) len = MEDIUM_BUFFER - 1;
			strncpy(initialfile, start, len);
      initialfile[len] = '\0';
            
		}
        
	}
	
	// load configuration
	
	conf = getDefaultConfiguration();
	loadConfiguration();
	
  // create window
	
  frmMain = hInstance;

  if(!hPrevInstance)
  {
    	
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = 0;
    wc.lpszClassName = "SCRYVANO";

    RegisterClass(&wc);
        
  }
	
	// create main menu structure

	mnuMenu = CreateMenu();

	/* File */

	mnuFile = CreatePopupMenu();
	AppendMenu(mnuFile, MF_STRING, 1001, "Sample");
	AppendMenu(mnuMenu, MF_POPUP, (HMENU)mnuFile, "&File");

	/* Edit */

	mnuEdit = CreatePopupMenu();
	AppendMenu(mnuEdit, MF_STRING, 1002, "Sample");
	AppendMenu(mnuMenu, MF_POPUP, (HMENU)mnuEdit, "&Edit");

	/* Find */

	mnuFind = CreatePopupMenu();
	AppendMenu(mnuFind, MF_STRING, 1003, "Sample");
	AppendMenu(mnuMenu, MF_POPUP, (HMENU)mnuFind, "&Find");

	/* View */

	mnuView = CreatePopupMenu();
	AppendMenu(mnuView, MF_STRING, 1004, "Sample");
	AppendMenu(mnuMenu, MF_POPUP, (HMENU)mnuView, "&View");

	/* Document */

	mnuDocument = CreatePopupMenu();

	mnuCharacter = CreatePopupMenu();
	AppendMenu(mnuCharacter, MF_STRING, 1005, "Sample");

	mnuParagraph = CreatePopupMenu();
	AppendMenu(mnuParagraph, MF_STRING, 1006, "Sample");

	AppendMenu(mnuDocument, MF_POPUP, (HMENU)mnuCharacter, "&Character");
	AppendMenu(mnuDocument, MF_POPUP, (HMENU)mnuParagraph, "&Paragraph");

	AppendMenu(mnuMenu, MF_POPUP, (HMENU)mnuDocument, "&Document");

	/* Execute */

	mnuExecute = CreatePopupMenu();

	AppendMenu(mnuExecute, MF_STRING, 1007, "Sample");
	AppendMenu(mnuExecute, MF_SEPARATOR, 0, NULL);

	mnuPlugins = CreatePopupMenu();
	AppendMenu(mnuPlugins, MF_STRING, 1008, "Sample");

	AppendMenu(mnuExecute, MF_POPUP, (HMENU)mnuPlugins, "P&lugins");

	AppendMenu(mnuMenu, MF_POPUP, (HMENU)mnuExecute, "E&xecute");

	/* Window */

	mnuWindow = CreatePopupMenu();
	AppendMenu(mnuWindow, MF_STRING, 1009, "Sample");
	AppendMenu(mnuMenu, MF_POPUP, (HMENU)mnuWindow, "&Window");

	/* Help */

	mnuHelp = CreatePopupMenu();
	AppendMenu(mnuHelp, MF_STRING, IDD_ABOUT, "&About");
	AppendMenu(mnuMenu, MF_POPUP, (HMENU)mnuHelp, "&Help");
	
	// initialize window
	
	appInst = hInstance;
	
	sw = GetSystemMetrics(SM_CXSCREEN);
	sh = GetSystemMetrics(SM_CYSCREEN);
	w = floor(sw * 0.88);
	h = floor(sh * 0.71);
	x = floor((sw - w) / 2);
	y = floor((sh - h) / 3);

  hwnd = CreateWindow(
		"SCRYVANO", /* window class name */
    "Scryvano", /* window title */
		WS_OVERLAPPEDWINDOW,
		x,
		y,
		w,
		h,
		0,
		mnuMenu,
		hInstance,
		0);

  frmMain = hwnd;

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  while(GetMessage(&msg,0,0,0))
  {
		
		TranslateMessage(&msg);
    DispatchMessage(&msg);
    
	}

  return msg.wParam;

}

/* 
  Purpose: Window events processor
  Created date: 05/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 05/08/2026
  Last modified username: Juan Manuel Mar Hdz.
*/
LRESULT FAR PASCAL WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	HDC hdc;
	FARPROC lpfnAbout;
	
	switch(msg)
  {

    case WM_CREATE:

			sbMain = StatusBar_Create(
				hwnd, 
				"Ready",
				TRUE);
			
      return 0;

    case WM_SIZE:

      StatusBar_Resize(hwnd, sbMain);
			return 0;
			
		case WM_CTLCOLOR:
			
			hdc = (HDC)wParam;

			if((HWND)lParam == sbMain)
			{
        
				SetBkColor(hdc, RGB(255,255,255));
        SetTextColor(hdc, RGB(0,0,0));
        return (LRESULT)GetStockObject(WHITE_BRUSH);
    
			}
			
			return 0;
			
	    case WM_COMMAND:
    
			switch(LOWORD(wParam))
			{
				
        case IDD_ABOUT:
        {
					
					lpfnAbout = MakeProcInstance((FARPROC)AboutDlgProc, appInst);
					
					if (lpfnAbout != NULL)
					{
        
						DialogBoxParam(
							appInst,
							MAKEINTRESOURCE(IDD_ABOUT), 
							hwnd, 
							lpfnAbout, 
							(LPARAM)hwnd
						);

						FreeProcInstance((FARPROC)lpfnAbout);
    
					}
					
          return 0;
        
				}
    
			}
    
			return 0;
		
		case WM_DESTROY:
      
      PostQuitMessage(0);
      return 0;
    
	}

  return DefWindowProc(hwnd,msg,wParam,lParam);

}
