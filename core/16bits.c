 /*
  Scryvano - Lightweight text editor
  Original file name: 16bits.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
  
  This file contains portions derived from and reimplemented based onthe osFree "Notepad" project:
  https://github.com/osfree-project/notepad/blob/main/main.c
 
  The original osFree Notepad source is licensed under the GNU Lesser General Public License 
	version 2.1 (LGPL-2.1). Portions derived from the original work have been modified and incorporated into Scryvano 
	under the relicensing provision of LGPL-2.1 Section 3.
 
  Copyright notices and attribution for the original work are retained where applicable.
  Thanks to the osFree project and its contributors for their work and reference implementation.
  https://github.com/osfree-project	
*/
  
/* 
  Purpose: Return default font
  Created date: 07/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 19/08/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT and gemini
*/
HFONT getDefaultFont()
{

  LOGFONT lf;
  memset(&lf, 0, sizeof(lf));

  // font -12 o -13. 
  lf.lfHeight = -12; 
  lf.lfWidth = 0;
  lf.lfEscapement = 0;
  lf.lfOrientation = 0;
    
  // FW_SEMIBOLD | FW_NORMAL
  lf.lfWeight = FW_NORMAL; 
    
  lf.lfItalic = FALSE;
  lf.lfUnderline = FALSE;
  lf.lfStrikeOut = FALSE;
    
  // We force the ANSI set to look for vector TrueType fonts.
	lf.lfCharSet = ANSI_CHARSET; 
  lf.lfOutPrecision = OUT_TT_ONLY_PRECIS; // Only TrueType fonts
  lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  lf.lfQuality = DEFAULT_QUALITY;
  lf.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS; 

  lstrcpy(lf.lfFaceName, "Arial");
	
  return CreateFontIndirect(&lf);

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
  
  hFont = getDefaultFont();
	hdc = GetDC(0);
	hOldFont = (HFONT)SelectObject(hdc, hFont);

  GetTextMetrics(hdc, &tm);

  SelectObject(hdc, hOldFont);
  ReleaseDC(0, hdc);

  return tm.tmHeight;

}
