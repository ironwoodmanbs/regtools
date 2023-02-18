/* avapars.c */
#include <stdio.h>
#include <stdint.h>
#include "rgset.h"
#include "list.h"
#include "ava.h"
#include "common.h"


void prnAvaTitle(ava* ap) { // Вывод заголовка аварии
	printf("\n----------------ДОПОЛНИТЕЛЬНЫЙ ЗАГОЛОВОК------------------\n");
	printf("ПАРАМЕТР                 ЗНАЧЕНИЕ                         \n");
	printf("----------------------------------------------------------\n");
	printf("Ключевое слово           %s\n", ap->title->name);
	printf("Длительность такта       %u\n", ap->title->TactDuration);
	printf("Кол-во предавар. тактов  %u\n", ap->title->TactBefore);
	printf("Кол-во тактов            %u\n", ap->title->TactCount);
	printf("Причина аварии           %u\n", ap->title->Couse);
	printf("Событие                  %u\n", ap->title->Event);
	printf("Номер канала             %u\n", ap->title->NumChanel);
	printf("Значение уставки         %u\n", ap->title->Settings);
	printf("Первич. коэфф.           %f\n", ap->title->PrimFactor);
	printf("Типа расчета уставки     %u\n", ap->title->CalcSettingsType);
	printf("Номер группы реле        %u\n", ap->title->NumGrpRellay);
	printf("Состояние группы         ");
	printBits(2, &ap->title->GroupStatus);
	printf("\nЭталон    группы         ");
	printBits(2, &ap->title->GroupStandard);
	printf("\nТип АЦП                  %u\n", ap->title->AdcType);
	printf("Rellay canal             %u\n", ap->title->RellayCanal);
	printf("Смещ. осн. заголовка     %u\n", ap->title->OffsetMainTitle);
	printf("Смещ. доп. заголовка     %u\n", ap->title->OffsetAddTitle);
	printf("Флаги                    ");
	printBits(4, &ap->title->Flags);
	printf("\nСлужебное время аварии   %u\n", ap->title->ServiceTimeEvent);
	printf("Служебное время выключ.  %u\n", ap->title->ServiceTimeSwich);
	printf("Служебное время ff_min   %u\n", ap->title->ServiceTimeFF_min);
	printf("Служебное время ntact    %u\n", ap->title->ServiceTimeNtact);
	printf("Информация пользователя  %s\n", cp1251_to_utf(ap->title->UserInfo)); // запись в кодировке CP1251
};

void prnAvaMainTitle(ava* ap) {
	printf("\n-------------------ОСНОВНОЙ ЗАГОЛОВОК---------------------\n");
	printf("ПАРАМЕТР                  ЗНАЧЕНИЕ                         \n");
	printf("----------------------------------------------------------\n");
	printf("Дата время                %s.%d\n", str_local_time((DayTime*)&(ap->main_title->DayFault)), ap->main_title->MilsecFault);
	printf("Версия записи             %u\n", ap->main_title->RecordVersion);
	printf("Количество состояний      %u\n", ap->main_title->CountStatus);
	printf("Тип записи                %u\n", ap->main_title->RecordType);
	printf("Номер регистратора        %u\n", ap->main_title->RegNum);
	printf("Количество дискретов      %u\n", ap->main_title->CountBin);
	printf("Количество аналогов       %u\n", ap->main_title->CountChanel);
	printf("Количество тактов         %u\n", ap->main_title->CountTacts);
	printf("Смещение дискретов        %u\n", ap->main_title->OffsetBin);
	printf("Смещение аналогов         %u\n", ap->main_title->OffsetChanel);
};

void prnAvaBin(ava* ap) {
	if(ap->main_title->CountBin != 0) {
		printf("\n----------СРАБАТЫВАНИЕ ДИСКРЕТНЫХ СИГНАЛОВ----------\n"); 
		printf("Такт   М-Гр   Изменения                             \n");
		printf("----------------------------------------------------\n");
		CpxGrp cg;
		for (int i = 0; i < ap->main_title->CountBin; i++) {
			cg = GrpToCpx((ap->bin+i)->GroupNumb);
			printf("%-4.3d   %-1.1d-%-2.2d   ", (ap->bin+i)->Tact, cg.Matrix, cg.Group );
			printBits(2, &(ap->bin+i)->Status);
			printf("\n");
		};
		printf("\n--------------------------------------\n"); 
		printf("Такт   Группа  Разряд  Состояние       \n");
		printf("--------------------------------------\n");
		list* ls = ap->list_bin_i;
		TO_FIRST(ls);
		while(ls) {
			ava_bin_i* d = (ava_bin_i*)ls->data;
			printf("%-4.3d   %-2.2d      %-2.2d      %-1.1d\n", d->Tact, d->Group, d->Razr, d->Status);
			ls = ls->next;
		};
	};
};


int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Используй avapars avaXXXX.dat");
		return -1;
	}
	else {
		ava p;
		if (file_to_ram(&p, argv[1]) == 0) {
			if (ava_init(&p) != 0) {
				printf("\nОшибка открытия %s\n",argv[1]);
				return -1;
				}
			else {
				printf("Size of ava_title: %ld\n", sizeof(ava_title));
				printf("Size of ava_setting: %ld\n", sizeof(ava_setting));
				printf("Settings_count: %d\n", p.title->Settings_count);
				prnAvaTitle(&p);
				prnAvaMainTitle(&p);
				prnMatrixBin(p.start_bin);
				if(ava_bin_init(&p) == 0) {
					prnAvaBin(&p);
					ava_bin_close(&p);
				};
				ava_close(&p);
				return 0;
			};
		}
		else return -1;
	};
};
