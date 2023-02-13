/* norm.h */

#ifndef NORM
#define NORM

#pragma pack(push,1)

/* Каналы линии */
typedef struct ch_ratio { // Длина 19 байт
	char Void0; 		// [00-00] Нули
	uint16_t ChNumb; 	// [01-02] Номер канала из Rgset.dat
	char Void1[4]; 		// [03-06] Нули
	float ChRatio; 		// [07-10] Коэффициент связи между кодами АЦП и первичными величинами(из Rgset.dat)
	char Void2[8]; 		// [11-18] Нули
} ch_ratio;


/* Расчетные пераметры линии */
typedef struct calc_value { // Длина 108 байт
	float Ua;		// [000-003]
	float Ub;		// [004-007]
	float Uc;		// [008-011]	
	float Ia;		// [012-015]
	float Ib;		// [016-019]
	float Ic;		// [020-023]
	float Pa;		// [024-027]
	float Pb;		// [028-031]
	float Pc;		// [032-035]
	float Psum;		// [036-039]
	float Qa;		// [040-043]
	float Qb;		// [044-047]
	float Qc;		// [048-051]
	float Qsum;		// [052-055]
	float Sa;		// [056-059]
	float Sb;		// [060-063]
	float Sc;		// [064-067]
	float Ssum;		// [068-071]
	char Void0[3];	// [072-074] Три единицы
	float Void1;	// [075-078]
	float Void2;	// [079-082]
	float Void3;	// [083-086]
	float Angle_a;	// [087-090]
	float Angle_b;	// [091-094]
	float Angle_c;	// [095-098]
	float Cos_phi;	// [099-102]
	char Void4[4];	// [103-106]
	char Status;	// [107-107] Статус 0-обычная линия 3I+3U, 1-линия пост. тока, 2-междуфазное напряжение
} calc_value;


/* Описания линии */
typedef struct norm_line { // длина 224 байта
	uint16_t LineNumb; 		// [000-001] Номер линии из Rgset.dat
	ch_ratio ratio[6]; 		// [002-115] Массив коэффициентов каналов
	calc_value calc; 		// [116-223] Структура с расчетными значениями
} norm_line;


/* Заголовок файла */
typedef struct norm_title { // длина 322 байта
    uint16_t RegNumb; 	// [000-001] Номер регистратора
    char Void1[6]; 		// [002-007] ?? Поля не изменные во всех файлах 10, 0, 32, 8, 48, 0
    uint32_t RegTime; 	// [008-011] Время регистратора в формате Юникс
    char Day;	 		// [012-012] Текущий день
    char Month; 		// [013-013] Текущий месяц
    uint16_t Year; 		// [014-015] Текущий год
    char Hour; 			// [016-016] Текущий час
    char Minute; 		// [017-017] Текущая минута
    char Second; 		// [018-018] Текущая секунда
    char Void2[6]; 		// [019-024] ?? Нули	
    char Void3[2]; 		// [025-026] ?? Два байта с неизвестным назначением
    uint16_t LineCount; // [027-028] Количество линий в данном регистраторе
    char Flag; 			// [029-029] Флаг состояния 0-нормальный режим; 1-запись аварии; 2-запуск аварии.	
    char Void4[4]; 		// [030-033] ?? Нули	
    uint16_t ChNumb[32]; 	// [034-097] ?? Перечисление от 1 до 32-го канала
    uint16_t Bin[48]; 	// [098-193] Матрица дискретных сигналов
	float RMS[32]; 		// [194-321] Масив действующих значений аналоговых каналов
} norm_title;

#pragma pack(pop)

/* Структура norm */
typedef struct norm {
	int file_descr;	// Файловый дискриптор на normX.dat [Всегда первый в структуре]
	long int size;	// Размер файла normX.dat [Всегда второй в структуре]
	norm_title* title; // Указатель на заголовок [Всегда третий в структуре]
	norm_line* line; // Указатель на блок линии
	} norm;

/* Функция инициализации структуры norm */
int norm_init(norm* p, char* file_name);

/* Функция закрытия объекта norm */
int norm_close(norm* p); 

#endif
