/* array.h */

void* array_new(unsigned int count, unsigned int size);
/* Створює динамічний масив з числом елементів count, розміром одного елементу size.
 * Повертає вказівник на перший елемент масиву або NULL, якщо пам'ять для масиву не може бути виділена.
Приклад:
int* my_array = array_new(100, sizeof(int); // Створює динамічний масив для зберігання даних типу int на 100 комірок
my_array[0] = 12; // Встановлюємо значення першої комірки, рівне 12 */

void array_free(void* array);
/* Удаляет динамический массив, очищая занимаемую им память.
Пример:
array_free((void*)my_array); */

unsigned int array_count(void* array);
/* Возвращват количество элементов в массиве
Пример:
unsigned int n = array_count(my_array);
for(int i = 0; i < n; i++) {
	my_array[i] = ???; } */

void* array_add(void* array, unsigned int number, unsigned int count);
/* Добавляет к массиву array новые элементы, начиная с элемента с номером number, количеством count.
   Возвращает указатель на первый элемент массива или NULL, если память для расширения масива не может быть выделена.

Пример использования
int* my_array = array_new(100, sizeof(int)); // Создаем динамический масив хранения данных типа int на 100 ячеек.
...
my_array = array_add((void*)my_array, 50, 10); // Добавляет к массиву, начиная с 50-го элемента 10 новых элементов.
if (my_array = -1) return -1;
.....
*/

void* array_cut(void* array, unsigned int number, unsigned int count);
/* Удаляет из динамического массива array, начиная с элемента с номером number, count элементов.
 * При успехе возвращает указатель на первый элемент массива или NULL, если память для нового масива не может быть выделена   */
