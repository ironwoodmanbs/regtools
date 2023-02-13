typedef struct extremum {
	float before;
	float max;
	float min;
	float extrem;
	float z_min;
	float z_max;
} extremum;

typedef struct compl {
	double a;
	double b;
	double z;
	double phi;
} compl;

/* Функция поиска экстремума в масиве "сырых" аналоговых данных. Результат работы заносится в переменную по адресу extr */
int find_extremum (int16_t* first, int count, unsigned int period_of_signal, extremum* extr);

/* Функция для раскладывания масивы "сырых" аналоговых данных в масив векторных величин первой гармоники типа compl */
int fourier(int16_t* data, int count, unsigned int period_of_signal, compl* value);
