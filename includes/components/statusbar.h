/*
  Scryvano - Lightweight text editor
  Original file name: statusbar.h
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/ 

#ifndef STATUSBAR_H
#define STATUSBAR_H

HWND StatusBar_Create(HWND, LPCSTR, BOOL);
void StatusBar_SetText(HWND, LPCSTR);
void StatusBar_Resize(HWND, HWND);

#endif
