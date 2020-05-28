/*
    Контанты проекта
*/

#ifndef CONST_H
#define CONST_H

// константа очистки консоли
#ifdef __linux__
    #define CLEAR "clear"
#else
    #define CLEAR "cls"
#endif

// ------------------------- Прочие конcтанты -------------------------
#define cat_num 5 // Количество жанров музыки
#define MAXLEN 25 // Максимальная длина строки (+ нуль-терминатор)
#define MAXSTR 128 // Максимальная строка файла

extern const char * const categories[cat_num];

#endif