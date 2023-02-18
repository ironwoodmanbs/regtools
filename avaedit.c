/* avawrite.c */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "list.h"
#include "rgset.h"
#include "ava.h"
#include "common.h"

/* Добавление объекта ava_bin_i  */
void ava_bin_add(ava* p, int Tact, int Group, int Razr) {
	list* ls = p->list_bin_i;
	ls->data = Malloc(sizeof(ava_bin_i));
	ava_bin_i* d = (ava_bin_i*)ls->data;
	d->Tact = Tact;
	d->Group = Group;
	d->Razr = Razr;
}


/* Поск по Такту, Группе и Разряду объекта типа ava_bin_i и его последующее удаление. При неуспешном поиске, ничего не удаляет и возвращает -1 */
/*
int ava_bin_cut(ava* p, int Tact, int Group, int Razr){
	if(p->ba.count > 0) {
		ulist* ls = ul_first(&p->ba); // Переход в начало списка
		do {
			ava_bin_i* d = (ava_bin_i*)ls->data;
			if(d->Tact == Tact && d->Group == Group && d->Razr == Razr) { // Проверка соответствия Такта, Группы, Разряда
				while(ls->next) ls = ul_down(&p->ba); // Опускаем найденный элемент в низ списка
				free(ls->data);
				ul_del(&p->ba); // Удаление элемента списка и выход из функции
				return 0;
			};
			ls = ul_next(&p->ba);
		}
		while(ls);
	};
	return -1; // Выход с ошибкой при неуспешном поиске
};
*/



int main(int argc, char** argv) {
/*	if(argc != 2) {
		printf("Используй avapars avaXXXX.dat");
		return -1;
	}
	else { */
		ava p;
		if (file_to_ram(&p, argv[1]) != 0) {
			printf("\nОшибка открытия %s\n",argv[1]);
			return -1;
		};
		void* ap = malloc(p.size);
		printf("New adr: %p\n", ap);
		void* dest = memcpy(ap, p.title, p.size);
		size_t file_size = write(p.file_descr, ap, p.size);	
		printf("Dest: %p\tFile size: %ld\n", dest, file_size);
		if (ava_init(&p) != 0) {
			printf("\nОшибка инициализации %s\n",argv[1]);
			return -1;
			}
		else {
			//ava_bin_init(&p);
			//ava_binary_add(&p, 121, 12, 13);
			//ava_binary_add(&p, 123, 14, 15);
			//ava_binary_cut(&p, 0, 13, 6);
			//ava_bin_deinit(&p);
			ava_close(&p);
		};
		return 0;
};
