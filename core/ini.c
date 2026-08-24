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
  Last modified date: 23/08/2026
  Last modified username: Juan Manuel Mar Hdz.
	Thanks to chatgpt
*/
int readINIkey(char *section, char *key, char *value, int size, char *file)
{
	
	DWORD result;

  result = GetPrivateProfileString(
    section,
    key,
    "\x01",
    value,
    size,
    file
  );

  if(result == 1 && value[0] == '\x01')
  {
		
    value[0] = '\0';
    return FALSE;
    
	}
	else
		return TRUE;

}

/*int readINIkey(char *section, char *key, char *value, int size, char *file)
{
  GetPrivateProfileString(section, key, "", value, size, file);
}
*/


