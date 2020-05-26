#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "./include/dbl_list.h"
#include "./include/get.h"

void clear_str_array(char **str, int n)
{
    int i;
    for(i = 0;i < n; i++)
    {
        free(str[i]);
        str[i] = NULL;
    }
    free(str);
    str = NULL;
}

// Конвертация в узел
Node *convert_to_node(char **s2)
{
    Node *p = NULL;
    int len1, len2; // Длина строки категории и описания соответственно
    p = (Node*)malloc(sizeof(Node));
    p->next = NULL;
    p->prev = NULL;
    char str1[] = "Income";
    len1 = strlen(s2[1]);
    len2 = strlen(s2[2]);

    (p->info).category=(char*)malloc((len1+1)*sizeof(char));
    (p->info).description=(char*)malloc((len2+1)*sizeof(char));

    if(((p->info).category!=NULL)&&((p->info).description!=NULL))
    {
        if(strcmp(str1, s2[0]))
            (p->info).expenses_income = 2;
        else
            (p->info).expenses_income = 1;
        strcpy((p->info).category, s2[1]);
        strcpy((p->info).description, s2[2]);
        (p->info).money = atoi(s2[3]);
    }
    else
    {
        puts("Out if memory! Program terminated");
    }
    return p;
}

// Разделение строки на подстроки
char **simple_split(char *str, int length, char sep)
{
    char **str_array = NULL;
    int i, j,
        k,
        m;      // Количество сепораторов в строке
    int key,    // Проверка на выделение памяти
        count;  // Количество строк, которым была выделена память
    for(j = 0, m = 0; j < length; j++)
        if(str[j] == sep) m++;

    key = 0;
    str_array = (char**)malloc((m+1)*sizeof(char*));
    if(str_array != NULL)
    {
        for(i = 0, count = 0; i <= m; i++, count++)
        {
            str_array[i] = (char*)malloc(length*sizeof(char));
            if(str_array[i] != NULL) key = 1;
            else
            {
                key = 0;
                i = m;
            }
        }
        if(key)
        {
            k = 0;
            m = 0;
            for(j = 0; j < length; j++)
            {
                if(str[j] != sep) str_array[m][j-k] = str[j];
                else
                {
                    str_array[m][j-k]='\0';
                    k = j+1;
                    m++;
                }
            }
        } else clear_str_array(str_array,count);
    }
    return str_array;
}

// Чтение со строки
int get_database(Head *HEAD, int MODE)
{
    Node *p;
    int slen,       // Длина очередной строки
        i,          // Количество строк в файле
        flag = 1,   // Проверка на выделение памяти
        valid_file; // -1 - Чтение не вышло. 1 - Чтение прошло успешно. 2 - Файл пустой. 0 - Не удалось открыть файл
    char sep;           // Сепоратор
    char s1[MAXSTR];    // Очередная строка в файле
    char **s2 = NULL;   // Массив из полей очередной структуры

    FILE *df;
    if (MODE) // Чтение из нового файла
    {
        char *path;
        puts("Type path to file or his name: ");
        path = get_string();
        df = fopen(path, "r");
    }
    else df = fopen("database.txt", "r"); // Чтение из файла по умолчанию
    if(df != NULL)
    {
        sep=';';    // Сепоратор
        i = 0;
        while(fgets(s1, MAXSTR, df) != NULL && flag)
        {
            slen = strlen(s1);
            if(s1[slen-1] == '\n')
                s1[slen-1] = '\0';
            else
                s1[slen] = '\0';
            slen = strlen(s1);
            s2 = simple_split(s1, slen, sep);
            if(s2 != NULL)
            {
                p = convert_to_node(s2);
                add_last(HEAD, p);
                i++;

                clear_str_array(s2, 4);
            }
            else
            {
                flag = 0;
                valid_file = -1;
                puts("Row data not available!");
            }
        }
        if (fclose(df)!=EOF)
            if (i == 0)
                valid_file = 2;
            else
                valid_file = 1;
    }
    else
        valid_file = 0;
    return valid_file;
}

// Запись в файл
int write_to_file(Head *HEAD, int MODE)
{
	FILE *file;         // Указатель на файл 
	int valid_file = 1; // -1 - Файл не открылся. 0 - Файла закрылся с ошибкой. 1 - все ок.
	if (MODE) // Записать в новый файл
    {
        char *path;
        puts("Type path to file or his name: ");
        path = get_string();
        file = fopen(path, "w");
    }
    else file = fopen("output.txt", "w"); // Записать в файл по умолчанию

	if (file == NULL)
	{
		printf("Error opening file!\n");
		valid_file = -1;
	}
	else
    {
        int i;
        Node *p=NULL;
        p = HEAD->first;
        for (i = 0; i < HEAD->count; i++)
        {
            if((p->info).expenses_income == 1)
                fprintf(file, "Income;");
            else
                fprintf(file, "Expenses;");
            fprintf(file, "%s;", (p->info).category);
            fprintf(file, "%s;", (p->info).description);
            fprintf(file, "%.2f", (p->info).money);
            if (i < HEAD->count-1)
                fprintf(file, "\n");
            p = p->next;
        }
        if (fclose(file) == EOF)
            valid_file = 0;
	}
	return valid_file;
}