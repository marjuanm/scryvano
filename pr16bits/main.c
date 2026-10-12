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
#include "../includes/os.h"
#include "../includes/ini.h"
#include "../includes/core.h"
#include "../includes/dialogs/16bits.h"
#include "../includes/fs-operations/file.h"
#include "../includes/fs-operations/folder.h"
#include "../includes/configuration/basic.h"
#include "../includes/configuration/language.h"

#include "../includes/components/statusbar.h"

#include "../core/ini.c"
#include "../core/16bits.c"
#include "../core/commons.c"
#include "../core/os/16bits.c"
#include "../core/fs-operations/file.c"
#include "../core/fs-operations/folder.c"
#include "../core/configuration/basic.c"
#include "../core/configuration/language.c"
#include "../core/configuration/16bits.c"

#include "../core/dialogs/16bits/about.c"
#include "../core/components/statusbar.c"

HMENU H_MENU;

HMENU IDR_MFILE, IDR_MEDIT, IDR_MFIND, IDR_MVIEW;
HMENU IDR_MCHARACTER, IDR_MPARAGRAPH, IDR_MDOCUMENT;
HMENU IDR_MEXECUTE, IDR_MPLUGINS, IDR_MWINDOW, IDR_MHELP;

LRESULT FAR PASCAL WndProc(HWND, UINT, WPARAM, LPARAM);

/* 
  Purpose: Create the main window
  Created date: 05/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 01/10/2026
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
	
	// get os details
	
	if(strcasecmp(confpath, "/")	== 0)
		separator = '/';
	else
		separator = '\\';
	
	osbits = getOSBits();
	getOSFlavor(osflavor);

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

	H_MENU = CreateMenu();

	/* File */
	
	IDR_MFILE = CreatePopupMenu();
	
	/* submenu new */
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&New", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_file", "new", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&New", sizeof(menutext) - 1);
				
	}
	
	AppendMenu(IDR_MFILE, MF_STRING, IDR_MNEW, menutext);
	
	/* submenu new */
	
	/* submenu exit */
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Exit", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_file", "exit", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Exit", sizeof(menutext) - 1);
				
	}
	
	AppendMenu(IDR_MFILE, MF_SEPARATOR, 0, NULL);
	AppendMenu(IDR_MFILE, MF_STRING, IDR_MEXIT, menutext);
	
	/* submenu exit */
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&File", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "file", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&File", sizeof(menutext) - 1);
				
	}
	
	AppendMenu(H_MENU, MF_POPUP, (HMENU)IDR_MFILE, menutext);
	
	/* File */

	/* Edit */
	
  if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Edit", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "edit", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Edit", sizeof(menutext) - 1);
				
	}

	IDR_MEDIT = CreatePopupMenu();
	AppendMenu(IDR_MEDIT, MF_STRING, 1002, "Sample");
	AppendMenu(H_MENU, MF_POPUP, (HMENU)IDR_MEDIT, menutext);

	/* Find */
	
  if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Find", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "find", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Find", sizeof(menutext) - 1);
				
	}

	IDR_MFIND = CreatePopupMenu();
	AppendMenu(IDR_MFIND, MF_STRING, 1003, "Sample");
	AppendMenu(H_MENU, MF_POPUP, (HMENU)IDR_MFIND, menutext);

	/* View */
	
	IDR_MVIEW = CreatePopupMenu();
	
	/* submenu statusbar */
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Status bar", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_view", "statusbar", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Status bar", sizeof(menutext) - 1);
				
	}
	
	AppendMenu(IDR_MVIEW, MF_STRING, IDR_MSTATUSBAR, menutext);
	
	/* submenu statusbar */

	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&View", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "view", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&View", sizeof(menutext) - 1);
				
	}

	AppendMenu(H_MENU, MF_POPUP, (HMENU)IDR_MVIEW, menutext);
	
	/* View */

	/* Document */

	IDR_MDOCUMENT = CreatePopupMenu();

	IDR_MCHARACTER = CreatePopupMenu();
	AppendMenu(IDR_MCHARACTER, MF_STRING, 1005, "Sample");

	IDR_MPARAGRAPH = CreatePopupMenu();
	AppendMenu(IDR_MPARAGRAPH, MF_STRING, 1006, "Sample");
	
	AppendMenu(IDR_MDOCUMENT, MF_POPUP, (HMENU)IDR_MCHARACTER, "&Character");
	AppendMenu(IDR_MDOCUMENT, MF_POPUP, (HMENU)IDR_MPARAGRAPH, "&Paragraph");
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Document", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "document", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Document", sizeof(menutext) - 1);
				
	}

	AppendMenu(H_MENU, MF_POPUP, (HMENU)IDR_MDOCUMENT, menutext);

	/* Execute */

	IDR_MEXECUTE = CreatePopupMenu();

	AppendMenu(IDR_MEXECUTE, MF_STRING, 1007, "Sample");
	AppendMenu(IDR_MEXECUTE, MF_SEPARATOR, 0, NULL);

	IDR_MPLUGINS = CreatePopupMenu();
	AppendMenu(IDR_MPLUGINS, MF_STRING, 1008, "Sample");

	AppendMenu(IDR_MEXECUTE, MF_POPUP, (HMENU)IDR_MPLUGINS, "P&lugins");
	
  if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "E&xecute", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "execute", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "E&xecute", sizeof(menutext) - 1);
				
	}

	AppendMenu(H_MENU, MF_POPUP, (HMENU)IDR_MEXECUTE, menutext);

	/* Window */
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Window", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "window", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Window", sizeof(menutext) - 1);
				
	}

	IDR_MWINDOW = CreatePopupMenu();
	AppendMenu(IDR_MWINDOW, MF_STRING, 1009, "Sample");
	AppendMenu(H_MENU, MF_POPUP, (HMENU)IDR_MWINDOW, menutext);

	/* Help */

	IDR_MHELP = CreatePopupMenu();
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&About of Scryvano", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_about", "about", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&About of Scryvano", sizeof(menutext) - 1);
				
	}
	
	AppendMenu(IDR_MHELP, MF_SEPARATOR, 0, NULL);
	AppendMenu(IDR_MHELP, MF_STRING, IDD_ABOUT, menutext);
	
	if(stricmp(conf.language, "en") == 0)
		strncpy(menutext, "&Help", sizeof(menutext) - 1);
	else
	{
		
		status = readINIkey("menu_list", "help", menutext, sizeof(menutext), translatefile);
		if(status == FALSE) strncpy(menutext, "&Help", sizeof(menutext) - 1);
				
	}
	  
	AppendMenu(H_MENU, MF_POPUP, (HMENU)IDR_MHELP, menutext);
	
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
		H_MENU,
		hInstance,
		0);

  H_WINDOW = hwnd;

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
  Last modified date: 08/10/2026
  Last modified username: Juan Manuel Mar Hdz.
	Thanks to chatgpt and gemini
*/
LRESULT FAR PASCAL WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	HDC hdc;
	RECT statusRect;
	FARPROC lpfnAbout;
	char path[SMALL_BUFFER];
	int width, height, statusHeight;

	switch(msg)
  {

		case WM_CREATE:
		
			// create text editor
			
			H_SINGLE_EDITOR = CreateWindow(
        "EDIT",
        "",
        WS_CHILD |
        WS_VISIBLE |
        WS_BORDER |
        ES_MULTILINE |
        ES_AUTOVSCROLL |
        ES_AUTOHSCROLL |
        WS_VSCROLL |
        WS_HSCROLL,
        0,
        0,
        0,
        0,
        hwnd,
        (HMENU)1001,
        appInst,
        0
			);
			
			SendMessage(H_SINGLE_EDITOR, WM_SETFONT, (WPARAM)getDefaultFont(), TRUE);
			
			// create statusbar
			
			strncpy(path, "c:\\windows\\command", sizeof(path) - 1); 
			
			if(folder_exists(path) == TRUE)
			{
				
				strncpy(path, "c:\\windows\\system32", sizeof(path) - 1); 
				
				if(folder_exists(path) == TRUE)
				{
					
					H_STATUSBAR = StatusBarCreate(
						hwnd, 
						appInst, 
						0, 
						STATUSBAR_SIMPLE, 
						STATUSBAR_SMALL_HEIGHT2 - 4
					);
					
				}
				else
				{
					
					H_STATUSBAR = StatusBarCreate(
						hwnd, 
						appInst, 
						0, 
						STATUSBAR_SIMPLE, 
						STATUSBAR_SMALL_HEIGHT1
					);
					
				}
				
			}
			else
			{
				
				H_STATUSBAR = StatusBarCreate(
					hwnd, 
					appInst, 
					0, 
					STATUSBAR_SIMPLE, 
					STATUSBAR_SMALL_HEIGHT1 + 2
				);
				
			}

      return 0;

    case WM_SIZE:

			width = LOWORD(lParam);
      height = HIWORD(lParam);
		
			// attach statusbar
			StatusBarResize(H_STATUSBAR, width, height);
			
			// attach editor
			
			GetClientRect(H_STATUSBAR, &statusRect);
			statusHeight = statusRect.bottom;
			MoveWindow(H_SINGLE_EDITOR, 0, 0, width, height - statusHeight, TRUE);
			
			resizeEditor(hwnd); // resize editor area
			return 0;
					
		case WM_CTLCOLOR:
			
			if((HWND)lParam == H_STATUSBAR)
			{
        
				hdc = (HDC)wParam;
        SetBkColor(hdc, RGB(255, 255, 255));
        SetTextColor(hdc, RGB(0, 0, 0));
        return (LRESULT)GetStockObject(WHITE_BRUSH);
				
			}

			return 0;
			
	  case WM_COMMAND:
    
			switch(LOWORD(wParam))
			{
				
				case IDR_MNEW:
        {
					
					//StatusBarSetText(IDR_STATUSBAR, "Prueba statusbar");
          return 0;
        
				}
				
        case IDR_MEXIT:
        {
					
					//StatusBarClearFields(IDR_STATUSBAR);
					SendMessage(hwnd, WM_CLOSE, 0, 0);
          return 0;
        
				}
				
				case IDR_MSTATUSBAR:
				{
					
					if(IsWindowVisible(H_STATUSBAR))
						ShowWindow(H_STATUSBAR, SW_HIDE);
					else
						ShowWindow(H_STATUSBAR, SW_SHOW);
			
					resizeEditor(hwnd); // resize editor area
					return 0;
					
				}
				
        case IDD_ABOUT:
        {
					
					lpfnAbout = MakeProcInstance((FARPROC)AboutDlgProc, appInst);
					
					if(lpfnAbout != NULL)
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
      
			if(H_MENU)
      {
        
				DestroyMenu(H_MENU);
        H_MENU = 0;
    
			}

			UnregisterClass(StatusBarClassName, appInst);
			PostQuitMessage(0);
			
			return 0;
    
	}

  return DefWindowProc(hwnd,msg,wParam,lParam);

}
