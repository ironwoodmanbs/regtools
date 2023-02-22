/* ava.h  */
#ifndef AVA
#define AVA

#pragma pack(push,1)

typedef struct ava_title {
    char name[12]; // REGINA######
    uint16_t TactDuration; // Длительность такта
    uint16_t TactBefore; // Количество предаварийных тактов
    uint32_t TactCount; // Количество тактов
    char Couse; // Причина аварии
    char Event; // Событие
    uint16_t NumChanel; // Номер канала
    uint16_t Settings; // Значение уставки
    double PrimFactor; // Первичный коэффициент
    char CalcSettingsType; // Тип расчета уставки
    uint16_t NumGrpRellay; // Номер группы реле
    uint16_t GroupStatus; // Сотояние группы
    uint16_t GroupStandard; //Эталон группы
    uint16_t AdcType; // Тип АЦП
    uint16_t RellayCanal; // Rellay canal
    uint32_t OffsetMainTitle; // Смещение основного заголовка
    uint32_t OffsetAddTitle; // Смещение дополнительного заголовка
    uint32_t Flags; // Флажки
    uint32_t ServiceTimeEvent; // Служебное время аварии
    uint16_t ServiceTimeSwich; // Служебное время выкл.
    uint16_t ServiceTimeFF_min; // Служебное время ff_min
    uint16_t ServiceTimeNtact; // Служебное время ntact
    char UserInfo[200]; // Информация пользователя
	uint16_t Settings_count; // Количество уставок по каналам
	uint16_t Comb_settings_count; // Количество комбинированных уставок по каналам
	uint16_t Ava_time_corection; // Уточнение времени аварии в наносекундах
	float Adc_correction_ratio; // Коэффициент поправки АЦП. rgsetw показывает 1.0, а в файле присутствует 1.875
	uint16_t Offset_cause_file_saving; // Смещение причины записи файла
	char Unknown1[6];
	uint16_t Bin_signal_count; // Количество дискретных сигналов
	char Unknown2[28];
} ava_title;

typedef struct ava_add_title {
    uint16_t CountChannel; // Количество каналов
    uint16_t NumSettings; // Номер уставки
    uint32_t OffsetAddInfo; // Смещение доп. инфо
} ava_add_title;

typedef struct ava_main_title {
    char DayFault;
    char MonthFault;
    uint16_t YearFault;
    char HourFault;
    char MinuteFault;
    char SecondFault;
    uint16_t MilsecFault;
    char DateTimeRecord[9];// В староой версии фиксировалось дата, время записи. В новой постоянная последовательность байт 0, 202, 154, 59, 2, 0, 0, 0, 0.
    char RecordVersion;
    char CountStatus;
    char RecordType;
    char RegNum;
    uint16_t CountBin;
    uint16_t CountChanel;
    uint16_t CountTacts;
    uint32_t OffsetBin;
    uint32_t OffsetChanel;
} ava_main_title;

typedef struct ava_bin { // Структура, описывающая хранение информации в файле ava о двоичных сработках
	uint32_t Tact; //0-3 Такт появления двоичного сигнала
	uint16_t GroupNumb; //4-5 Номер группы сигнала (матрица х группа)
	uint16_t Status; //6-7 16-ти битный образ (разряды)
} ava_bin;

typedef struct ava_setting {
	uint8_t Chanel_type; // Тип канала
	uint8_t Setting_type; // Тип уставки
	uint16_t Chanel_number; // Номер канала
	uint16_t Setting_value; // Значение уставки
	char Unknown1[6];
	float Secondary_Ratio; // Вторичный коэфициент. rgsetw показывает коэфициент вторичной цепи. В файле записано значение равное произведению значения уставки (в кодах АЦП) на коэфициент вторичной цепи на поправосный коэфициент 
	uint8_t Setting_calc_type; //  Тип расчета уставки
	uint16_t Reley_number; // Номер реле
} ava_setting;

#pragma pack(pop)

typedef struct ava {
	int file_descr;	// Файловый дискриптор [Всегда первый в структуре]
	long int size;	// Размер файла [Всегда второй в структуре]
	ava_title* title; // Ссылка на заголовок [Всегда третий в структуре]
	ava_add_title* add_title;
	ava_main_title* main_title;
	uint16_t* start_bin; // Начальное состояние двоичных сигналов (адрес = &ava_binary - 96)
	ava_bin* bin; // Начало блока двоичных сработок
	int16_t* chanel; // Начало блока аналоговых сигналов
	list* list_bin_i;
} ava;

typedef struct CpxGrp { // Структура описывающая номер группы с полями Матрица, Группа
	int Matrix;
	int Group;
} CpxGrp;

typedef struct ava_bin_i { // Структура инициализированных (развернутых) данных о двоичных сработках 
	int Tact;
	int Group;
	int Razr;
	int Status;
} ava_bin_i;

int avaInit(ava* p); // Прототип функции инициализации структуры ava
int avaClose(ava* p); // Прототип функции закрытия avaxxxx.dat
int avaFindChNumb(rgset* pr, ava* ap, int i); // Функция определения номера канала в rgset.dat по номеру канала в avaxxxx.dat
int avaCpxToGrp(CpxGrp complrx); // Функция перевода номера группы из комплексного в машинный формат
CpxGrp avaGrpToCpx(int MashGrp); // Функция перевода номера группы из машинного формата в комплексный
int avaBinInit(ava* p);  // Инициализация (разворачивание двоичных сработок из ava_bin в ava_bin_i)
void avaBinClose(ava* p); // Закрытие двоичных сработок, очистка памяти (удаление объектов ava_bin_i)
#endif
