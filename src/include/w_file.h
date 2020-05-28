#ifndef W_FILE_H
#define W_FILE_H

char **simple_split(char *str, int length, char sep);   // Разбиение строк над подстроки по сепартору
int get_database(Head *HEAD, int MODE);                 // Чтение из файла
int cycle_get_database(Head *HEAD, int MODE);                 // Чтение из файла
int write_to_file(Head *HEAD, int MODE);                // Запись в файл
Node *convert_to_node(char **s2);                       // Конвератация массива строк в элемент списка

#endif