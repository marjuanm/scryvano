/*
  Scryvano - Lightweight text editor
  Original file name: folder.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
	
*/

/* 
  Purpose: Return flag folder exists
  Created date: 08/10/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 08/10/2026
  Last modified username: Juan Manuel Mar Hdz.
*/
int folder_exists(char *fullpath) 
{
    
	struct stat stats;

  if(stat(fullpath, &stats) == 0) 
  {
	
		if(S_ISDIR(stats.st_mode))
			return TRUE;
    else
		  return FALSE;
			
	}
	else
	  return FALSE;
		
}
