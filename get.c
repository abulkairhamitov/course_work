#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "./include/get.h"

char *get_string() // Возвращает указатель на введенную строку
{
    char c;                                            // Очередной символ
    char *string = (char*)malloc(MAXLEN*sizeof(char)); // Указатель на строку
    int i = 0;                                         // Индекс очередного символа
    if (string != NULL)
    {
        do
        {
            while ((c = getchar()) != '\n' && i < MAXLEN-1) string[i++] = c;
            string[i] = '\0';
            if (i < 1) printf("Error. You entered empty string. Please, try again.\n");
        } while (i < 1);
        if (i >= MAXLEN - 1)
            while ((c = getchar()) != '\n' && c != EOF);
    }
    return string;
}

int get_int()  // Ввод числа
{
    char line[MAXLEN];   // Буффер
    char curChar = ' ';  // Последний символ
    int temp, result;
    do {
        line[MAXLEN - 1] = '\n';
        fgets(line, MAXLEN - 1, stdin);
        temp = sscanf(line, "%d%c", &result, &curChar);
        temp = !temp || temp < 0 || (curChar != '\n' && curChar != ' ');
        if (temp)
            printf("Error reading number. Please, try again.\n");
    } while (temp); // Не число на самом деле
    if (line[MAXLEN - 1] != '\n') //clear all iput
        while ((curChar = getchar()) != '\n' && curChar != EOF);
    return result;
}

float get_float() // Ввод вещественного числа
{
    char line[MAXLEN];   // Буффер
    char curChar = ' ';
    int temp;
    float result;
    do {
        line[MAXLEN - 1] = '\n';
        fgets(line, MAXLEN - 1, stdin);
        temp = sscanf(line, "%f%c", &result, &curChar);
        temp = !temp || temp < 0 || (curChar != '\n' && curChar != ' ');
        if (temp)
            printf("Error reading number. Please, try again.\n");
    } while (temp); // Не число на самом деле
    if (line[MAXLEN - 1] != '\n') // Избавление от муссора
        while ((curChar = getchar()) != '\n' && curChar != EOF);
    return result;
}