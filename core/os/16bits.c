/*
  Scryvano - Lightweight text editor
  Original file name: 16bits.c
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
	Licensed under GPL-3.0, see the license file on the root project structure for more information.
	
	This file contains portions derived from and reimplemented based on
  ShellDOS project https://github.com/marjuanm/shdos/blob/main/core/os/16bits.c
 
  The original source is licensed under the General Public License version 3 (GPL-3). 
	Portions derived from the original work have been modified and incorporated into Scryvano project.
 
  Copyright notices and attribution for the original work are retained where applicable.
  Thanks to the ShellDOS project and contributors for their work and reference implementation.
  https://github.com/marjuanm/shdos
	
*/ 

/* Purpose: Return OS bit number
	 Created date: 25/06/2026
   Created by username: Juan Manuel Mar Hdz.
   Last modified date: 25/06/2026
   Last modified username: Juan Manuel Mar Hdz.
*/
int getOSBits()
{
	return 16;
}

/* Purpose: Return OS flavor
	 Created date: 15/07/2026
   Created by username: Juan Manuel Mar Hdz.
   Last modified date: 17/08/2026
   Last modified username: Juan Manuel Mar Hdz.
	 Thanks to chatgpt
*/
void getOSFlavor(char *flavor)
{
	
	flavor[0] = '\0';

	if(separator == '\\')
		strncpy(flavor, "WINDOWS", MEDIUM_BUFFER - 1);
	else
		strncpy(flavor, "LINUX", MEDIUM_BUFFER - 1);
	
	flavor[MEDIUM_BUFFER - 1] = '\0';
	
}

/* Purpose: Return OS major version
	 Created date: 15/07/2026
   Created by username: Juan Manuel Mar Hdz.
   Last modified date: 17/07/2026
   Last modified username: Juan Manuel Mar Hdz.
	 Thanks to chatgpt
*/
int getOSMajorVersion()
{
	
	DWORD dwVersion;
	
	if(osflavor[0] == '\0')
		getOSFlavor(osflavor);
	
	if(stricmp(osflavor, "WINDOWS") != 0 && stricmp(osflavor, "LINUX") != 0)
		return 0;
	else
	{
		
		dwVersion = GetVersion();
		
		if(LOBYTE(LOWORD(dwVersion)) < 6)
		  return LOBYTE(LOWORD(dwVersion)); //work on Windows xp or minus
		else
			return 0;
		
	}
	
	return 0;
	
}

/* Purpose: Return OS minor version
	 Created date: 15/07/2026
   Created by username: Juan Manuel Mar Hdz.
   Last modified date: 01/10/2026
   Last modified username: Juan Manuel Mar Hdz.
	 Thanks to chatgpt
*/
int getOSMinorVersion()
{
	
	DWORD dwVersion;
	
	if(osflavor[0] == '\0')
		getOSFlavor(osflavor);
	
	if(stricmp(osflavor, "WINDOWS") != 0 && stricmp(osflavor, "LINUX") != 0)
		return 0;
	else
	{
		
		dwVersion = GetVersion();
		return HIBYTE(LOWORD(dwVersion));

  }
	
	return 0;
	
}
