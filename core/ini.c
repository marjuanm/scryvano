/*
  Scryvano - Lightweight text editor
  Original file name: ini.c
	New file name: basic.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/

/* 
  Purpose: Return value from ini section/key file
  Created date: 21/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 21/08/2026
  Last modified username: Juan Manuel Mar Hdz.
*/
void readINIkey(char *section, char *key, char *value, int size, char *file)
{
  GetPrivateProfileString(section, key, "", value, size, file);
}

