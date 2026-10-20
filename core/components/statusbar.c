/*
  Scryvano - Lightweight text editor
  Original file name: statusbar.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.

	This file contains portions derived from and reimplemented based on WinVi project Copyright (C) 1994-2007 Raphael Molle
	https://github.com/FigBug/WinVi/blob/master/Status.c
 
  The original source is licensed under the General Public License version (GPL). 
	Portions derived from the original work have been modified and incorporated into Scryvano project.
 
  Copyright notices and attribution for the original work are retained where applicable.
  Thanks to the WinVi project and contributors for their work and reference implementation.
  https://www.winvi.de/en | https://github.com/FigBug/WinVi
*/

/* 
  Purpose: Register statusbar class
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 06/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
static BOOL StatusBarRegisterClass(HINSTANCE hInstance)
{
	
	WNDCLASS wc;
	
	if(GetClassInfo(hInstance, StatusBarClassName, &wc))
		return TRUE;
	
	wc.style = 0;
  wc.lpfnWndProc = StatusBarWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof(LONG);
  wc.hInstance = hInstance;
  wc.hIcon = 0;
  wc.hCursor = LoadCursor(0, IDC_ARROW);
  wc.hbrBackground = 0;
  wc.lpszMenuName = 0;
  wc.lpszClassName = StatusBarClassName;

  return RegisterClass(&wc) != 0;

}

/* 
  Purpose: Create statusbar
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 28/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
HWND StatusBarCreate(HWND hwndParent, HINSTANCE hInstance, int id, int mode, int height)
{
	
	HWND hwndStatus;
	
	if(!StatusBarRegisterClass(hInstance))
		return 0;

	// initialize basic statusbar
  statusBarData.mode = mode;
  statusBarData.height = height;
  statusBarData.fieldCount = STATUSBAR_MAX_FIELDS;
	statusBarData.hFont = (HFONT)getDefaultFont();
	
	hwndStatus = CreateWindow(
    StatusBarClassName,
    "",
    WS_CHILD | WS_VISIBLE,
    0,
    0,
    0,
    height,
    hwndParent,
    (HMENU)id,
    hInstance,
    0
  );

  if(hwndStatus == 0)
    return 0;

  H_STATUSBAR = hwndStatus;
  StatusBarClearFields(hwndStatus); // initialize fields
	
  return hwndStatus;
	
}

/* 
  Purpose: Set style
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 06/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
void StatusBarSetMode(HWND hwndStatus, int mode)
{

  statusBarData.mode = mode;

  /*InvalidateRect(
        hwndStatus,
        0,
        TRUE
    );*/

}

/* 
  Purpose: Set text on the first field
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 06/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
void StatusBarSetText(HWND hwndStatus, LPCSTR text)
{
	
	if(text == 0)
    text = "";

	StatusBarSetFieldText(hwndStatus, 0, text);

    /*InvalidateRect(
        hwndStatus,
        0,
        TRUE
    );*/
}

/* 
  Purpose: Set text on field index
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 26/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
void StatusBarSetFieldText(HWND hwndStatus, int field, LPCSTR text)
{
	
	if(field < 0 || field >= STATUSBAR_MAX_FIELDS)
		return;

  if (text == 0)
    text = "";
	
	if(field == 0)
	{
		
		//lstrcpy(statusBarData.simpleText, " ");
		//lstrcat(statusBarData.simpleText, text);
		lstrcpy(statusBarData.simpleText, text);
		
		
	}

	lstrcpyn(statusBarData.fields[field].text, text, sizeof(statusBarData.fields[field].text));

	// redraw statusbar
  InvalidateRect(hwndStatus, 0, TRUE);
	
}

/* 
  Purpose: Set field with
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 06/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
void StatusBarSetFieldWidth(HWND hwndStatus, int field, int width)
{
	
	if(field < 0 || field >= STATUSBAR_MAX_FIELDS)
		return;
	
	if(width < 0)
		width = 0;

  statusBarData.fields[field].width = width;

    /*InvalidateRect(
        hwndStatus,
        0,
        TRUE
    );*/
}

/* 
  Purpose: Set field align
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 06/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
void StatusBarSetFieldAlign(HWND hwndStatus, int field, UINT align)
{
	
	if(field < 0 || field >= STATUSBAR_MAX_FIELDS)
		return;

  statusBarData.fields[field].align = align;

    /*InvalidateRect(
        hwndStatus,
        0,
        TRUE
    );*/
}

/* 
  Purpose: Set activate / deactivate lowered style
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 06/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
void StatusBarSetFieldLowered(HWND hwndStatus, int field, BOOL lowered)
{
	
	if(field < 0 || field >= STATUSBAR_MAX_FIELDS)
    return;

  statusBarData.fields[field].lowered = lowered;

    /*InvalidateRect(
        hwndStatus,
        0,
        TRUE
    );*/
}

/* 
  Purpose: Clear fields
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 26/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
void StatusBarClearFields(HWND hwndStatus)
{

  int i;

  for(i=0; i<STATUSBAR_MAX_FIELDS; i++)
	{
		
		if(i == 0)
		{
			
			// set default text and font style
			//lstrcpy(statusBarData.fields[0].text, " ");
			//lstrcat(statusBarData.fields[0].text, defaultstatusbar);
			lstrcpy(statusBarData.fields[0].text, defaultstatusbar);

		}
		else
			statusBarData.fields[i].text[0] = '\0';
		
	}
	
	// set default text and font style
  //lstrcpy(statusBarData.simpleText, " ");
	//lstrcat(statusBarData.simpleText, defaultstatusbar);
	lstrcpy(statusBarData.simpleText, defaultstatusbar);

	// redraw statusbar
  InvalidateRect(hwndStatus, 0, TRUE);
	
}

/* 
  Purpose: Set field height
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 06/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
void StatusBarSetHeight(HWND hwndStatus, int height)
{

	RECT rect;

  if(height < 1)
		height = 1;

  statusBarData.height = height;
	GetWindowRect(hwndStatus, &rect);

  SetWindowPos(
    hwndStatus,
    0,
    0,
    0,
    rect.right - rect.left,
    height,
    SWP_NOMOVE | SWP_NOZORDER
  );
	
}

/* 
  Purpose: Resize statusbar
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 06/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
void StatusBarResize(HWND hwndStatus, int parentWidth, int parentHeight)
{
	
	SetWindowPos(
    hwndStatus,
    0,
    0,
    parentHeight - statusBarData.height,
    parentWidth,
    statusBarData.height,
    SWP_NOZORDER
  );
	
}

/* 
  Purpose: Get statusbar height
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 06/09/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT
*/
int StatusBarGetHeight(HWND hwndStatus)
{
	return statusBarData.height;
}

/* 
  Purpose: Manage events on statusbar
  Created date: 26/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 18/10/2026
  Last modified username: Juan Manuel Mar Hdz. 
  Thanks to chatGPT, gemini and WinVi
*/
LRESULT CALLBACK StatusBarWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	HDC hdc;
	int i, j;
	HFONT hOldFont;
	PAINTSTRUCT ps;
	char path[SMALL_BUFFER];
	HBRUSH hBrush, hDark, hLight;
	RECT client, lineRect, textRect;
	POINT HiliteShadow[6], Offsets[6];
	HPEN hOldPen, hShadowPen, hHighlightPen;
	int gripHeight, lineSpacing, numLines;
	
	gripHeight = statusBarData.height;
	lineSpacing = 5;
	numLines = 3;
	
	/* grip map */
  Offsets[0].x = -2; Offsets[0].y = -1;
	Offsets[1].x = -1; Offsets[1].y = -2;
	Offsets[2].x = -1; Offsets[2].y = -3;
	Offsets[3].x = -4; Offsets[3].y =  0;
	Offsets[4].x = -4; Offsets[4].y = -1;
	Offsets[5].x =  0; Offsets[5].y = -5;

	switch (message)
  {
        
		case WM_PAINT: 
		{ 
		
			hdc = BeginPaint(hwnd, &ps); 
			
			GetClientRect(hwnd, &client); 
			
			if(getOSBits() == 32)
				hBrush = CreateSolidBrush(GetSysColor(COLOR_BTNFACE)); // prepare brush to background 
			else
				hBrush = CreateSolidBrush(GetSysColor(COLOR_MENU));  // prepare brush to background 
			
			FillRect(hdc, &client, hBrush); // paint background 
			DeleteObject(hBrush); 
			
			// 3D efect to statusbar
			
			// superior bar (dark and white)
			hDark = CreateSolidBrush(GetSysColor(COLOR_BTNSHADOW));
			lineRect = client;
			lineRect.top = 0;
			lineRect.bottom = 1;
			FillRect(hdc, &lineRect, hDark);
			DeleteObject(hDark);

			hLight = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
			lineRect.top = 1;
			lineRect.bottom = 2;
			FillRect(hdc, &lineRect, hLight);
			DeleteObject(hLight);
			
			//grip (diagonal bars) on the right corner - thanks to WinVi
			
			if(statusBarData.height > STATUSBAR_SMALL_HEIGHT1 || statusBarData.height > STATUSBAR_SMALL_HEIGHT2)
			{
				
				// large mode: We draw 4 or 5 lines to cover half the height in a stylized way
				
				if(statusBarData.height > STATUSBAR_SMALL_HEIGHT2)
				{	
			
					numLines = 5;
				  lineSpacing = 4;
					
				}
				else
				{	
			
					numLines = 4;
				  lineSpacing = 3;
					
				}	
				
			}
			
			hShadowPen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW));
			hHighlightPen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNHIGHLIGHT));
			hOldPen = (HPEN)SelectObject(hdc, hShadowPen);
			
			// initial mapping of absolute offsets from the bottom-right corner
			for(i=0; i<6; ++i) 
			{
				
				HiliteShadow[i].x = Offsets[i].x + client.right;
				HiliteShadow[i].y = Offsets[i].y + client.bottom;
				
			}
			
			// Iterative drawing of the 3D diagonal bars
			for(i=0; i<numLines; ++i)
			{
				
				// Dark side (Shadow)
				SelectObject(hdc, hShadowPen);
				Polyline(hdc, HiliteShadow, 4);

				// Clear part (3D gloss)
				SelectObject(hdc, hHighlightPen);
				Polyline(hdc, HiliteShadow + 4, 2);
				
				// Progressive upward/leftward shift
				for(j=0; j<6; ++j) 
				{
					
					if((j & 3) == 0 || (j & 3) == 3)
            HiliteShadow[j].x -= lineSpacing;
					else
            HiliteShadow[j].y -= lineSpacing;
    
				}
				
			}
			
			// GDI clean objects
			SelectObject(hdc, hOldPen);
			DeleteObject(hShadowPen);
			DeleteObject(hHighlightPen);

			// draw text in statusbar, set transparent background and text using button control text color 
			
			hOldFont = (HFONT)SelectObject(hdc, statusBarData.hFont); 
			
			// patch, center vertical text
			textRect = client;
			
			strncpy(path, "c:\\windows\\command", sizeof(path) - 1); 
			
			if(folder_exists(path) == TRUE)
			{
				
				strncpy(path, "c:\\windows\\system32", sizeof(path) - 1); 
				
				if(folder_exists(path) == FALSE) // Windows 95 / 98
				  textRect.top += 4;  // padding top
				else
					textRect.top += 2;  // padding top
				
			}
			else
				textRect.top += 2;  // padding top
			
			textRect.left += 5; // padding left
			textRect.right -= 18; // padding right

			SetBkMode(hdc, TRANSPARENT); 
			SetTextColor(hdc, GetSysColor(COLOR_BTNTEXT)); 
			DrawText(
				hdc, 
				statusBarData.simpleText, 
				-1, 
				&textRect, 
				DT_SINGLELINE | DT_VCENTER | DT_LEFT 
			);
			SelectObject(hdc, hOldFont);
			EndPaint(hwnd, &ps); 
			
			return 0; 
			
		}
		
		case WM_SYSCOLORCHANGE:

      InvalidateRect(hwnd, NULL, TRUE);
      UpdateWindow(hwnd);

    break;

		case WM_ERASEBKGND:
      return 1;

  }

  return DefWindowProc(
		hwnd,
    message,
    wParam,
    lParam
  );
	
}
