/*
  Scryvano - Lightweight text editor
  Original file name: 32bits.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/

/* 
  Purpose: Return translation flag
  Created date: 18/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 18/08/2026
  Last modified username: Juan Manuel Mar Hdz.
	Thanks to chatGPT
*/
void getLanguage(char *language)
{
	
	WORD lang, primary, sub;
	
	lang = GetUserDefaultLangID();
	primary = PRIMARYLANGID(lang);
	sub = SUBLANGID(lang);

	if(primary == LANG_ENGLISH)
	{
    
		if(sub == SUBLANG_ENGLISH_UK)
			strcpy(language, "en_GB");
		else if (sub == SUBLANG_ENGLISH_US)
      strcpy(language, "en_US");
	  else
      strcpy(language, "en");

	}
	else if (primary == LANG_SPANISH)
	{
    
		if(sub == SUBLANG_SPANISH_MEXICAN)
      strcpy(language, "es_MX");
		else if (sub == SUBLANG_SPANISH_MODERN)
      strcpy(language, "es_ES");
	  else
      strcpy(language, "es");
		
	}
	else if (primary == LANG_FRENCH)
		strcpy(language, "fr");
	else if (primary == LANG_GERMAN)
		strcpy(language, "de");
	else
		strcpy(language, "en");
		
}
