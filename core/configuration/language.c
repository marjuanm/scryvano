/*
  Scryvano - Lightweight text editor
  Original file name: language.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/

/* 
  Purpose: Return translation file
  Created date: 15/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 15/08/2026
  Last modified username: Juan Manuel Mar Hdz.
	Thanks to chatGPT
*/
void findLanguageFile(char *language, char *file)
{
	
	char *p;
  char path[LARGE_BUFFER];

  // not found by default
	file[0] = '\0';

  // find in current path
	
	strcpy(path, currentpath);
  strcat(path, "lang\\");
  strcat(path, language);
  strcat(path, ".ini");

  if (file_exists(path) == TRUE)
  {

    strcpy(file, path);
    return;
    
	}
	
	// find in parent folder
	
	strcpy(path, currentpath);

  // remove trailing backslash

  p = strrchr(path, '\\');
	if(p != NULL) *p = '\0';

	// remove current directory
	
	p = strrchr(path, '\\');
	if(p != NULL) *(p + 1) = '\0';
	
	strcat(path, "lang\\");
  strcat(path, language);
  strcat(path, ".ini");

  if (file_exists(path) == TRUE)
  {
		
		strcpy(file, path);
    return;
    
	}
	
}
