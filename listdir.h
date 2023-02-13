/* listdir */

#ifndef LISTDIR
#define LISTDIR
void mk_full_path(const char* path, struct dirent* entry, char* fullpatf); // функция определения полного пути к файлу аварии

int listdir(const char* path, void (*processor)(rgset* rp, ava* ap, const char* file_name)); // Рекурсивная функция поиска файлов аварий в каталоге path. При обнаружении управление передается функции processor
void (*processor)(rgset* rp, ava* ap, const char* file_name); 

#endif
