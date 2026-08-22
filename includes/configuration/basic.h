/*
  Scryvano - Lightweight text editor
  Original file name: configuration.h
	New file name: basic.h
  Copyright (C) 2026 Juan Manuel Mar Hdz / Scryvano & contributors.
  Licensed under GPL-3.0, see the license file on the root project structure for more information.

	This file contains portions derived from and reimplemented based on
  ShellDOS project https://github.com/marjuanm/shdos/blob/main/includes/configuration.h
 
  The original source is licensed under the General Public License version 3 (GPL-3). 
	Portions derived from the original work have been modified and incorporated into Scryvano project.
 
  Copyright notices and attribution for the original work are retained where applicable.
  Thanks to the ShellDOS project and its contributors for their work and reference implementation.
  https://github.com/marjuanm/shdos
*/

#ifndef BASIC_H
#define BASIC_H

struct CONFIGURATION conf;
char line[SMALL_BUFFER], tmp[2];
char value[SMALL_BUFFER], stmp[SMALL_BUFFER];

void loadConfiguration();
void getValueFromKey(char *, char *);
void findLanguageFile(char *, char *);
void getCorrectValueToLoad(char *, char *);
struct CONFIGURATION getDefaultConfiguration();

#endif
