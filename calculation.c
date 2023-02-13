#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "calculation.h"
#include "common.h"
#include <math.h>
#define Pi 3.14159265

static inline void ab_to_rp(compl*);

int find_extremum (int16_t* data, int count, unsigned int period, extremum* extr) {
	unsigned long long temp = 0;
	unsigned long sq = 0;
	int i;
	for(i = 0; i < period; i++) {
		temp = temp + data[i] * data[i];
	};
	extr->before = sqrtf(temp/period);
	unsigned long min = temp;
	unsigned long max = temp;
	int number = 0;
	for(i = period; i < count; i++) {
		sq = data[i] * data[i];
		number = i - period;
		temp = temp + sq - data[number] * data[number];
		if (temp > max) max = temp;
		if (temp < min) min = temp;
	};
	extr->max = sqrtf(max/period);
	extr->min = sqrtf(min/period);

	/* Получения данных о первой гармонике */
	compl* compl_p;
	compl_p	= Malloc(sizeof(compl) * (count - period)); // Выделение памяти для масива веркторных величин
	fourier(data, count, period, compl_p); // Заполнение массива векторных величин
	float z_temp = compl_p[0].z;
	extr->z_max = z_temp;
	extr->z_min = z_temp;
	for(i = 0; i < count - period; i++) {
		z_temp = (float)compl_p[i].z;
		if (z_temp > extr->z_max) extr->z_max = z_temp;
		if (z_temp < extr->z_min) extr->z_min = z_temp;
	};
	extr->z_max = extr->z_max / period;
	extr->z_min = extr->z_min / period;
	free(compl_p); // Освобождение памяти
	return 0;
};
/*
* Функция для формирования масива векторных величин первой гармоники
*/
int fourier(int16_t* data, int count, unsigned int period, compl* dest) {
	if(count < period) return -1; /* Проверка превышения количество отсчетов к периоду */
	double dcos[period];
	double dsin[period];
	int i, index;
	compl numb = {0, 0, 0, 0};
	/* Заполнение масивов синусов и косинусов */
	for(i = 0; i < period; i++) { 
		dcos[i] = cosf(i*2*Pi/period);
		dsin[i] = sinf(i*2*Pi/period);
	};
	/* Определяем вектор первой гармоники на первом периоде */
	for(i = 0; i < period; i++) { 
		numb.a = numb.a + data[i] * dcos[i % period];
		numb.b = numb.b + data[i] * dsin[i % period];
		ab_to_rp(&numb);	
		/* Запись в масив */
		dest->a = numb.a;
		dest->b = numb.b;
		dest->z = numb.z;
		dest->phi = numb.phi;
		//printf("cos %f\t data %d\ta %f\n", dcos[i % period], *(data+i), a);
	};
	/* Определяем вектор первой гармоники на всем протяжении записи */
	for(i = period; i < count; i++) {
		index = i - period;
		numb.a = numb.a + (data[i] - data[index]) * dcos[i % period];
		numb.b = numb.b + (data[i] - data[index]) * dsin[i % period];
		ab_to_rp(&numb);	
		/* Запись в масив */
		dest[index].a = numb.a;
		dest[index].b = numb.b;
		dest[index].z = numb.z;
		dest[index].phi = numb.phi;
	};
	return 0;
};

/* Преобразование из алгебраической формы комплексного числа(X+iY) в показательную (R*e^Phi) */
static inline void ab_to_rp(compl* numb) {
	numb->z = sqrtf(numb->a * numb->a + numb->b * numb->b);
	if(numb->a == 0) {
		if(numb->b == 0) numb->phi = 0;
		if(numb->b > 0) numb->phi = Pi/2;
		if(numb->b < 0) numb->phi = -Pi/2;
	}
	else {
		if (numb->a > 0) numb->phi = atanf(numb->b/numb->a);
		if (numb->a < 0) numb->phi = atanf(numb->b/numb->a)+Pi;
	};
};

