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
#include <commctrl.h>

#include "../dialogs/about.h"

#include "../includes/constants.h"
#include "../includes/structures.h"
#include "../includes/core.h"
#include "../includes/configuration.h"
#include "../includes/dialogs/32bits.h"
#include "../includes/fs-operations/file.h"
#include "../includes/components/statusbar.h"

#include "../core/32bits.c"
#include "../core/configuration.c"
#include "../core/fs-operations/file.c"

#include "../core/components/32bits.c"
#include "../core/dialogs/32bits/about.c"
#include "../core/components/statusbar.c"

HMENU mnuMenu;

HMENU mnuFile, mnuEdit, mnuFind, mnuView;
HMENU mnuCharacter, mnuParagraph, mnuDocument;
HMENU mnuExecute, mnuPlugins, mnuWindow, mnuHelp;

HMENU mnuAbout;

HWND sbMain;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/* 
  Purpose: Create the main window
  Created date: 05/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 13/08/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	int len;
	char *end;
	char *p, *start;
	WNDCLASS wc = {0};
	MSG msg;
	HWND hwnd;
	
	// initialize path
	
	GetModuleFileName(NULL, currentpath, sizeof(currentpath));
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
	
	// create window
	
  InitCommonControls();

  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WndProc;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wc.lpszClassName = "SCRYVANO";

  RegisterClass(&wc);
	
	// load configuration
	
	conf = getDefaultConfiguration();
	loadConfiguration();
	
  // create main menu structure

	mnuMenu = CreateMenu();

	/* File */

	mnuFile = CreatePopupMenu();
	AppendMenu(mnuFile, MF_STRING, 1001, "Sample");
	AppendMenu(mnuMenu, MF_POPUP, (UINT_PTR)mnuFile, "&File");

	/* Edit */

	mnuEdit = CreatePopupMenu();
	AppendMenu(mnuEdit, MF_STRING, 1002, "Sample");
	AppendMenu(mnuMenu, MF_POPUP, (UINT_PTR)mnuEdit, "&Edit");

	/* Find */

	mnuFind = CreatePopupMenu();
	AppendMenu(mnuFind, MF_STRING, 1003, "Sample");
	AppendMenu(mnuMenu, MF_POPUP, (UINT_PTR)mnuFind, "&Find");

	/* View */

	mnuView = CreatePopupMenu();
	AppendMenu(mnuView, MF_STRING, 1004, "Sample");
	AppendMenu(mnuMenu, MF_POPUP, (UINT_PTR)mnuView, "&View");

	/* Document */

	mnuDocument = CreatePopupMenu();

	mnuCharacter = CreatePopupMenu();
	AppendMenu(mnuCharacter, MF_STRING, 1005, "Sample");

	mnuParagraph = CreatePopupMenu();
	AppendMenu(mnuParagraph, MF_STRING, 1006, "Sample");

	AppendMenu(mnuDocument, MF_POPUP, (UINT_PTR)mnuCharacter, "&Character");
	AppendMenu(mnuDocument, MF_POPUP, (UINT_PTR)mnuParagraph, "&Paragraph");

	AppendMenu(mnuMenu, MF_POPUP, (UINT_PTR)mnuDocument, "&Document");

	/* Execute */

	mnuExecute = CreatePopupMenu();

	AppendMenu(mnuExecute, MF_STRING, 1007, "Sample");
	AppendMenu(mnuExecute, MF_SEPARATOR, 0, NULL);

	mnuPlugins = CreatePopupMenu();
	AppendMenu(mnuPlugins, MF_STRING, 1008, "Sample");

	AppendMenu(mnuExecute, MF_POPUP, (UINT_PTR)mnuPlugins, "P&lugins");

	AppendMenu(mnuMenu, MF_POPUP, (UINT_PTR)mnuExecute, "E&xecute");

	/* Window */

	mnuWindow = CreatePopupMenu();
	AppendMenu(mnuWindow, MF_STRING, 1009, "Sample");
	AppendMenu(mnuMenu, MF_POPUP, (UINT_PTR)mnuWindow, "&Window");

	/* Help */

	mnuHelp = CreatePopupMenu();
	AppendMenu(mnuHelp, MF_STRING, IDD_ABOUT, "&About");
	AppendMenu(mnuMenu, MF_POPUP, (UINT_PTR)mnuHelp, "&Help");

  // initialize window
	
	appInst = hInstance;
	
  hwnd = CreateWindow(
    "SCRYVANO", /* window class name */
    "Scryvano", /* window title */
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    640,
    480,
    NULL,
    mnuMenu,
    hInstance,
    NULL);
		
	frmMain = hwnd;

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  while(GetMessage(&msg,NULL,0,0))
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
  Last modified date: 07/08/2026
  Last modified username: Juan Manuel Mar Hdz.
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch(msg)
  {

    case WM_CREATE:

			sbMain = StatusBar_Create(
				hwnd, 
				"Ready",
				FALSE);
			
      return 0;

    case WM_SIZE:

      StatusBar_Resize(hwnd, sbMain);
			return 0;
			
		case WM_COMMAND:
    
			switch(LOWORD(wParam))
			{
				
        case IDD_ABOUT:
        {
					
					DialogBoxParam(
						GetModuleHandle(NULL), 
						MAKEINTRESOURCE(IDD_ABOUT), 
						hwnd, 
						AboutDlgProc, 
						(LPARAM)hwnd // parent to dialog
					);

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
