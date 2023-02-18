/* common.c */
#define _GNU_SOURCE
#include <iconv.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include "common.h"
#define LENGHT 400 

/* функция, обрабатывающая ошибки malloc() */
void* Malloc(size_t size) {
	void* res = malloc(size);
	if(res == NULL) {
		perror("Memory is not allocated");
		exit(EXIT_FAILURE);
	};
	return res;
}

/* Функция для вывода строковых данных фиксированной длины */
void prnFix(char* pt, int size, int step) {
	int l1 = strlen(pt);
	if(l1 <= size) {
		printf("%s",utf(pt));
		for(int i = 0; i < step-l1; i++) printf(" ");
	}
	else {
		char tmp[l1 + 1];
		strcpy(tmp, pt);
		tmp[size] = 0;
		printf("%s", utf(tmp));
		for(int i = 0; i < step-size; i++) printf(" ");
	};
};

static char buf[LENGHT];
/* Функция перевода строки из CP866 в UTF */
char* utf(char* from) {
	bzero((void*)buf, LENGHT); // Очистка buf
	iconv_t conv = iconv_open("UTF-8","CP866");
	size_t Lfrom, Lto;
	char* my_buf = buf;
	Lfrom = (strlen(from)+1);
	Lto = 2*Lfrom;
	iconv(conv, &from, &Lfrom, &my_buf, &Lto);
	iconv_close(conv);
	return buf;
};

static char buf2[LENGHT];
/* 2-я Функция перевода строки из CP866 в UTF */
char* utf2(char* from) {
	bzero((void*)buf2, LENGHT); // Очистка buf2
	iconv_t conv = iconv_open("UTF-8","CP866");
	size_t Lfrom, Lto;
	char* my_buf = buf2;
	Lfrom = (strlen(from)+1);
	Lto = 2*Lfrom;
	iconv(conv, &from, &Lfrom, &my_buf, &Lto);
	iconv_close(conv);
	return buf2;
};

/* Функция перевода строки из CP1251 в UTF */
char* cp1251_to_utf(char* from) {
	bzero((void*)buf, LENGHT); // Очистка buf
	iconv_t conv = iconv_open("UTF-8","CP1251");
	size_t Lfrom, Lto;
	char* my_buf = buf;
	Lfrom = (strlen(from)+1);
	Lto = 2*Lfrom;
	iconv(conv, &from, &Lfrom, &my_buf, &Lto);
	iconv_close(conv);
	return buf;
}

long int filesize(char *filename)
{
	struct stat buffer;
	if (stat(filename, &buffer) == 0){
		return (unsigned int)buffer.st_size;
	} else return -1;
};

void printBits(size_t const size, void const* ptr) { // Функкция печати числа в двоичном формате
	unsigned char* b = (unsigned char*)ptr;
	unsigned char byte;
	int i, j;
	for(i=size-1; i >= 0; i--) {
		for(j=7; j >=0; j--) {
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		};
	};
};

int inv(int a) { // Функция инвертирования
	if(a == 0) return 1;
	else return 0;
};

uint16_t bite_image(int Razr) { // Функция битового образа
	uint16_t tmp = 1;
	tmp = tmp << (Razr-1);
	return tmp;
};

/* Функции помещения файла file_name с диска в оперативную память */
int file_to_ram(void* p, char* file_name) {	
	common_file* file = p;

	// Определяем размер файла 
	file->file_size = filesize(file_name);
	if (file->file_size == -1) {
		perror("Ошибка определения размера файла");
		return -1;
	}
	else {
		// Проверка на условие, что размер файла не равен 0
		if (file->file_size == 0) {
			printf("Размер файла %s равен 0 \n", file_name);
			return -1;
		};
		
		// Определяем дескриптор файла
		file->file_descr = open(file_name,O_RDWR);
		if (file->file_descr == -1) {
			perror("Ошибка открытия файла");
			return -1;
		}
		else {
			
			/* Вычисляем указатель на первый байт памяти, куда помещен файл */
			file->file_pointer = mmap(0, file->file_size, PROT_READ, MAP_SHARED, file->file_descr, 0);
 			if (file->file_pointer == NULL) {
				perror("Ошибка маппинга файла в память");
				return -1;
			}
		}
	return 0;
	};
};

/* Функция закрытия файла */
int file_close(void* p) {
	common_file* file = p;
	if(file->file_pointer != NULL) {
		if (munmap(file->file_pointer, file->file_size) == 0) { 
			if(close(file->file_descr) == 0) {
				return 0;
			}
			else {
				perror("Ошибка закрытия файла");
				return -1;
			};
		}
		else {
				perror("Ошибка демапинга файла");
				return -1;
		};
	};
	return -1;
};

// Функция для заполнения strTime локальным датой, временем в формате ГГГГ-ММ-ДД ЧЧ:ММ:СС:МИЛ
static char str[STR_TIME_LENGHT]; // Выделение области для хранения даты времени в текстовом формате
char* str_local_time(DayTime* p) {
	time_t my_time = 0;
	struct tm grinv_time;
	struct tm* local_time;
	grinv_time.tm_year = p->Year - 1900;
	grinv_time.tm_mon = p->Month - 1;
	grinv_time.tm_mday = p->Day;
	grinv_time.tm_hour = p->Hour;
	grinv_time.tm_min = p->Minute;
	grinv_time.tm_sec = p->Second;
	grinv_time.tm_isdst = 0;
	my_time = mktime(&grinv_time);
	my_time = my_time + 7200;
	local_time = localtime(&my_time);
	sprintf(str, "%u-%-2.2u-%-2.2u %-2.2u:%-2.2u:%-2.2u", local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
	return str;
};

/* Печать матриц дискретных сигналов */
void prnMatrixBin(uint16_t* bp) {
	printf("\n---------------- СОСТОЯНИЕ ДВОИЧНЫХ СИГНАЛОВ -----------------\n");
	printf("           M1                  M2                  M3\n");
	printf("--------------------------------------------------------------\n");
	printf("                         Р а з р я д ы \n");
	printf("Гр  6543210987654321    6543210987654321    6543210987654321\n");
	for(int i = 0; i < 16; i++) {
		printf("%-3.2d ", i+1);
		printBits(2, bp+i*3);
		printf("    ");
		printBits(2, bp+i*3+1);
		printf("    ");
		printBits(2, bp+i*3+2);
		printf("\n");
	};
};


/* Вырезание или добавление блока файла в оперативной памяти */
void* change_file(common_file* p, void* from_adress, size_t size, enum FileChangeMode mode){
	/* | Первый, фиксированный, неперемещаемый блок | Второй блок, удаляемый при перемещении | Третий перемещаемы блок | */
	size_t fixed_block_size = (uintptr_t)from_adress - (uintptr_t)p->file_pointer; /* Размер первого (фиксированного) блока  */
	/* Размер второго блока - в переменной size  */
	size_t moved_block_size = p->file_size - fixed_block_size - size; /* Размер третьего (перемещаемого) блока  */
	size_t old_size = p->file_size;	
	size_t new_size = p->file_size;	
	switch(mode) {
		case CUT:
		//	printf("CUT section\nnew_adress:\t%p\nold_adress:\t%p\nblock_size\t%i\n", from_adress, (void*)((uintptr_t)from_adress + size), moved_block_size);
			memmove(from_adress, (void*)((uintptr_t)from_adress + size), moved_block_size);
			new_size = old_size - size;
			break;
		case ADD:
		//	printf("ADD section\nnew_adress:\t%p\nold_adress:\t%p\nblock_size\t%i\n", from_adress, (void*)((uintptr_t)from_adress + size), moved_block_size);
			memmove((void*)((uintptr_t)from_adress + size), from_adress, moved_block_size);
			new_size = old_size + size;
			break;
	}
			p->file_size = new_size;
		//	printf("mremap:\nfile_pointer: %p\nold_size: %i\nnew_size: %i\nsize: %i\n", p->file_pointer, old_size, new_size, size);
	return	mremap(p->file_pointer, old_size, new_size, 0); // Возвращаем указатель на новый file_poinrer
};
