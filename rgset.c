/* rgset.c */
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "array.h"
#include "rgset.h"
#include "common.h"

/* Функция для инициализации массива структур типа rgset_bin
source - указатель на участок памяти (образ файла rgset.dat) 
откуда начинаются данные о дискретных сигналах (поле OffsetBinSignal
проинициализированной структуры rgset_title).
destin - указатель на участок памяти куда производится копирование
информации (д.б. типа grset_bin*).
count -  количество считываний */
void init_bin_arr(uint16_t* source, rgset_bin* dest, int count) {
	rgset_bin* bin = dest;
	uint16_t* pt = source;
	for (int j = 0; j < count; j++) {
		// Заполнение нулями текстовые поля структуры rgset_bin
		for (int i = 0; i < 48; i++) bin->Name[i]=0;
		for (int i = 0; i < 24; i++) bin->Panel[i]=0;
		for (int i = 0; i < 24; i++) bin->Relay[i]=0;
		
		// Копирование имени дискретного сигнала
		for (int i = 0; i < *pt && i < 47; i++) bin->Name[i] = *(char*)((uintptr_t)pt+2+i);
		
		// Копирование название панели
		pt=(uint16_t*)((uintptr_t)pt+*pt+2);
		for (int i = 0; i < *pt && i < 23; i++) bin->Panel[i] = *(char*)((uintptr_t)pt+2+i);
		
		// Копирование название реле
		pt=(uint16_t*)((uintptr_t)pt+*pt+2);
		for (int i = 0; i < *pt && i < 23; i++) bin->Relay[i] = *(char*)((uintptr_t)pt+2+i);
		
		// Копирование цифровых данных (Номер сигнала, номер регистратора, Тип сигнала, Флаг)
		pt=(uint16_t*)((uintptr_t)pt+*pt+2);
		bin->Numb = *pt; pt++;
		bin->Reg = *pt; pt++;
		bin->Type = *pt; pt++;
		bin->Flag = *pt; pt++;
		bin++;
	};
}

int prnRgsetTitle(rgset* p) {
	if(p != NULL && p->title != NULL) {
		printf("----------------------------------TITLE------------------------------\n");
		printf("NAME                                  VALUE\n");
		printf("---------------------------------------------------------------------\n");
		printf("Version rgset                         %s\n", p->title->Version);
		printf("Name Station                          %s\n", utf(p->title->NameStation));
		printf("NameArch                              %s\n", utf(p->title->NameArch));
		printf("SpesialLine(Passw)                    %s\n", utf(p->title->SpesialLine));
		printf("CountChanel                           %d\n",p->title->CountChanel);
		printf("CountReg                              %d\n",p->title->CountReg);
		printf("CountLine                             %d\n",p->title->CountLine);
		printf("CountBinSignal                        %d\n",p->title->CountBinSignal);
		printf("CountMarkBinSignal                    %d\n",p->title->CountMarkBinSignal);
		printf("MaxNumberSignal                       %d\n",p->title->MaxNumberSignal);
		printf("CountLineSection                      %d\n",p->title->CountLineSect);
		printf("CountSwich                            %d\n",p->title->CountSwich);
		printf("CountCircleSettings                   %d\n",p->title->CountCircleSettings);
		printf("CountTableSettings                    %d\n",p->title->CountTableSettings);
		printf("CountTransmisChanel                   %d\n",p->title->CountTransmisChanel);
		printf("CountAutotransf                       %d\n",p->title->CountAutotransf);
		printf("DeleyExpressInfo                      %d\n",p->title->DeleyExpressInfo);
		printf("OffsetChanel                          %d\n",p->title->OffsetChanel);
		printf("OffsetLine                            %d\n",p->title->OffsetLine);
		printf("OffsetReg                             %d\n",p->title->OffsetReg);
		printf("OffsetBin                             %d\n", p->title->OffsetBin);
		printf("OffsetMark                            %d\n",p->title->OffsetMark);
		printf("OffsetLineSect                        %d\n",p->title->OffsetLineSect);
		printf("OffsetSwich                           %d\n",p->title->OffsetSwich);
		printf("OffsetCircleSettings                  %d\n",p->title->OffsetCircleSettings);
		printf("OffsetTableSettings                   %d\n",p->title->OffsetTableSettings);
		printf("OffsetTransmisChanel                  %d\n",p->title->OffsetTransmisChanel);
		printf("OffsetAutotransformer                 %d\n",p->title->OffsetAutotransformer);
		printf("OffsetRecordLineReg                   %d\n",p->title->OffsetRelationsLineReg);
		printf("CountSpecifLineProtection             %d\n",p->title->CountSpecifLineProtection);
		printf("CountSpecifLineProtection2            %d\n",p->title->CountSpecifLineProtection2);
		printf("OffsetSpesifLineProtection            %d\n",p->title->OffsetSpesifLineProtection);
		printf("CountSpecifStageProtection            %d\n",p->title->CountSpecifStageProtection);
		printf("OffsetAdditSpecifProtections          %d\n",p->title->OffsetAdditSpecifChanel);
		printf("CountProtectionZoneSectionallyLinear  %d\n",p->title->CountProtectionZoneSectionallyLinear);
		printf("OffsetProtectionZoneSectionallyLinear %d\n",p->title->OffsetProtectionZoneSectionallyLinear);
	};
	return 0;
};

int prnRgsetChanel(rgset* p) {
	if(p != NULL && p->chanel != NULL && p->title->CountChanel != 0) {
		printf("\n\n------------------------------------------------------CHANNELS--------------------------------------------------------\n");
		printf("N   NAME                          ShN   PRI   SEC   LINE  REG   TYPE  PHASE\tK2\tK3\tK4\tK5\tMR\n");
		printf("----------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < p->title->CountChanel; i++) {
			printf("%-4d", (p->chanel+i)->ChNumber);
			prnFix((p->chanel+i)->Name, 29, 30);
			prnFix((p->chanel+i)->SymbolChanel, 5, 6);
			prnFix((p->chanel+i)->SymbolPrimCircuit, 5, 6);
			prnFix((p->chanel+i)->SymbolSecondCircuit, 5, 6);
			printf("%-6d", (p->chanel+i)->LineNumber);
			printf("%-6d", (p->chanel+i)->RegNumber);
			printf("%-6d", (p->chanel+i)->TypeChanel);
			printf("%-6d\t", (p->chanel+i)->Phase);
			printf("%-1.2f\t", (p->chanel+i)->K2);
			printf("%-1.2f\t", (p->chanel+i)->K3);
			printf("%-1.2f\t", (p->chanel+i)->K4);
			printf("%-1.1f\t", (p->chanel+i)->K5);
			printf("%-1.4f\n", mainratio(p, i));
		};
	};
	return 0;
};

int prnRgsetLines(rgset* p) {
	if (p != NULL && p->line != NULL && p->title->CountLine != 0) {
		printf("\n\n--------------------------LINES----------------------------------------\n");
		printf("N    NAME                           REG  TYPE   LENGHT   PowerCalcLogic\n");
		printf("-----------------------------------------------------------------------\n");
		for (int i = 0; i < p->title->CountLine; i++) {
			printf("%2d   ", i+1);
			prnFix((p->line+i)->Name, 29, 30);
			printf("%2d",(p->line+i)->RegNumber);
			printf("%7d", (p->line+i)->LineType);
			printf("%10.1f", (p->line+i)->LineLenght);
			printf("%4d\n",(p->line+i)->PowerCalcLogic);
		};
	};
	return 0;
};

int prnRgsetReg(rgset* p) {
	if(p != NULL && p->reg != NULL && p->title->CountReg != 0) {
		printf("\n\n----------------------------REGISTRATORS-------------------------------------------\n");
		printf("N  NAME        CountTact   TactDurat   KTactToMin  CountFrontT CountLine   AdcType\n");
		printf("-----------------------------------------------------------------------------------\n");
		for (int i = 0; i < p->title->CountReg; i++) {
			printf("%-3d",i+1);
			prnFix((p->reg+i)->Name, 11,12);
			printf("%-12d",(p->reg+i)->CountTacts);
			printf("%-12d",(p->reg+i)->TactDuration);
			printf("%-12d",(p->reg+i)->KTactToMinute);
			printf("%-12d",(p->reg+i)->CountFrontTacts);
			printf("%-12d",(p->reg+i)->CountLines);
			printf("%-12d\n",(p->reg+i)->AdcType);
		};
	};
	return 0;
};

int prnRgsetBin(rgset* p) {
	if (p != NULL && p->bin != NULL && p->title->CountBinSignal !=0){
		printf("\n\n---------------------------------------------BINARY--------------------------------------------\n");
		printf("N   NAME                                N     M-G-R     REG    TYPE   FLAG   PANEL       RELEY\n");
		printf("-----------------------------------------------------------------------------------------------\n");
		binNum tmp;
		for (int i = 0; i < p->title->CountBinSignal; i++) {
			printf("%-4d",i+1);
			prnFix((p->bin+i)->Name, 34, 36);
			printf("%-5u", (p->bin+i)->Numb);
			binNumb((p->bin+i)->Numb, &tmp);
			printf("%2u-%u-%u\t", tmp.Matrix, tmp.Group, tmp.Razr);
			printf("%-7u", (p->bin+i)->Reg);
			printf("%-7u", (p->bin+i)->Type);
			printf("%-7u", (p->bin+i)->Flag);
			prnFix((p->bin+i)->Panel, 11, 12);
			prnFix((p->bin+i)->Relay, 11, 12);
			printf("\n");
		};
	};
	return 0;
};

int binNumb(int numb, binNum* out) {
	out->Razr = (numb-1) % 16+1;
	int tmp = (int)(numb/16);
	out->Matrix = tmp % 3 + 1;
	out->Group = (int)tmp/3+1;
	out->MG = (out->Group-1)*3 + out->Matrix;
	return 0;
};

int prnRgsetMark(rgset* p) { 
	if(p != NULL && p->mark != 0 && p->title->CountMarkBinSignal != 0) {
		printf("\n\n------------------------MarkBinSignals-------------------------\n");
		printf("N  NAME                ON        OFF      P1   P2   COUNT\n");
		printf("---------------------------------------------------------------\n");
		for (int i = 0; i < p->title->CountMarkBinSignal; i++) {
			printf("%-3u",(p->mark+i)->Numb);
			prnFix((p->mark+i)->Name, 19, 20);
			prnFix((p->mark+i)->StatusOn, 9, 10);
			prnFix((p->mark+i)->StatusOff, 9, 10);
			printf("%-5u", (p->mark+i)->Position1);
			printf("%-5u", (p->mark+i)->Position2);
			printf("%-5u\n", (p->mark+i)->Count);
		};
	};
	return 0;
};

int prnRgsetLineSect(rgset* p) {
	if(p != NULL && p->linesect != NULL && p->title->CountLineSect != 0) {
		printf("\n\n--------------------------------------LINE SECTIONS----------------------------------------------------\n");
		printf("LineN SectN Lenght    R1     X1     R0     X0     R1C    X1C    Flags CtRelLine RelatLine RL1   XL1\n");
		printf("-------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < p->title->CountLineSect; i++) {
			printf("%-6u",(p->linesect+i)->LineNumb);
			printf("%-6u",(p->linesect+i)->LineSectNumb);
			printf("%-10.2f",(p->linesect+i)->LenghtSect);
			printf("%-7.2f",(p->linesect+i)->R1Sect);
			printf("%-7.2f",(p->linesect+i)->X1Sect);
			printf("%-7.2f",(p->linesect+i)->R0Sect);
			printf("%-7.2f",(p->linesect+i)->X0Sect);
			printf("%-7.2f",(p->linesect+i)->R1Coil);
			printf("%-7.2f",(p->linesect+i)->X1Coil);
			//printf("%-6.2f",(p->linesect+i)->R0Coil);
			//printf("%-6.2f",(p->linesect+i)->X0Coil);
			printf("%-6u",(p->linesect+i)->Flags);
			printf("%-10u",(p->linesect+i)->CountRelatedLine);
			printf("%-10u",(p->linesect+i)->NumbRelLine1);
			printf("%-6.2f",(p->linesect+i)->RelatedRL1);
			printf("%-6.2f\n",(p->linesect+i)->RelatedXL1);
			//printf("RL2\t%f\tXL2\t%f\n",(p->linesect+i)->RelatedRL2,(p->linesect+i)->RelatedXL2);
			//printf("MarColumnThous\t%u\n",(p->linesect+i)->MarkColumnThous);
			//printf("MarColumnHundr\t%u\n\n",(p->linesect+i)->MarkColumnHundr);
		};
	};
	return 0;
};

int prnRgsetSwich(rgset* p) {
	if(p != NULL && p->swich != NULL && p->title->CountSwich != 0) {
		printf("\n\n----------------------------Swiches-------------------------------\n");
		for (int i = 0; i < p->title->CountSwich; i++) {
			printf("Name\t%s\n",utf((p->swich+i)->Name));
			printf("NumBin\t%u\n",(p->swich+i)->NumBin);
			printf("CurPos\t%u\n",(p->swich+i)->CurPos);
			printf("LineNumb\t%u\n",(p->swich+i)->LineNumb);
			printf("AllowedCountOpp\t%f\n",(p->swich+i)->AllowedCountOpp);
			printf("WearRatio1st\t%f\n",(p->swich+i)->WearRatio1st);
			printf("WearRatio2st\t%f\n",(p->swich+i)->WearRatio2st);
			printf("WearRatio3st\t%f\n",(p->swich+i)->WearRatio3st);
			printf("WearRatio4st\t%f\n",(p->swich+i)->WearRatio4st);
			printf("CountOppA1st\t%u\n",(p->swich+i)->CountOppA1st);
			printf("CountOppA2st\t%u\n",(p->swich+i)->CountOppA2st);
			printf("CountOppA3st\t%u\n",(p->swich+i)->CountOppA3st);
			printf("CountOppA4st\t%u\n",(p->swich+i)->CountOppA4st);
			printf("CountOppB1st\t%u\n",(p->swich+i)->CountOppB1st);
			printf("CountOppB2st\t%u\n",(p->swich+i)->CountOppB2st);
			printf("CountOppB3st\t%u\n",(p->swich+i)->CountOppB3st);
			printf("CountOppB4st\t%u\n",(p->swich+i)->CountOppB4st);
			printf("CountOppC1st\t%u\n",(p->swich+i)->CountOppC1st);
			printf("CountOppC2st\t%u\n",(p->swich+i)->CountOppC2st);
			printf("CountOppC3st\t%u\n",(p->swich+i)->CountOppC3st);
			printf("CountOppC4st\t%u\n",(p->swich+i)->CountOppC4st);
			printf("NumBinA\t%u\n",(p->swich+i)->NumBinA);
			printf("NumBinB\t%u\n",(p->swich+i)->NumBinB);
			printf("NumBinC\t%u\n",(p->swich+i)->NumBinC);
			printf("NumChanA\t%u\n",(p->swich+i)->NumChanA);
			printf("NumChanB\t%u\n",(p->swich+i)->NumChanB);
			printf("NumChanC\t%u\n\n",(p->swich+i)->NumChanC);
		};
	};
	return 0;
};


int prnRgsetAll(rgset* p) {
	if(p != NULL) {
		prnRgsetTitle(p);
		prnRgsetChanel(p);
		prnRgsetLines(p);
		prnRgsetReg(p);
		prnRgsetBin(p);
		prnRgsetMark(p);
		prnRgsetLineSect(p);
//		prnRgsetSwich(p);
	};
	return 0;
};

/* Функкция инициализации rgset */
rgset* rgsetInit(char* file_name) {
	/* Виділення пам'яті під структуру rgset */
	rgset* rp = malloc(sizeof(rgset));
	if(rp == NULL) {
		printf("Memory for struct rgset is not allocated\n");
		return NULL;
	};
	rp->bin = NULL;	
	
	char vers[] = "21";
	if	(file_to_ram(rp, file_name) == 0){
		rp->title = rp->file_pointer;
		if(!strstr((rp->title)->Version, vers)) { 
			printf("Версия rgset.dat отличается от 21\n");
			return NULL;
		}
		else { // Инициализация структур данных Rgset.dat
				rp->chanel = (rgset_chanel*)((rp->title)->OffsetChanel+(uintptr_t)rp->title);
			rp->line = (rgset_line*)(rp->title->OffsetLine+(uintptr_t)rp->title);
			rp->reg =(rgset_reg*)(rp->title->OffsetReg+(uintptr_t)rp->title);
			rp->bin = (rgset_bin*)Malloc(sizeof(rgset_bin)*rp->title->CountBinSignal);
			if (rp->bin != NULL) init_bin_arr((uint16_t*)(rp->title->OffsetBin+(uintptr_t)rp->title), rp->bin, rp->title->CountBinSignal);
			else printf("Memory for binary signals is not allocated\n");
			rp->mark = (rgset_mark*)(rp->title->OffsetMark+(uintptr_t)rp->title);
			rp->linesect = (rgset_linesect*)(rp->title->OffsetLineSect+(uintptr_t)rp->title);
			rp->swich = (rgset_swich*)(rp->title->OffsetSwich+(uintptr_t)rp->title);
			return rp;
		};
	}
	else return NULL;
};


/* Функкция закрытия rgset */
void rgsetClose(rgset* rp) {
	if (rp != NULL) {
	if(rp->bin!= NULL) free(rp->bin);
	if(rp->file_descr != 0) file_close(rp);
	else {
		free (rp->title);
	}	
	free(rp);
	}
};

// Функция определения обобщенного коэфициента канала по его номеру в rgset.dat
float mainratio(rgset* rp, int chnumber) {
	if((rp->reg + rp->chanel->RegNumber)->AdcType == 3) return (rp->chanel+chnumber)->K5 / 8191 * (rp->chanel+chnumber)->K3 * (rp->chanel+chnumber)->K2;
	return (rp->chanel+chnumber)->K5 / 2047 * (rp->chanel+chnumber)->K3 * (rp->chanel+chnumber)->K2;
};

// Функция для определения количества отсчетов за период 20 мс (обратно проп. частоте дискретизации)
int findperiod(rgset* rp) {
	const char NameStation2000Hz[] = "ЮУАЭС Блок 1";
	if(strcmp(NameStation2000Hz, utf(rp->title->NameStation)) == 0) return 40;
	else return 20;
};

int rgsetSplit(rgset* rp) { 
	 void* tmp = malloc(sizeof(rgset_title));
	 if (tmp == NULL) 	return -1;
	 memcpy (tmp, rp->title, sizeof(rgset_title));
	 rp->title = tmp;
	
	 tmp = array_new(rp->title->CountChanel,sizeof(rgset_chanel));
	 if(tmp == NULL)	return -1;
	 memcpy(tmp, rp->chanel, sizeof(rgset_chanel)*rp->title->CountChanel);
	 rp->chanel = tmp;
	 
	 tmp = array_new(rp->title->CountLine,sizeof(rgset_line));
	 if(tmp == NULL)	return -1;
	 memcpy(tmp, rp->line, sizeof(rgset_line)*rp->title->CountLine);
	 rp->line = tmp;
	 
	 tmp = array_new(rp->title->CountReg,sizeof(rgset_reg));
	 if(tmp == NULL)	return -1;
	 memcpy(tmp, rp->reg, sizeof(rgset_reg)*rp->title->CountReg);
	 rp->reg = tmp;
	 
	 tmp = array_new(rp->title->CountBinSignal,sizeof(rgset_bin));
	 if(tmp == NULL)	return -1;
	 memcpy(tmp, rp->bin, sizeof(rgset_bin)*rp->title->CountBinSignal);
	 rp->bin = tmp;
	 
	 tmp = array_new(rp->title->CountMarkBinSignal,sizeof(rgset_mark));
	 if(tmp == NULL)	return -1;
	 memcpy(tmp, rp->mark, sizeof(rgset_mark)*rp->title->CountMarkBinSignal);
	 rp->mark = tmp;
	 
	  tmp = array_new(rp->title->CountLineSect,sizeof(rgset_linesect));
	 if(tmp == NULL)	return -1;
	 memcpy(tmp, rp->linesect, sizeof(rgset_linesect)*rp->title->CountLineSect);
	 rp->linesect = tmp;
	 
	 tmp = array_new(rp->title->CountSwich,sizeof(rgset_swich));
	 if(tmp == NULL)	return -1;
	 memcpy(tmp, rp->swich, sizeof(rgset_swich)*rp->title->CountSwich);	
	 rp->swich = tmp;
	 file_close(rp);
	rp->file_descr = 0;
	return 0;
};

		int rgsetUnit(rgset* rp) { /* НЕ РЕАЛІЗОВАНО */
	return -1;
};

int rgsetAddChanel(rgset* pointer, int chNumb) { 
	pointer->title->CountChanel++;
	pointer->chanel = array_add((void*)pointer->chanel, chNumb , 1);
	
	return 0;
};

int rgsetDelChanel(rgset* pointer, int chNumb) { 
	if (pointer->title->CountChanel < 1) {
		printf("Неможливо видалити (канали відсутні)");
		return -1;
	}
	else
	pointer->title->CountChanel--;
	pointer->chanel = array_cut((void*)pointer->chanel, chNumb, 1);

	return 0;
};

int rgsetAddReg(rgset* pointer, int regNumb) {//не реалізовано
	//pointer->title->CountReg++; 
	//pointer->reg = array_add((void*)pointer->reg, regNumb , 1);
	return -1;
};

int rgsetDelReg(rgset* pointer, int regNumb) { // не реалізовано
	//if (pointer->title->CountReg < 1) {
		//printf("Неможливо видалити (регістратори відсутні)");
		//return -1;
	//}
	//else
	//pointer->title->CountReg--;
	//pointer->reg = array_cut((void*)pointer->reg, regNumb , 1);
	return -1;
};

rgset* rgsetNew() { 	
	rgset* rp = malloc(sizeof(rgset));
	if (rp == NULL) return NULL;
	memset((void*)rp, 0, sizeof(rgset));
	rp->title = malloc(sizeof(rgset_title));
	if (rp->title == NULL) {
		free (rp);
		return NULL;
	}
	memset((void*)rp->title,0, sizeof(rgset_title));
	strcpy(rp->title->Version, "21");
return rp;
};

int rgsetSave(rgset* pointer, char* filename) { /* НЕ РЕАЛІЗОВАНО */
	return 0;
};


