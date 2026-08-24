/*
  Scryvano - Lightweight text editor
  Original file name: main.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
	Special thanks to the Flaticon project for the icon used for the Scryvano executable.
	You can view the original image at https://www.flaticon.es/icono-gratis/pluma_11073685?term=pluma+de+escribir&page=1&position=2&origin=search&related_id=11073685
*/

#include <io.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "../dialogs/about.h"

#include "../includes/constants.h"
#include "../includes/structures.h"
#include "../includes/ini.h"
#include "../includes/core.h"
#include "../includes/dialogs/16bits.h"
#include "../includes/fs-operations/file.h"
#include "../includes/configuration/basic.h"
#include "../includes/configuration/language.h"

#include "../includes/components/statusbar.h"

#include "../core/ini.c"
#include "../core/16bits.c"
#include "../core/fs-operations/file.c"
#include "../core/configuration/basic.c"
#include "../core/configuration/language.c"
#include "../core/configuration/16bits.c"

#include "../core/components/16bits.c"
#include "../core/dialogs/16bits/about.c"
#include "../core/components/statusbar.c"

HMENU IDD_MENU;

HMENU IDD_MFILE, IDD_MEDIT, IDD_MFIND, IDD_MVIEW;
HMENU IDD_MCHARACTER, IDD_MPARAGRAPH, IDD_MDOCUMENT;
HMENU IDD_MEXECUTE, IDD_MPLUGINS, IDD_MWINDOW, IDD_MHELP;

HWND IDD_SMAIN;

LRESULT FAR PASCAL WndProc(HWND, UINT, WPARAM, LPARAM);

/* 
  Purpose: Create the main window
  Created date: 05/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 24/08/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	int len;
	MSG msg;
	HWND hwnd;
	WNDCLASS wc = {0};
	char *end, *p, *start;
	int sw, sh, w, h, x, y, status;
	char menutext[MEDIUM_BUFFER], initialfile[LARGE_BUFFER];

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
	loadConfiguration(); // get configuration from .cfg file, load in the main structure and set translation file path in translatefile var
	if(translatefile[0] == '\0') strncpy(conf.language, "en", sizeof(conf.language) - 1);
	
  // load default statusbar string
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(defaultstatusbar, "Ready", sizeof(defaultstatusbar) - 1);
	else
	{
		
		status = readINIkey("status_bar", "defaulttext", defaultstatusbar, sizeof(defaultstatusbar), translatefile);
		if(status == FALSE) strncpy(defaultstatusbar, "Ready", sizeof(defaultstatusbar) - 1);
				
	}
	
  // create window

  if(!hPrevInstance)
  {
    	
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
		wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = 0;
    wc.lpszClassName = "SCRYVANO";

    RegisterClass(&wc);
        
  }
	
	// create main menu structure

	IDD_MENU = CreateMenu();

	/* File */
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&File", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "file", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&File", sizeof(menutext) - 1);
				
	}

	IDD_MFILE = CreatePopupMenu();
	
	/* submenu new */
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&New", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_file", "new", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&New", sizeof(menutext) - 1);
				
	}
	
	AppendMenu(IDD_MFILE, MF_STRING, IDD_NEW, menutext);
	
	/* submenu new */
	
	/* submenu exit */
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Exit", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_file", "exit", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Exit", sizeof(menutext) - 1);
				
	}
	
	AppendMenu(IDD_MFILE, MF_SEPARATOR, 0, NULL);
	AppendMenu(IDD_MFILE, MF_STRING, IDD_EXIT, menutext);
	
	/* submenu exit */
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&File", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "file", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&File", sizeof(menutext) - 1);
				
	}
	
	AppendMenu(IDD_MENU, MF_POPUP, (HMENU)IDD_MFILE, menutext);

	/* Edit */
	
  if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Edit", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "edit", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Edit", sizeof(menutext) - 1);
				
	}

	IDD_MEDIT = CreatePopupMenu();
	AppendMenu(IDD_MEDIT, MF_STRING, 1002, "Sample");
	AppendMenu(IDD_MENU, MF_POPUP, (HMENU)IDD_MEDIT, menutext);

	/* Find */
	
  if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Find", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "find", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Find", sizeof(menutext) - 1);
				
	}

	IDD_MFIND = CreatePopupMenu();
	AppendMenu(IDD_MFIND, MF_STRING, 1003, "Sample");
	AppendMenu(IDD_MENU, MF_POPUP, (HMENU)IDD_MFIND, menutext);

	/* View */

	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&View", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "view", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&View", sizeof(menutext) - 1);
				
	}
	

	IDD_MVIEW = CreatePopupMenu();
	AppendMenu(IDD_MVIEW, MF_STRING, 1004, "Sample");
	AppendMenu(IDD_MENU, MF_POPUP, (HMENU)IDD_MVIEW, menutext);

	/* Document */

	IDD_MDOCUMENT = CreatePopupMenu();

	IDD_MCHARACTER = CreatePopupMenu();
	AppendMenu(IDD_MCHARACTER, MF_STRING, 1005, "Sample");

	IDD_MPARAGRAPH = CreatePopupMenu();
	AppendMenu(IDD_MPARAGRAPH, MF_STRING, 1006, "Sample");
	
	AppendMenu(IDD_MDOCUMENT, MF_POPUP, (HMENU)IDD_MCHARACTER, "&Character");
	AppendMenu(IDD_MDOCUMENT, MF_POPUP, (HMENU)IDD_MPARAGRAPH, "&Paragraph");
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Document", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "document", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Document", sizeof(menutext) - 1);
				
	}

	AppendMenu(IDD_MENU, MF_POPUP, (HMENU)IDD_MDOCUMENT, menutext);

	/* Execute */

	IDD_MEXECUTE = CreatePopupMenu();

	AppendMenu(IDD_MEXECUTE, MF_STRING, 1007, "Sample");
	AppendMenu(IDD_MEXECUTE, MF_SEPARATOR, 0, NULL);

	IDD_MPLUGINS = CreatePopupMenu();
	AppendMenu(IDD_MPLUGINS, MF_STRING, 1008, "Sample");

	AppendMenu(IDD_MEXECUTE, MF_POPUP, (HMENU)IDD_MPLUGINS, "P&lugins");
	
  if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "E&xecute", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "execute", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "E&xecute", sizeof(menutext) - 1);
				
	}

	AppendMenu(IDD_MENU, MF_POPUP, (HMENU)IDD_MEXECUTE, menutext);

	/* Window */
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Window", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "window", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Window", sizeof(menutext) - 1);
				
	}

	IDD_MWINDOW = CreatePopupMenu();
	AppendMenu(IDD_MWINDOW, MF_STRING, 1009, "Sample");
	AppendMenu(IDD_MENU, MF_POPUP, (HMENU)IDD_MWINDOW, menutext);

	/* Help */

	IDD_MHELP = CreatePopupMenu();
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&About of Scryvano", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_about", "about", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&About of Scryvano", sizeof(menutext) - 1);
				
	}
	
	AppendMenu(IDD_MHELP, MF_SEPARATOR, 0, NULL);
	AppendMenu(IDD_MHELP, MF_STRING, IDD_ABOUT, menutext);
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Help", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "help", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Help", sizeof(menutext) - 1);
				
	}
	  
	AppendMenu(IDD_MENU, MF_POPUP, (HMENU)IDD_MHELP, menutext);
	
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
		IDD_MENU,
		hInstance,
		0);

  IDD_FMAIN = hwnd;

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
  Last modified date: 21/08/2026
  Last modified username: Juan Manuel Mar Hdz.
*/
LRESULT FAR PASCAL WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	HDC hdc;
	FARPROC lpfnAbout;
	
	switch(msg)
  {

    case WM_CREATE:

			IDD_SMAIN = StatusBar_Create(
				hwnd, 
				defaultstatusbar,
				TRUE);
			
      return 0;

    case WM_SIZE:

      StatusBar_Resize(hwnd, IDD_SMAIN);
			return 0;
			
		case WM_CTLCOLOR:
			
			hdc = (HDC)wParam;

			if((HWND)lParam == IDD_SMAIN)
			{
        
				SetBkColor(hdc, RGB(255,255,255));
        SetTextColor(hdc, RGB(0,0,0));
        return (LRESULT)GetStockObject(WHITE_BRUSH);
    
			}
			
			return 0;
			
	    case WM_COMMAND:
    
			switch(LOWORD(wParam))
			{
				
        case IDD_EXIT:
        {
					
					SendMessage(hwnd, WM_CLOSE, 0, 0);
          return 0;
        
				}
				
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
