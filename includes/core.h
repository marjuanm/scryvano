/*
  Scryvano - Lightweight text editor
  Original file name: core.h
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/ 

#ifndef CORE_H
#define CORE_H

HWND H_WINDOW;
HWND H_STATUSBAR;
HINSTANCE appInst;

HWND H_SINGLE_EDITOR;

char language[SMALL_BUFFER];
char confpath[LARGE_BUFFER];
char currentpath[LARGE_BUFFER];
char translatefile[SMALL_BUFFER];
char defaultstatusbar[SMALL_BUFFER];

HFONT getDefaultFont();
void resizeEditor(HWND);
int getDefaultFontHeight();
HFONT getDefaultFontWithSize(int);

#endif
