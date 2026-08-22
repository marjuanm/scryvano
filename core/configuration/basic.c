/*
  Scryvano - Lightweight text editor
  Original file name: configuration.c
	New file name: basic.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.

	This file contains portions derived from and reimplemented based on
  ShellDOS project https://github.com/marjuanm/shdos/blob/main/core/configuration.c
 
  The original source is licensed under the General Public License version 3 (GPL-3). 
	Portions derived from the original work have been modified and incorporated into Scryvano project.
 
  Copyright notices and attribution for the original work are retained where applicable.
  Thanks to the ShellDOS project and its contributors for their work and reference implementation.
  https://github.com/marjuanm/shdos
*/

/* 
  Purpose: Return value from string in key=value format
  Created date: 21/06/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 15/08/2026
  Last modified username: Juan Manuel Mar Hdz.
*/
void getValueFromKey(char *stream, char *val)
{
	
	char *p;

  // ignore full comments
	if(stream[0] == ';' || stream[0] == '#')
  {
		
		val[0] = '\0';
    return;
    
	}
	
	// ignore comments section on the line, the line is truncate at found ; or #
	p = strpbrk(stream, ";#");
  if(p != NULL) *p = '\0';
	
	// extract value at found '=' on the line
	
	p = strchr(stream, '=');
  
	// no value found to line
	if(p == NULL)
  {
		
		val[0] = '\0';
    return;
    
	}
	
	// copy the value section
	p++;
	while(*p == ' ' || *p == '\t') p++;

	val[0] = '\0';
  strncpy(val, p, SMALL_BUFFER - 1);
  val[SMALL_BUFFER - 1] = '\0';

}

/* 
  Purpose: Return value from string in correct format (convert yes and on to 1, no, off to 0)
  Created date: 21/06/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 05/07/2026
  Last modified username: Juan Manuel Mar Hdz.
*/
void getCorrectValueToLoad(char *stream, char *val)
{

	if(strcasecmp(stream, "1") == 0 ||
    strcasecmp(stream, "yes") == 0 ||
    strcasecmp(stream, "on") == 0)
		{
			
			strcpy(val, "1");
			val[SMALL_BUFFER - 1] = '\0';
			
		}
	else if (strcasecmp(stream, "0") == 0 ||
    strcasecmp(stream, "no") == 0 ||
    strcasecmp(stream, "off") == 0)
		{
			
			strcpy(val, "0");
			val[SMALL_BUFFER - 1] = '\0';
			
		}
	else
	{
    
		strncpy(val, stream, SMALL_BUFFER - 1);
    val[SMALL_BUFFER - 1] = '\0';

	}
	
}

/* 
  Purpose: Return default Scryvano configuration
  Created date: 08/06/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 15/08/2026
  Last modified username: Juan Manuel Mar Hdz.
*/
struct CONFIGURATION getDefaultConfiguration()
{
	
	struct CONFIGURATION conf;
    
  conf.language[0] = '\0';
  strncpy(conf.language, "en", sizeof(conf.language) - 1);
	conf.language[sizeof(conf.language) - 1] = '\0';
  
	return conf;

}

/* 
  Purpose: Load Scryvano configuration from file
  Created date: 07/07/2026
  Created by username: Juan Manuel Mar Hdz.
  Last modified date: 15/08/2026
  Last modified username: Juan Manuel Mar Hdz.
*/
void loadConfiguration()
{

	int exists, itmp;
	char file[LARGE_BUFFER];
	FILE *fp = fopen(confpath, "r");
	
	if(fp != NULL)
  {
		
		// load configuration from scryvano.cfg, every line start with key=value
		while(fgets(line, SMALL_BUFFER, fp) != NULL)
	  {
			
			line[strcspn(line, "\r\n")] = '\0';
		  
			if(strncasecmp(line, "language=", strlen("language=")) == 0) 
			{
				
				getValueFromKey(line, value);
				
				if(value != NULL) 
				{
					
					getCorrectValueToLoad(value, stmp);
					
					conf.language[0] = '\0';
					strncpy(conf.language, stmp, sizeof(conf.language) - 1);
					conf.language[sizeof(conf.language) - 1] = '\0';
					
				}
				
			}
				
		}

		fclose(fp);
    exists = TRUE;

	}
	else
	  exists = FALSE;

	// create configuration file
	if(exists == FALSE)
	{
		
		fp = fopen(confpath, "w");
		getLanguage(conf.language);

		// check if language file exits, then load in the configuration, else load english
		
		if(stricmp(conf.language, "en") != 0) // check if only the language not is english, english is by default
		{
			
			findLanguageFile(conf.language, file);
			
			if(file[0] == '\0')
			{
				
				strcpy(conf.language, "en");
				translatefile[0] = '\0';
				
			}
			else
			{
				
				translatefile[0] = '\0';
				strncpy(translatefile, file, sizeof(translatefile) - 1);
			
			}
			
		}
		else
			translatefile[0] = '\0';
		
		// Load regional language (if it exists)

		// if not fail then write on the created file (fail to write on cdrom by example)	
		if(fp != NULL)
		{
			
			fprintf(fp, "language=%s\n", conf.language);

		  fclose(fp);
			
		}
		
	}
	else
	{
		
		// check if language file exits, then load in the configuration, else load english
		
		if(stricmp(conf.language, "en") != 0) // check if only the language not is english, english is by default
		{
			
			findLanguageFile(conf.language, file);
			
			if(file[0] == '\0')
			{
				
				strcpy(conf.language, "en");
				translatefile[0] = '\0';
				
			}
			else
			{
				
				translatefile[0] = '\0';
				strncpy(translatefile, file, sizeof(translatefile) - 1);
			
			}
			
		}
		else
			translatefile[0] = '\0';
		
	}

}
