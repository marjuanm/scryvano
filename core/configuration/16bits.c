/*
  Scryvano - Lightweight text editor
  Original file name: 16bits.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.
*/

/* 
  Purpose: Return translation flag
  Created date: 19/08/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 19/08/2026
  Last modified username: Juan Manuel Mar Hdz.
	Thanks to chatGPT
*/
void getLanguage(char *language)
{
	
	char lang[SMALL_BUFFER];

  GetProfileString("intl", "sLanguage", "", lang, sizeof(lang));

	if(stricmp(lang, "enu") == 0)
		strcpy(language, "en_US");
	else if (stricmp(lang, "eng") == 0)
    strcpy(language, "en_GB");
  else if (stricmp(lang, "esm") == 0)
    strcpy(language, "es_MX");
  else if (stricmp(lang, "esp") == 0)
		strcpy(language, "es_ES");
	else if (stricmp(lang, "fra") == 0)
		strcpy(language, "fr");
	else if (stricmp(lang, "deu") == 0)
		strcpy(language, "de");
	else
		strcpy(language, "en");
	
}
