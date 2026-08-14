/*
  Scryvano - Lightweight text editor
  Original file name: core.h
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/ 

#ifndef CORE_H
#define CORE_H

HWND frmMain;
HINSTANCE appInst;

char language[SMALL_BUFFER];

char confpath[LARGE_BUFFER];
char initialfile[LARGE_BUFFER];
char currentpath[LARGE_BUFFER];

HFONT getDefaultFont();
int getDefaultFontHeight();

#endif
