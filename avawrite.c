/* avawrite.c */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "ulist.h"
#include "rgset.h"
#include "ava.h"
#include "common.h"
/* Возможные опции вызова программы
 * 
 * avawrite avafile --binadd Group Razr Tact 
 * Добавляет в файл avafile дискретную сработку группы Groupe, разряда Razr в такт Tact.
 * 
 * avawrite avafile --bincut Groupe Razr [Tact] 
 * В файле avafile удаляет дискретную сработку группы Groupe, разряда Razr в такт Tact. 
 * Если Tact отрицательный или отсутствует - удаляет все сработки группы Groupe, разряда Razr. 
 *
 * avawrite avafile --binsset Groupe Word
 * В файле avafile выполняет начальную (доаварийную) установку состояния разрядов группы Groupe в соответствии с числом Word. 
 * Число Word представляет собой двухбайтовое представление состояния 16 разрядов. 
 * Сработанному состоянию разряда соответствует 0, несработанному - 1.
 * Пример представления числа Word для сработанного 1 и 4 разрядов:
 * 1111111111110110 = 65526
 */

int main(int argc, char** argv) {
/*	if(argc != 2) {
		printf("Используй avapars avaXXXX.dat");
		return -1;
	}
	else { */
		struct ava p;
		p.file_descr = open(argv[1], O_RDONLY); //Открытие файла в режиме чтение
		p.size = filesize(argv[1]); // Определение размера файла
		p.title = Malloc(p.size + sizeof(ava_bin)); // Выделение памяти под файл
		Read(p.file_descr, p.title, p.size); // Загрузка файла в память	
		if (avaInit(&p) != 0) {
			printf("\nОшибка инициализации %s\n",argv[1]);
			return -1;
			}
		else {
			close(p.file_descr);
			avaBinInit(&p);
			//ava_binary_add(&p, 121, 12, 13);
			//ava_binary_add(&p, 123, 14, 15);
			ava_binary_cut(&p, 121, 12, 13);
			ava_bin_deinit(&p);
			p.file_descr = open(argv[1], O_WRONLY | O_TRUNC); //Открытие файла в режиме записи
			Write(p.file_descr, p.title, p.size);	
			free(p.title);
		};
		close(p.file_descr);
		return 0;
};
