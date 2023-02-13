/* avaprint.c */
#include <dirent.h>
#include <error.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "list.h"
#include "rgset.h"
#include "ava.h"
#include "calculation.h"
#include "common.h"
#include "listdir.h"


void avaprint(rgset* rp, ava* ap, const char* filename) {
	extremum ext;
	int j;
	float k;
	int period = findperiod(rp);// Определяем период сигнала (20 или 40 отсчетов)
	printf("\nФайл: %s\n", filename);
	printf("Объект: %s\n", utf(rp->title->NameStation));
	printf("Регистратор: %s\n", utf((rp->reg + ap->main_title->RegNum - 1)->Name));
	printf("Дата события: %s\n", str_local_time((DayTime*)&(ap->main_title->DayFault)));
	printf("-------------------------------------Аналоговые каналы-----------------------------\n");
	printf("N  Name                                 Before   Max      Min      Max1h    Min1h\n");
	printf("-----------------------------------------------------------------------------------\n");
	for(int i = 0; i < ap->main_title->CountChanel; i++) { // Для каждого канала в файле аварии
		find_extremum(ap->chanel+i*ap->main_title->CountTacts, ap->main_title->CountTacts, period, &ext);
		j = findChNumb(rp, ap, i);// Определяе номер нашего канала в файле rgset.dat
		if(j < rp->title->CountChanel) {
			k = fabsf(mainratio(rp, j));// Определяем обобщенный коэфициент
			// Вывод результатов
			printf("%-3d", i+1);
			prnFix((rp->chanel+j)->Name, 28, 30);
			printf("%s\t",utf((rp->chanel+j)->SymbolPrimCircuit));
			printf("%-9.3f", ext.before*k);
			printf("%-9.3f", ext.max*k);
			printf("%-9.3f", ext.min*k);
			printf("%-9.3f", ext.z_max*k/0.7071);
			printf("%-9.3f\n", ext.z_min*k/0.7071);
		};
	};

	if (ava_bin_init(ap) == 0) { // Инициализация двоичных данных
//		list* ls = ap->list_bin_i;
		int i,t;
		if(findperiod(rp) == 40) t = 2; else t = 1;
		printf("\n----------------------ДИСКРЕТНЫЕ СИГНАЛЫ-----------------------\n");
		printf("мс     Гр-Рз    Наименование                             Статус\n");
		printf("---------------------------------------------------------------\n");
		TO_FIRST(ap->list_bin_i);
		for(list *ls = ap->list_bin_i; ls; ls = ls->next) {
//		while(ls) {
			ava_bin_i* d = (ava_bin_i*)ls->data;
			binNum tmp;
			i = 0;
			binNumb((rp->bin + i)->Numb, &tmp);
			while((d->Group != tmp.MG || ap->main_title->RegNum != (rp->bin + i)->Reg || d->Razr != tmp.Razr) && (i < rp->title->CountBinSignal))
			{
				i++;
				binNumb((rp->bin + i)->Numb, &tmp);
			};
			printf("%-4.3d   %-2.2d-%-2.2d    ", (int)(d->Tact/t), d->Group, d->Razr);
			prnFix((rp->bin + i)->Name, 45, 46);
			printf("%-1.1d\n", d->Status);
//			ls = ls->next;
		}
		ava_bin_close(ap);
	};
};
int main (int argc, char** argv) {
	if (argc != 2) printf ("Неправильное число аргументов\n");
	else { 
		processor = avaprint;
		//processor = avasql;
		listdir(argv[1], processor);
	};
return 0;
};
