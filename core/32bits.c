/*
  Scryvano - Lightweight text editor
  Original file name: 32bits.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/

/* 
  Purpose: Return default font
  Created date: 07/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 26/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
HFONT getDefaultFont()
{
	
	NONCLIENTMETRICS ncm;
  memset(&ncm, 0, sizeof(NONCLIENTMETRICS));
  ncm.cbSize = sizeof(NONCLIENTMETRICS);

  // get system client area meters
  if(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0))
		return CreateFontIndirect(&ncm.lfMenuFont);
  else
		return (HFONT)GetStockObject(DEFAULT_GUI_FONT);

}

/* 
  Purpose: Return default font height
  Created date: 08/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 08/08/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
int getDefaultFontHeight()
{

  HDC hdc;
	TEXTMETRIC tm;
  HFONT hFont, hOldFont;

  hFont = (HFONT)getDefaultFont();
  hdc = GetDC(NULL);
  hOldFont = (HFONT)SelectObject(hdc, hFont);

  GetTextMetrics(hdc, &tm);

  SelectObject(hdc, hOldFont);
  ReleaseDC(NULL, hdc);

  return tm.tmHeight;

}
