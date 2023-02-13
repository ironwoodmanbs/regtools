/* common.h */

#ifndef COMMON
#define COMMON

// Обобщенная структура для хранения информации об открытом файле
typedef struct common_file {
	int file_descr;
	long int file_size;
	void* file_pointer;
} common_file;

enum FileChangeMode {
	ADD = 1,
	CUT = 2
};

// Структура для хранения данных о дате и времени
#define STR_TIME_LENGHT 40
#pragma pack(push,1)
typedef struct DayTime {	
	char Day;	 		// День
    char Month; 		// Месяц
    uint16_t Year; 		// Год
    char Hour; 			// Час
    char Minute; 		// Минута
    char Second; 		// Секунда
} DayTime;
#pragma pack(pop)

// Функция для заполнения strTime локальным датой, временем в формате ГГГГ-ММ-ДД ЧЧ:ММ:СС:МИЛ
char* str_local_time(DayTime* p);

void* Malloc(size_t size); 
void prnFix(char* pt, int size, int step);
char* utf2(char* from);
char* utf(char* from);
char* cp1251_to_utf(char* from);
long int filesize(char* filename);
void printBits(size_t const size, void const* ptr); // Функкция печати числа в двоичном формате
int inv(int a); // Функция инвертирования двоичного (бинарного) значения
uint16_t inv_16(uint16_t a, uint16_t b); // Функция инвертирования битов числа 'a' для которых биты числа 'b' равны 1
uint16_t bite_image(int Razr); // Перевод из номера разряда в битовый образ

/* Функции помещения файла с диска в оперативную память */
/* Принимает имя файла, и указатель на указатель в памяти, где будет располагаться первый байт файла */
/* В случае ошибки - возвращает -1 */
int file_to_ram(void* p, char* file_name);  

// Функция закрытия файла
int file_close(void* p); 

/* Печать матриц дискретных сигналов */
void prnMatrixBin(uint16_t* bp);

/* Вырезание или добавление блока файла в оперативной памяти */
void* change_file(common_file* p, void* from_adress, size_t size, enum FileChangeMode mode);

#endif
