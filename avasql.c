/* avasql.c */
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <sqlite3.h>
#include <wchar.h>
#include "calculation.h"
#include "rgset.h"
#include "list.h"
#include "ava.h"
#include "common.h"
#include "listdir.h"
#define TEXT_LENGHT 200
static char* sql_file;

///////////////////////////////////////////////////////////////////////
////////  Функция добавления элементов objects в базу данных  /////////
///////////////////////////////////////////////////////////////////////
int sql_add_object(sqlite3* db, const char* object_name) {
	sqlite3_stmt* stmt;
	int id = 0;
	int temp = 0;
	
	//// Проверка существование элемента objects //////
	if(sqlite3_prepare_v2(db, "SELECT id FROM objects WHERE name = ?", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, object_name, -1, 0);
		temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step");
			return -1;
		};
		if(temp == SQLITE_ROW) {
			id = sqlite3_column_int(stmt,0);
			sqlite3_finalize(stmt);
			return id;
		};
		sqlite3_finalize(stmt);
	}
	else {
		perror("Ошибка создания sqlite3_prepare_v2 для запроса SELECT objects");
		return -1;
	};
	//////////////////////////////////////////////

	///// Вставка нового элемента objects /////////
	if(sqlite3_prepare_v2(db, "INSERT INTO objects VALUES (NULL, ?)", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, object_name, -1, 0);
		temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step");
			return -1;
		};
		sqlite3_finalize(stmt);
		id = sql_add_object(db, object_name);
	}
	else {
		perror("Ошибка создания sqlite3_prepare для запроса INSERT objects");
		return -1;
	};
	///////////////////////////////////////////////
	return id;
};
///////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/////////// Функция добавления элементов reg в базу данных ///////////////
//////////////////////////////////////////////////////////////////////////
int sql_add_reg(sqlite3* db, const char* name, int id_object) {
	sqlite3_stmt* stmt;
	int id = 0;
	int temp = 0;
	
	//// Проверка существование элемента reg //////
	if(sqlite3_prepare_v2(db, "SELECT id FROM reg WHERE name = ? AND id_object = ?", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, name, -1, 0);
		sqlite3_bind_int(stmt, 2, id_object);
		temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step");
			return -1;
		};
		if(temp == SQLITE_ROW) {
			id = sqlite3_column_int(stmt,0);
			sqlite3_finalize(stmt);
			return id;
		};
		sqlite3_finalize(stmt);
	}
	else {
		perror("Ошибка создания sqlite3_prepare_v2 для запроса SELECT reg");
		return -1;
	};
	//////////////////////////////////////////////

	///// Вставка нового элемента reg /////////
	if(sqlite3_prepare_v2(db, "INSERT INTO reg VALUES (NULL, ?, ?)", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, name, -1, 0);
		sqlite3_bind_int(stmt, 2, id_object);
		temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step");
			return -1;
		};
		sqlite3_finalize(stmt);
		id = sql_add_reg(db, name, id_object);
	}
	else {
		perror("Ошибка создания sqlite3_prepare для запроса INSERT reg");
		return -1;
	};
	return id;
	///////////////////////////////////////////////
};
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///////    Функция добавления в базу нового канала    //////////////////
////////////////////////////////////////////////////////////////////////
int sql_add_channel(sqlite3* db, const char* name, const char* units, int id_reg) {
	sqlite3_stmt* stmt;
	int id = 0;
	int temp = 0;

	//// Проверка существование элемента channel //////
	if(sqlite3_prepare_v2(db, "SELECT id FROM channels WHERE name = ? AND id_reg = ?", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, name, -1, 0);
		sqlite3_bind_int(stmt, 2, id_reg);
		temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step");
			return -1;
		};
		if(temp == SQLITE_ROW) {
			id = sqlite3_column_int(stmt,0);
			sqlite3_finalize(stmt);
			return id;
		};
		sqlite3_finalize(stmt);
	} 
	else {
		perror("Ошибка создания sqlite3_prepare_v2 для запроса SELECT reg");
		return -1;
	};
	//////////////////////////////////////////////

	///// Вставка нового элемента channel /////////
	if(sqlite3_prepare_v2(db, "INSERT INTO channels VALUES (NULL, ?, ?, ?)", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, name, -1, 0);
		sqlite3_bind_text(stmt, 2, units, -1, 0);
		sqlite3_bind_int(stmt, 3, id_reg);
		temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step");
			return -1;
		};
		sqlite3_finalize(stmt);
		id = sql_add_channel(db, name, units, id_reg);
	}
	else {
		perror("Ошибка создания sqlite3_prepare для запроса INSERT channels");
		return -1;
	};
	return id;
	///////////////////////////////////////////////
};
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///////    Функция добавления в базу нового дискр. сигнала    //////////
////////////////////////////////////////////////////////////////////////
int sql_add_binary(sqlite3* db, const char* name, int id_reg) {
	sqlite3_stmt* stmt;
	int id = 0;
	int temp = 0;
	
	//// Проверка существование элемента binarys  //////
	if(sqlite3_prepare_v2(db, "SELECT id FROM binarys WHERE name = ? AND id_reg = ?", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, name, -1, 0);
		sqlite3_bind_int(stmt, 2, id_reg);
		temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step binarys");
			return -1;
		};
		if(temp == SQLITE_ROW) {
			id = sqlite3_column_int(stmt,0);
			sqlite3_finalize(stmt);
			return id;
		};
		sqlite3_finalize(stmt);
	} 
	else {
		perror("Ошибка создания sqlite3_prepare_v2 для запроса SELECT binarys");
		return -1;
	};
	//////////////////////////////////////////////

	///// Вставка нового элемента binarys /////////
	if(sqlite3_prepare_v2(db, "INSERT INTO binarys VALUES (NULL, ?, ?)", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, name, -1, 0);
		sqlite3_bind_int(stmt, 2, id_reg);
		temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step binarys");
			return -1;
		};
		sqlite3_finalize(stmt);
		id = sql_add_binary(db, name, id_reg);
	}
	else {
		perror("Ошибка создания sqlite3_prepare для запроса INSERT binarys");
		return -1;
	};
	return id;
	///////////////////////////////////////////////
};
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//////////    Функция добавления в базу нового события    //////////////
////////////////////////////////////////////////////////////////////////
int sql_add_event(sqlite3* db, const char* filename, const char* time, int id_reg) {
	sqlite3_stmt* stmt;
	int id = 0;
	int temp = 0;
	
	//// Проверка существование элемента event //////
	if(sqlite3_prepare_v2(db, "SELECT id FROM events WHERE time = ? AND id_reg = ?", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, time, -1, 0);
		sqlite3_bind_int(stmt, 2, id_reg);
		temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step event");
			return -1;
		};
		if(temp == SQLITE_ROW) {
			id = sqlite3_column_int(stmt,0);
			sqlite3_finalize(stmt);
			return id * -1;
		};
		sqlite3_finalize(stmt);
	} 
	else {
		perror("Ошибка создания sqlite3_prepare_v2 для запроса SELECT event");
		return -1;
	};
	//////////////////////////////////////////////

	///// Вставка нового элемента events /////////
	if(sqlite3_prepare_v2(db, "INSERT INTO events VALUES (NULL, ?, ?, ?)", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, filename, -1, 0);
		sqlite3_bind_text(stmt, 2, time, -1,0);
		sqlite3_bind_int(stmt, 3, id_reg);
		temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step binarys");
			return -1;
		};
		sqlite3_finalize(stmt);
		id = -1 * sql_add_event(db, filename, time, id_reg);
	}
	else {
		perror("Ошибка создания sqlite3_prepare для запроса INSERT events");
		return -1;
	};
	return id;
	///////////////////////////////////////////////
};
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//////////    Функция добавления в базу нового описания   //////////////
////////////////////////////////////////////////////////////////////////
int sql_add_info(sqlite3*db, int id_event, const char* data) {
	sqlite3_stmt* stmt;
	if(sqlite3_prepare_v2(db, "INSERT INTO info VALUES (NULL, ?, ?)", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, id_event);
		sqlite3_bind_text(stmt, 2, data, -1,0);
		int temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step info");
		};
		sqlite3_finalize(stmt);
		return 0;
	}
	else {
		perror("Ошибка создания sqlite3_prepare для запроса INSERT events");
		return -1;
	};
};
///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//////////    Функция добавления в базу новых величин     //////////////
////////////////////////////////////////////////////////////////////////
int sql_add_val(sqlite3* db, float before, float min, float max, float z_min, float z_max, int id_event, int id_channel) {
	sqlite3_stmt* stmt;
	
	///// Вставка нового элемента val /////////
	if(sqlite3_prepare_v2(db, "INSERT INTO val VALUES (NULL, ?, ?, ?, ?, ?, ?, ?)", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_double(stmt, 1, (double)before);
		sqlite3_bind_double(stmt, 2, (double)max);
		sqlite3_bind_double(stmt, 3, (double)min);
		sqlite3_bind_double(stmt, 4, (double)z_max);
		sqlite3_bind_double(stmt, 5, (double)z_min);
		sqlite3_bind_int(stmt, 6, id_event);
		sqlite3_bind_int(stmt, 7, id_channel);
		int temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step val");
			return -1;
		};
		sqlite3_finalize(stmt);
	}
	else {
		perror("Ошибка создания sqlite3_prepare для запроса INSERT val");
		return -1;
	};
	return 0;
	///////////////////////////////////////////////
};
///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
//////    Функция добавления в базу новой двоичной сработки    /////////
////////////////////////////////////////////////////////////////////////
int sql_add_operate(sqlite3* db, int time, int status, int id_binary, int id_event) {
	sqlite3_stmt* stmt;

	///// Вставка нового элемента operates /////////
	if(sqlite3_prepare_v2(db, "INSERT INTO operates VALUES (NULL, ?, ?, ?, ?)", -1, &stmt, 0) == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, time);
		sqlite3_bind_int(stmt, 2, status);
		sqlite3_bind_int(stmt, 3, id_binary);
		sqlite3_bind_int(stmt, 4, id_event);
		int temp = sqlite3_step(stmt);
		if (temp != SQLITE_ROW && temp != SQLITE_DONE)  {
			perror("Ошибка sqlite3_step operates");
			return -1;
		};
		sqlite3_finalize(stmt);
	}
	else {
		perror("Ошибка создания sqlite3_prepare для запроса INSERT operates");
		return -1;
	};
	return 0;
	///////////////////////////////////////////////
};
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//////// Функция открытия базы данных и заполнение таблиц  ///////////////////
//////////////////////////////////////////////////////////////////////////////
void avasql(rgset* rp, ava* ap, const char* filename) {
	sqlite3 *db = 0;
	sqlite3_stmt* stmt;
	extremum ext;
	char char_msec[7];
	printf("%s\n", filename);
	int period = findperiod(rp);// Определяем период сигнала (20 или 40 отсчетов)
	if(sqlite3_open(sql_file, &db)) perror ("Ошибка открытия базы");
	sqlite3_prepare_v2(db, "PRAGMA synchronous=OFF", -1, &stmt, 0);
	sqlite3_finalize(stmt);

	// Добавляем запись в таблицу objects
	int id_object = sql_add_object(db, utf(rp->title->NameStation));

	// Добавляем запись в тблицу reg
	int id_reg = sql_add_reg(db,utf((rp->reg + ap->main_title->RegNum - 1)->Name), id_object);
	
	// Добавляем запись в таблицу events
	sprintf(char_msec,".%-3.3u",ap->main_title->MilsecFault);
	int id_event = sql_add_event(db, filename, strcat(str_local_time((DayTime*)&(ap->main_title->DayFault)),char_msec), id_reg);
	
	if(id_event > 0) { // Если присутствует добавление нового элемента event а не обнаружение существующего элемента event
		if(*ap->title->UserInfo != 0) sql_add_info(db, id_event, cp1251_to_utf(ap->title->UserInfo));		
		
		// Добавляем записи в таблицы chanel и val (только если до этого была создана новая запиь в таблице events)
		for(int i = 0; i < ap->main_title->CountChanel; i++) { // Для каждого канала в файле аварии
			int j = findChNumb(rp, ap, i);// номер канала в файле rgset.dat
			if (j != -1) {
				int	id_channel = sql_add_channel(db, utf((rp->chanel+j)->Name), utf2((rp->chanel+j)->SymbolPrimCircuit), id_reg);
				find_extremum(ap->chanel+i*ap->main_title->CountTacts, ap->main_title->CountTacts, period, &ext);
				if(j < rp->title->CountChanel) {
					float k = fabsf(mainratio(rp, findChNumb(rp, ap, i)));// Определяем обобщенный коэфициент
					sql_add_val(db, ext.before*k, ext.min*k, ext.max*k, ext.z_min*k/0.7071, ext.z_max*k/0.7071, id_event, id_channel);
				};
			};
		};
		
		// Добавляем запись в таблицы binarys и operates (только если до этого была создана новая запись в таблице events)
		if (ava_bin_init(ap) == 0) { // Инициализация двоичных данных
			list* ls = ap->list_bin_i;
			while(ls->prev) ls = ls->prev;
			int i,t;
			if(findperiod(rp) == 40) t = 2; else t = 1;
			while(ls) {
				ava_bin_i* d = (ava_bin_i*)ls->data;
				binNum tmp;
				i = 0;
				binNumb((rp->bin + i)->Numb, &tmp);
				while((d->Group != tmp.MG || ap->main_title->RegNum != (rp->bin + i)->Reg || d->Razr != tmp.Razr) && (i < rp->title->CountBinSignal))
				{
					i++;
					binNumb((rp->bin + i)->Numb, &tmp);
				};
				int id_binary = sql_add_binary(db, utf((rp->bin + i)->Name), id_reg);
				sql_add_operate(db, (int)(d->Tact/t), d->Status, id_binary, id_event);
				ls = ls->next;
			};
			ava_bin_close(ap);
		};
	};
sqlite3_close(db);
};
//////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	if (argc != 3) printf ("Неправильное число аргументов. Используй: avasql [Файл базы данных][Каталог]\n");
	else { 
		sql_file = argv[1];
		// Проверка существования файла базы данных
		// Если файла базы данных не существует - создаем его
		if (filesize(sql_file) == -1) {
			char str_cmd[TEXT_LENGHT];
			bzero((void*)str_cmd, TEXT_LENGHT);
			strcat(str_cmd, "mkdb ");
			strcat(str_cmd, sql_file);
			system(str_cmd);
		};

		listdir(argv[2], avasql);
	};
return 0;
}
