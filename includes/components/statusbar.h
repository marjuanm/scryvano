/*
  Scryvano - Lightweight text editor
  Original file name: statusbar.h
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/ 

/*
  Scryvano - Lightweight text editor
  Original file name: statusbar.h
	New file name: basic.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.

	This file contains portions derived from and reimplemented based on WinVi project Copyright (C) 1994-2007 Raphael Molle
	https://github.com/FigBug/WinVi/blob/master/Status.h
 
  The original source is licensed under the General Public License version (GPL). 
	Portions derived from the original work have been modified and incorporated into Scryvano project.
 
  Copyright notices and attribution for the original work are retained where applicable.
  Thanks to the WinVi project and contributors for their work and reference implementation.
  https://www.winvi.de/en | https://github.com/FigBug/WinVi
*/

#ifndef STATUSBAR_H
#define STATUSBAR_H

#define STATUSBAR_SIMPLE 0
#define STATUSBAR_FIELDS 1
#define STATUS_ALIGN_LEFT 0
#define STATUS_ALIGN_RIGHT 2
#define STATUS_ALIGN_CENTER 1
#define STATUSBAR_MAX_FIELDS 4
#define STATUSBAR_EXTRA_LARGE_HEIGHT1 42
#define STATUSBAR_EXTRA_LARGE_HEIGHT2 48
#define STATUSBAR_LARGE_HEIGHT 38
#define STATUSBAR_MIDDLE_HEIGHT 30
#define STATUSBAR_SMALL_HEIGHT2 25
#define STATUSBAR_SMALL_HEIGHT1 20

// statusbar field
typedef struct
{

  int width;
  UINT align;
  BOOL lowered;
  char text[MEDIUM_BUFFER];
	
} STATUSFIELD;

// statusbar data
typedef struct 
{
  
  int mode;
  int height;
	HFONT hFont;
	int fieldCount;
  char simpleText[MEDIUM_BUFFER];
  STATUSFIELD fields[STATUSBAR_MAX_FIELDS];
	
} STATUSBARDATA;

STATUSBARDATA statusBarData;
char StatusBarClassName[] = "StatusBar";

int StatusBarGetHeight(HWND);
void StatusBarClearFields(HWND);
void StatusBarSetMode(HWND, int);
void StatusBarSetHeight(HWND, int);
void StatusBarSetText(HWND, LPCSTR);
void StatusBarResize(HWND, int, int);
void StatusBarSetFieldWidth(HWND, int, int);
void StatusBarSetFieldAlign(HWND, int, UINT);
void StatusBarSetFieldText(HWND, int, LPCSTR);
void StatusBarSetFieldLowered(HWND, int, BOOL);
HWND StatusBarCreate(HWND, HINSTANCE, int, int, int);
void StatusBarDrawField(HDC, RECT *, STATUSFIELD *, HFONT);
LRESULT CALLBACK StatusBarWndProc(HWND, UINT, WPARAM, LPARAM);

#endif
