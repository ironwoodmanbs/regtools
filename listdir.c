/* listdir */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdint.h>
#include "rgset.h"
#include "list.h"
#include "ava.h"
#include "common.h"

//void (*processor)(rgset* rp, ava* ap, const char* file_name); 

void mk_full_path(const char* path, struct dirent* entry, char* fullpath) {
	const char line[] = "/";
	strcpy(fullpath, path);
	strcat(fullpath, line);
	strcat(fullpath, entry->d_name);
};

int listdir(const char* path, void (*processor)(rgset* rp, ava* ap, const char* file_name)) {
	struct dirent* entry = NULL;
	DIR* dp;
	char newpath[255];
	const char rgset_patern1[] = "rgset.dat";
	const char rgset_patern2[] = "Rgset.dat";
	const char rgset_patern3[] = "RGSET.DAT";
	const char ava_patern[] = "ava";
	const char dat_patern[] = ".dat";
	const char onedot[] = ".";
	const char twodot[] = "..";
	int rg = 0; // Флаг наличия в данном каталоге файла rgset.dat

	//// Открываем каталог ////
	dp = opendir(path);
	if (dp == NULL) {
		perror("opendir");
		return -1;
	};
	///////////////////////////

	//////////////////////////////////////////////
	/////// Блок поиска файлов rgset.dat /////////
	//////////////////////////////////////////////
	entry = readdir(dp);
	rgset* rp = NULL;
	while(entry) {
		if((entry->d_type & 8) && (!strcmp(entry->d_name, rgset_patern1) || !strcmp(entry->d_name, rgset_patern2) || !strcmp(entry->d_name, rgset_patern3))) 
		{ 
			mk_full_path(path, entry, newpath);
			rp = rgsetInit(newpath);
			if(rp != NULL) rg = 1;
			else rg = 0;
		};
		entry = readdir(dp);
	};
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	///// Блок поиска файлов аварии ava.dat //////
	//////////////////////////////////////////////
	rewinddir(dp);
	if(rg == 1) {
		entry = readdir(dp);
		while(entry) {
			if(entry->d_type & 8 && strstr(entry->d_name, ava_patern) && strstr(entry->d_name, dat_patern)) { // Для всех файлов содержащих в имение "ava" и ".dat"
				ava ap;
				// Определение полного пути
				mk_full_path(path, entry, newpath);
				if(file_to_ram(&ap, newpath) == 0) {
					if(ava_init(&ap) == 0) {
						//printf("\nФайл аварии: %s\n",newpath);
						processor(rp, &ap, newpath);
						ava_close(&ap);
					};
			
				};
			};
		entry = readdir(dp);
		};
	};
	if(rg == 1) rgsetClose(rp); // Закраваем rgset.dat
	////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////
	///////// Блок поиска вложенных каталогов  /////////
	////////////////////////////////////////////////////
	rewinddir(dp);
	entry = readdir(dp);
	while(entry) { // Разбор вложенных каталогов (рекурсия функции listdir)
		if(entry->d_type & 4 && !strstr(entry->d_name, onedot) && !strstr(entry->d_name, twodot)) {
			mk_full_path(path, entry, newpath);
			listdir(newpath, processor);// Рекурсивный вход в функцию listdir
		};
		entry = readdir(dp);
	};
	/////////////////////////////////////////////////////
	
	closedir(dp); // Закрываем каталог
	return 0;
};


