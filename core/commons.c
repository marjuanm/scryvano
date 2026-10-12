
/* 
  Purpose: Ajust size on the text editor area
  Created date: 07/10/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 07/10/2026
  Last modified username: Juan Manuel Mar Hdz.
	Thanks to chatgpt and gemini
*/
void resizeEditor(HWND hwnd)
{
    
	RECT clientRect, statusRect;
  int width, height, statusHeight = 0;

  GetClientRect(hwnd, &clientRect);

  width = clientRect.right;
  height = clientRect.bottom;

  // if statusbar is visible get height
	if(H_STATUSBAR != 0 && IsWindowVisible(H_STATUSBAR))
  {
		
		GetClientRect(H_STATUSBAR, &statusRect);
    statusHeight = statusRect.bottom;
    
	}
	
	// prevent negative height
	if(statusHeight > height)
    statusHeight = 0;

  MoveWindow(H_SINGLE_EDITOR, 0, 0, width, height - statusHeight, TRUE);
	
}
