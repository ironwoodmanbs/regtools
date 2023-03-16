/* rgset.h */

#ifndef RGSET
#define RGSET

#pragma pack(push,1)

typedef struct rgset_title { 			// [0 - ???]
		char Version[20]; 				// [0 - 19]
		char NameStation[40]; 			// [20 - 59]
		char NameArch[20]; 				// [60 - 79]
		char SpesialLine[24]; 			// [80 - 103]
		uint16_t CountChanel; 			// [104 - 105]
		uint16_t CountReg; 				// [106 - 107]
		uint16_t CountLine; 			// [108 - 109]
		uint16_t CountBinSignal; 		// [110 - 111]
		uint16_t CountMarkBinSignal; 	// [112 - 113]
		uint16_t MaxNumberSignal; 		// [114 - 115]
		uint16_t CountLineSect; 		// [116 - 117]
		uint16_t CountSwich; 			// [118 - 119]
		uint16_t CountCircleSettings; 	// [120 - 121]
		uint16_t CountTableSettings; 	// [122 - 123]
		uint16_t CountTransmisChanel; 	// [124 - 125]
		uint16_t CountAutotransf; 		// [126 - 127]
		uint16_t DeleyExpressInfo; 		// [128 - 129]
		uint32_t OffsetChanel; 			// [130 - 133]
		uint32_t OffsetLine; 			// [134 - 137]
		uint32_t OffsetReg;
		uint32_t OffsetBin;
		uint32_t OffsetMark;
		uint32_t OffsetLineSect;
		uint32_t OffsetSwich;
		uint32_t OffsetCircleSettings;
		uint32_t OffsetTableSettings;
		uint32_t OffsetTransmisChanel;
		uint32_t OffsetAutotransformer;
		uint32_t OffsetRelationsLineReg;
		//uint32_t CountSpecifLineProtection; 
		uint32_t OffsetAdditTitle;
		uint32_t CountSpecifLineProtection;
		uint32_t OffsetSpesifLineProtection;
		uint32_t CountSpecifStageProtection;
		uint32_t OffsetSpecifStageProtection;
		uint32_t OffsetAdditSpecifChanel;
		uint32_t CountProtectionZoneSectionallyLinear;
		uint32_t OffsetProtectionZoneSectionallyLinear;
		uint32_t ReservCount1;
		uint32_t ReservOffset1;
		uint32_t ReservCount2;
		uint32_t ReservOffset2;
		uint32_t ReservCount3;
		uint32_t ReservOffset3;
		uint32_t ReservCount4;
		uint32_t ReservOffset4;
		uint32_t ReservCount5;
		uint32_t ReservOffset5;
		uint32_t ReservCount6;
		uint32_t ReservOffset6;
		uint32_t ReservCount7;
		uint32_t ReservOffset7;
		uint32_t ReservCount8;
		uint32_t ReservOffset8;
		uint32_t ReservCount9;
		uint32_t ReservOffset9;
		uint32_t OffsetAdditisData;
	} rgset_title;
	
typedef struct rgset_chanel {
	char Name[40];
	char SymbolChanel[10];
	char SymbolPrimCircuit[10];
	char SymbolSecondCircuit[10];
	uint16_t ChNumber;
	uint16_t LineNumber;
	uint16_t RegNumber;
	uint16_t Void;
	uint8_t TypeChanel;
	uint8_t MarkChanel;
	uint8_t Phase;
	uint16_t FirstPseudoChanel;
	uint16_t SecondPseudoChanel;
	uint16_t ThirdPseudoChanel;
	uint16_t Void2;
	float K1;
	float K2;
	float K3;
	float K4;
	float K5;
} rgset_chanel;
	
typedef struct rgset_line { // 340 байт
	char Name[32]; 			// [0 - 31]
	uint16_t RegNumber; 	// [32 - 33]
	uint16_t LineType; 		// [34 - 35]
	uint16_t Void; 			// [36 - 37]
	float LineLenght; 		// [38 - 41]
	uint16_t PowerCalcLogic;// [42 - 43] 0-Нет; 1-По трем фазам; 2-По двум фазам; 3-Линия пост.тока
	char Void2[296]; 		// [44 - 339]
} rgset_line;

typedef struct rgset_reg {
    char Name[30];
    uint16_t CountTacts;
    uint16_t TactDuration;
    uint16_t KTactToMinute;
    uint16_t CountFrontTacts;
    uint16_t CountLines;
    uint16_t CountChanels;
    uint16_t MaxEntryAnalog;
    uint16_t MaxEntryBin;
    uint16_t MaxEntryBinNotFault;
    uint16_t NumbTransmChanel;
    uint16_t TransmRate;
    float MaxCurrentValue;
    float MaxVoltageValue;
    uint16_t RegType;
    uint16_t MaxBinNumber;
    char Void1[6];
    uint16_t CountBinSign;
    char Void2[12];
    uint16_t AdcType;
    char Void3[4];
    } rgset_reg;

typedef struct rgset_bin {
	char Name[48];
	char Panel[24];
	char Relay[24];
	uint16_t Numb;
	uint16_t Reg;
	uint16_t Type;
	uint16_t Flag;
} rgset_bin;
	
typedef struct rgset_mark {
	char Name[20];
	uint16_t Numb;
	char StatusOn[10];
	char StatusOff[10];
	uint16_t Position1;
	uint16_t Position2;
	uint16_t Count;
} rgset_mark;

typedef struct rgset_linesect {
    uint16_t LineNumb;
    uint16_t LineSectNumb;
    float LenghtSect;
    float R1Sect;
    float X1Sect;
    float R0Sect;
    float X0Sect;
    float R1Coil;
    float X1Coil;
    float R0Coil;
    float X0Coil;
    uint8_t Flags;
    uint8_t CountRelatedLine;
    uint16_t NumbRelLine1;
    uint16_t NumbRelLine2;
    uint16_t NumbRelLine3;
    uint16_t NumbRelLine4;
    uint16_t NumbRelLine5;
    uint16_t NumbRelLine6;
    uint16_t NumbRelLine7;
    uint16_t NumbRelLine8;
    uint16_t NumbRelLine9;
    uint16_t NumbRelLine10;
    float RelatedRL1;
    float RelatedXL1;
    float RelatedRL2;
    float RelatedXL2;
    float RelatedRL3;
    float RelatedXL3;
    float RelatedRL4;
    float RelatedXL4;
    float RelatedRL5;
    float RelatedXL5;
    float RelatedRL6;
    float RelatedXL6;
    float RelatedRL7;
    float RelatedXL7;
    float RelatedRL8;
    float RelatedXL8;
    float RelatedRL9;
    float RelatedXL9;
    float RelatedRL10;
    float RelatedXL10;
    uint16_t MarkColumnThous;
    uint16_t MarkColumnHundr;
    } rgset_linesect;
    
typedef struct rgset_swich {
    char Name[20];
    uint16_t NumBin;
    uint16_t CurPos;
    uint16_t LineNumb;
    float AllowedCountOpp;
    float WearRatio1st;
    float WearRatio2st;
    float WearRatio3st;
    float WearRatio4st;
    float Settings1st;
    float Settings2st;
    float Settings3st;
    float Settings4st;
    float ZeroTreshold;
    uint16_t CountOppA1st;
    uint16_t CountOppA2st;
    uint16_t CountOppA3st;
    uint16_t CountOppA4st;
    uint16_t CountOppB1st;
    uint16_t CountOppB2st;
    uint16_t CountOppB3st;
    uint16_t CountOppB4st;
    uint16_t CountOppC1st;
    uint16_t CountOppC2st;
    uint16_t CountOppC3st;
    uint16_t CountOppC4st;
    uint16_t NumBinA;
    uint16_t NumBinB;
    uint16_t NumBinC;
    uint16_t NumChanA;
    uint16_t NumChanB;
    uint16_t NumChanC;
    } rgset_swich;
    
 typedef struct rgset_circleset {
 char Name[40];
 float Radius;
 float Distance; 
 float Angle;
 }rgset_circleset ;   

typedef struct rgset_tableset {
    char Name[40];
    float Z0;
    float Z10;
    float Z20;
    float Z30;
    float Z40;
    float Z50;
    float Z60;
    float Z70;
    float Z80;
    float Z90;
    float Z100;
    float Z110;
    float Z120;
    float Z130;
    float Z140;
    float Z150;
    float Z160;
    float Z170;
    float Z180;
    float Z190;
    float Z200;
    float Z210;
    float Z220;
    float Z230;
    float Z240;
    float Z250;
    float Z260;
    float Z270;
    float Z280;
    float Z290;
    float Z300;
    float Z310;
    float Z320;
    float Z330;
    float Z340;
    float Z350;
} rgset_tableset;

typedef struct rgset_transmischanel {
    char Name[32];			 										// 0-31
    uint16_t BaseAddress; 										// 32-33
    uint16_t TypeChanel;											//34-35
    uint16_t TransmissionSpeed;							//36-37
	char Void [4];														 //38-41
    uint16_t Flags; 													 //42-43
    uint16_t  ObjectIdentifier;							   		 //44-45
    uint16_t  RecipientIdentifier; 							 //46-47
    uint16_t  CallCount;											 //48-49
    uint16_t ConnectionTimeAfterPickingupTube; //50-51	
    uint16_t ConnectingTimeAfterDialing; 			//52-53
    uint16_t CountConnectionAttempt; 				//54-55
    char NumberPhone [79];  									//56-134
    char Void1 [1]; 													//135
    char InitializationString [63];		 						//136-198
    char Void2[9];														//199-207
    
    } rgset_transmischanel;
    
typedef struct rgset_autotrans {
    char Name[32];
    uint16_t Regnum;
    uint16_t NumchA;
    uint16_t NumchB;
    uint16_t NumchC;
    float CurSettings;
    } rgset_autotrans;

typedef struct rgset_relationslinereg {
    char Void[5];
    } rgset_relationslinereg;

typedef struct rgset_speciflineprotection {
    char FullName[40];
    char Name[16];
    uint16_t LineNumb;
    uint16_t RegNumb;
    uint16_t ProtectType;
    char Void1[6];
    uint16_t PickupBin;
    uint16_t TripBin;
    uint32_t TripTime;
    char Void2[28];
    uint16_t AddBinNumb1;
    char Void3[2];
    uint16_t AddBinNumb2;
    char Void4[2];
    uint16_t AddBinNumb3;
    char Void5[2];
    float AnalogSet1;
    float AnalogSet2;
    float AnalogSet3;
    float AnalogSet4;
    float AnalogSet5;
    float AnalogSet6;
    float AnalogSet7;
    float AnalogSet8;
    char void6[8];
    } rgset_speciflineprotection;

typedef struct rgset_specifstageprotection {
    //uint16_t NumSpesif;
    //uint16_t NumProtectStage;
    //char Void[4];
    //uint16_t NumBinary;
    //float TimeOperation;
    //uint32_t SensitivUp;
    //uint32_t SensitivDown;
    //char Void2[32];
    //float threshold;
    //char Void3[6];
    char Void [94];
    } rgset_specifstageprotection;

typedef struct rgset_additspecifchanel {
    char Void[40];
    } rgset_additspecifchanel;

typedef struct rgset_protectionzonesectionallylinear {
    char Void[40];
    uint16_t count;
    char Void2[2];
    float X1;
    float X2;
    float X3;
    float X4;
    float X5;
    float X6;
    float X7;
    float X8;
    float X9;
    float X10;
    float X11;
    float X12;
    float X13;
    float X14;
    float X15;
    float X16;
    float X17;
    float X18;
    float X19;
    float X20;
    float Y1;
    float Y2;
    float Y3;
    float Y4;
    float Y5;
    float Y6;
    float Y7;
    float Y8;
    float Y9;
    float Y10;
    float Y11;
    float Y12;
    float Y13;
    float Y14;
    float Y15;
    float Y16;
    float Y17;
    float Y18;
    float Y19;
    float Y20;
    } rgset_protectionzonesectionallylinear;

#pragma pack(pop)

typedef struct rgset{
	int file_descr;	// Файловый дискриптор [Всегда первый в структуре]
	long int size;	// Размер файла [Всегда второй в структуре]
	void* file_pointer;
	rgset_title* title; // Указатель на заголовок [Всегда третий в структуре]
	rgset_chanel* chanel;
	rgset_line* line;
	rgset_reg* reg;
	rgset_bin* bin;
	rgset_mark* mark;
	rgset_linesect* linesect;
	rgset_swich* swich;
	rgset_circleset* circleset;
	rgset_tableset* tableset;
	rgset_transmischanel*  transmischanel;
	rgset_autotrans*  autotrans;
	rgset_relationslinereg* relationslinereg; 
	rgset_speciflineprotection*  speciflineprotection;
	rgset_specifstageprotection* specifstageprotection;
	rgset_additspecifchanel* additspecifchanel;
	rgset_protectionzonesectionallylinear* protectionzonesectionallylinear;
	
} rgset;

typedef struct binNum {
	unsigned int MG;
	unsigned int Matrix;
	unsigned int Group;
	unsigned int Razr;
} binNum;

int prnRgsetTitle(rgset* p); // Прототип функции вывода заголовка rgset.dat
int prnRgsetChanel(rgset* p); // Прототип функции вывода описания аналоговых каналов rgset.dat
int prnRgsetLines(rgset* p);  // Прототип функции вывода описания аналоговых каналов rgset.dat
int prnRgsetReg(rgset* p); // Прототип функции вывода описания регистраторов rgset.dat
int prnRgsetBin(rgset* p); // Прототип функции вывода перечня дискретных сигналов rgset.dat
void init_bin_arr(uint16_t* source, rgset_bin* dest, int count); // Прототип функции заполнения структур типа rgset_bin из данных rgset.dat
int prnRgsetMark(rgset* p); // Прототип функции вывода типов дискретных сигналов из данных rgset.dat
int prnRgsetLineSect(rgset* p); // Прототип функции вывода участков линий из данных rgset.dat
int prnRgsetSwich(rgset* p); // Прототип вывода выключателей из данных rgset.dat
int prnRgsetAll(rgset* p); // Прототип функции вывода всех полей rgset

rgset* rgsetInit(char* filename);
/* Завантажує файл filename в пам'ять. Створює структуру типу rgset та ініціалізує її поля.
   При успіху повертає вказівник на структуру rgset, при невдачі поветає Null.
   Кожному виклику rgsetInit() повинен відповідати rgsetClose(), який віконує зворотні дії */

void rgsetClose(rgset* p);
/* Вивантажує файл rgset.dat з пам'яті. Вивільняє пам'ять, зайняту структурою rgset */

int rgsetSplit(rgset* p);/* НЕ РЕАЛІЗОВАНО */
/* Розділює відображення файлу rgset.dat на окремі масиви для можливості подальших змін.
   При успішу поветрає 0, при невдачі -1*/

int rgsetUnit(rgset* p);/* НЕ РЕАЛІЗОВАНО */
/* Об'єднує раніше розділене відображення файлу rgset.dat.
   Ця функція виконує зворотні дії до rgsetSplit().
   При успіху повертає 0, при невдачі -1 */

int rgsetAddChanel(rgset* pointer, int chNumb);/* НЕ РЕАЛІЗОВАНО */
/* Додає до розділеного відображення файлу rgset.dat новий канал з номером chNumb.
   При chNumb = 0 доданий елемент масиву буде самим першим (лівим).
   При chNumb = pointer->title.CountChanel доданий елемент масиву буде останнім (правим).
   Оновлює поля структури pointer->chanel, pointer->title.CountChanel 
   При успіху повертає 0, при невдачі -1 */

int rgsetDelChanel(rgset* pointer, int chNumb);/* НЕ РЕАЛІЗОВАНО */
/* Видалає у розділеному відображення файлу rgset.dat канал з номером chNumb.
   Оновлює поля структури pointer->chanel, pointer->title.CountChanel 
   При успіху повертає 0, при невдачі -1 */

int rgsetAddReg(rgset* pointer, int regNumb);/* НЕ РЕАЛІЗОВАНО */
/* Додає до розділеного відображення файлу rgset.dat новий реєстратор з номером regNumb.
   При regNumb = 0 доданий елемент масиву буде самим першим (лівим).
   При regNumb = pointer->title.CountReg доданий елемент масиву буде останнім (правим).
   Оновлює поля структури pointer->reg, pointer->title.CounReg 
   При успіху повертає 0, при невдачі -1 */

int rgsetDelReg(rgset* pointer, int regNumb);/* НЕ РЕАЛІЗОВАНО */
/* Видалає у розділеному відображення файлу rgset.datреєстратор з номером regNumb.
   Оновлює поля структури pointer->reg, pointer->title.CountReg 
   При успіху повертає 0, при невдачі -1 */


rgset* rgsetNew(); /* НЕ РЕАЛІЗОВАНО */
/* Створює структуру типу rgset, виділяє пам'ять під образ файлу rgset.dat (тільки під title).
   При успіху повертає вказівник на структуру rgset, при невдачі поветає Null.
   Для додавання реєстраторів, каналів, дискретних сигналів тощо використовувати функції rgsetAdd...().
   Кожному виклику rgsetNew() повинен відповідати rgsetClose(), який віконує зворотні дії */

int rgsetSave(rgset* pointer, char* filename); /* НЕ РЕАЛІЗОВАНО */
/* Зберігає образ файлу rgset до файлу з ім'ям filename
   При успіху повертає 0, при невдачі -1 */

float mainratio(rgset* rp, int chnumber); // Прототип функции определения обобщенного коэф. канала по его номеру в rgset.dat
int findperiod(rgset* rp); // Функция для определения количества отсчетов за период 20 мс (обратно проп. частоте дискретизации)
int binNumb(int numb, binNum* out); // Функция для перевода норемера дискретного сигнала в матрица-группа-разряд

#endif
