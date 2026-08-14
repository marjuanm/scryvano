/*
  Scryvano - Lightweight text editor
  Original file name: file.h
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
	
	This file contains portions derived from and reimplemented based on
  ShellDOS project https://github.com/marjuanm/shdos/blob/experimental/core/fs-operations/file.c
 
  The original source is licensed under the General Public License version 3 (GPL-3). 
	Portions derived from the original work have been modified and incorporated into Scryvano project.
 
  Copyright notices and attribution for the original work are retained where applicable.
  Thanks to the ShellDOS project and its contributors for their work and reference implementation.
  https://github.com/marjuanm/shdos
*/

/* 
  Purpose: Return folder from path
  Created date: 21/06/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 22/06/2026
  Last modified username: Juan Manuel Mar Hdz.
*/
void getExePath(char *fullpath, char *path)
{
	
	char *p;

  memset(path, 0, LARGE_BUFFER);
	strncpy(path, fullpath, LARGE_BUFFER - 1);
	path[LARGE_BUFFER - 1] = '\0';

  p = strrchr(path, '\\');

  if(p != NULL)
    *(p + 1) = '\0';
  else
    path[0] = '\0';

}

/* 
  Purpose: Return flag file exists
  Created date: 13/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 13/08/2026
  Last modified username: Juan Manuel Mar Hdz.
*/
int file_exists(char *fullpath) 
{

	if(access(fullpath, F_OK) == 0)
    return TRUE;
	else
	  return FALSE;

}
