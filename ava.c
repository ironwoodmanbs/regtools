/* ava.c */

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iconv.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "list.h"
#include "rgset.h"
#include "ava.h"
#include "common.h"

/* Инициализация ava */
int avaInit(ava* p) {
	const char regina[] = "REGINA#####"; 
		if(strcmp(regina,(p->title)->name) != 0) { // Проверка на соответствие файла формату файлов аварии Регины
			printf("Не верный формат ava файла");
			return -1;
		}
		else {
			p->main_title = (ava_main_title*)((uintptr_t)p->title + p->title->OffsetMainTitle);
			p->add_title = (ava_add_title*)((uintptr_t)p->title + p->title->OffsetAddTitle);
			p->chanel = (int16_t*)((uintptr_t)p->title + p->main_title->OffsetChanel);
			p->bin = (ava_bin*)((uintptr_t)p->title + p->main_title->OffsetBin);
			p->start_bin = (uint16_t*)((uintptr_t)p->bin - 96);
			p->list_bin_i = NULL;
			return 0;
		};
};

/* Функция закрытие ava */
int avaClose(ava* p) {
	if(p->title != NULL) file_close(p);
	return 0;
};


// Функция определения номера канала в rgset.dat по номеру в avaxxxx.dat
int avaFindChNumb(rgset* rp, ava* ap, int i) {
	int j = 0;
	while(!(((rp->chanel+j)->RegNumber == (ap->main_title)->RegNum) && ((rp->chanel+j)->ChNumber == i+1)) && (j < rp->title->CountChanel)) {
		j++;
	};
	return j;
};	

CpxGrp avaGrpToCpx(int mg) {
	CpxGrp cg;
	cg.Matrix = (mg - 1) % 3 + 1;
	cg.Group = (int)(mg-1)/3 + 1;
	return cg;
};

int avaCpxToGrp(CpxGrp cp) {
	return (cp.Group - 1)*3 + cp.Matrix;
};

int avaBinInit(ava* p) {
	if(p->main_title->CountBin != 0) {
		// Создем инверсную копию масива start_bin
		uint16_t curr_bin[96];
		for(int i = 0; i < 96; i++) curr_bin[i] = ~(p->start_bin[i]);
		/* Перебор объектов bin и формирование на их основе списка разжатых (распакованых) объектов ava_bin_i */
		list* ls = NULL;
		for(int i = 0; i < p->main_title->CountBin; i++) {
			uint16_t word = 1;
			for(int j = 0; j < 16; j++) {
				if(((word << j) & (p->bin+i)->Status) > 0) {
					ls = list_add(ls);
					ls->data = Malloc(sizeof(ava_bin_i));
					ava_bin_i* ava_bin = (ava_bin_i*) ls->data;
					ava_bin->Tact = (p->bin+i)->Tact;
					ava_bin->Group = (p->bin+i)->GroupNumb;
					ava_bin->Razr = j+1;
					curr_bin[ava_bin->Group] = curr_bin[ava_bin->Group] ^ bite_image(ava_bin->Razr); 
					if(curr_bin[ava_bin->Group] & bite_image(ava_bin->Razr)) ava_bin->Status = 1;
					else ava_bin->Status = 0;
				};
			};
		};
	p->list_bin_i = ls;	
	return 0;
	}
	else return -1;
};

void avaBinClose(ava* p) {
	list* ls = p->list_bin_i;
	while(ls->next) ls = ls->next;
	while(ls) {
		free(ls->data);
		ls = list_del(ls);
	};
};

