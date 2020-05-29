#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "./include/dbl_list.h"
#include "./include/get.h"
#include "./include/const.h"
#include "./include/common.h"


Head *make_head(int *bl) // Создание головы
{
    Head *ph=NULL;
    ph=(Head*)malloc(sizeof(Head));
    if(ph!=NULL)
    {
        ph->count=0;
        ph->first = NULL;
        ph->last = NULL;
    } else *bl = 0;
    return ph;
}

void print_managers(Head *my_head)
{
    Node *p;
    int i;
    printf("|Num|Expenses/Income| category|          Description|       Money|\n");
    printf("|___|_______________|_________|_____________________|____________|\n");
    p = my_head->first;
    for (i = 0; i < my_head->count; i++)
    {
        if( (p->info).expenses_income == 1)
        {
            printf("|%3d|         Income|%9.22s|%21.22s|%12.0f|\n", i+1, (p->info).category, (p->info).description, (p->info).money);
            printf("|___|_______________|_________|_____________________|____________|\n");
        } else
        {
            printf("|%3d|        Expense|%9.22s|%21.22s|%12.0f|\n", i+1, (p->info).category, (p->info).description, (p->info).money);
            printf("|___|_______________|_________|_____________________|____________|\n");
        }
        p = p->next;
    }
}

char *get_category() // Выбор категории. Возвращает число (пункт в списка категории)
{
    int q,      // Выбор пункта из списка категорий
        i;      // Индекс категории
    char *str;  // Очередная категория
    for (i = 0; i < cat_num; i++)
        printf("%d. %s\n", i+1, categories[i]);
    //Очистка потока ввода
    do
    {
        q = get_int();
        if (q <= 0 || q > (int)sizeof(categories)/sizeof(char*))
            printf("You entered an invalid value, try again: \n");
    } while (q <= 0 || q > (int)sizeof(categories)/sizeof(char*));
    printf("Your choice %s\n", categories[q-1]);
    str = (char*)malloc(strlen(categories[q-1])*sizeof(char));
    strcpy(str, categories[q-1]);
    return str;
}

void fill_node(manager *list, int *bl) // Ввод очередной структуры
{
    do
    {
        printf("Choose this income or expense. Income - 1, Expense - 2\n");
        list->expenses_income = get_int();
        if(list->expenses_income != 1 && list->expenses_income != 2)
            puts("You entered an invalid number");
    } while (list->expenses_income <= 0 || list->expenses_income > 2);
    printf("Select the desired category: \n");
    list->category = get_category();
    printf("Enter a description: \n");
    list->description = get_string(bl);
    do
    {
        printf("Enter the amount of money: \n");
        list->money = get_float();
        if(list->money <= 0)
            puts("The number must be positive!");
    } while (list->money <= 0);
}

Node *create_node(int *bl) // Создание узла
{
    Node *new_node=NULL;
    new_node = (Node*)malloc(sizeof(Node));
    if(new_node)
    {
        fill_node(&(new_node->info), bl);
    } else *bl = 0;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void add_first(Head *my_head, Node *new_node) // Добавление элемента в начало
{
    if(my_head&&new_node)
    {
        if (!(my_head->count))
            my_head->last = new_node;
        else
        {
            (my_head->first)->prev = new_node;
            new_node->next = my_head->first;
        }
        my_head->first = new_node;
        my_head->count++;
    }
}

void add_last(Head *my_head, Node *new_node) // Добавление элемента в конец
{
    if(my_head&&new_node)
    {
        if (!(my_head->count))
            my_head->first = new_node;
        else
        {
            (my_head->last)->next = new_node;
            new_node->prev = my_head->last;
        }
        new_node->next = NULL;
        my_head->last = new_node;
        my_head->count++;
    }
}

void insert(Head *my_head, Node *new_node) // Добавление элемента в n-ую позицию
{
    int i,   // Переменная в цикле
        pos; // Выбор позиции пользователем
    Node *p;

    do
    {
        printf("What is the position? [1 to %d]\n", my_head->count+1);
        pos = get_int();
    } while (pos < 1 || pos > my_head->count+1);

    if(my_head&&new_node)
    {
        if (!(my_head->count)) // Если в списке ноль элементов
        {
            my_head->first = new_node;
            my_head->last = new_node;
            my_head->count++;
        }
        else if (pos > 0 && pos < my_head->count+2)
        {
            if (pos == 1)
                add_first(my_head, new_node);
            else if (pos == my_head->count + 1)
                add_last(my_head, new_node);
            else {
                p = my_head->first;
                for (i = 1; i < pos - 1; i++) // Добираемся до позиции pos-1
                    p = p->next;
                new_node->prev = p;
                new_node->next = p->next;
                (p->next)->prev = new_node;
                p->next = new_node;
                my_head->count++;
            }
        }
    }
}

void add_item(Head *HEAD, int *bl) // Добавление элемента в список
{
    Node *p=NULL;
    int c;
    do
    {
        printf("1 - Add node to start\n2 - Add node to end\n3 - Insert node\nPress 0 to stop\n");
        c = get_int();
        if (c != 0) p = create_node(bl);
        switch (c)
        {
            case 1:
                add_first(HEAD, p);
                break;
            case 2:
                add_last(HEAD, p);
                break;
            case 3:
                insert(HEAD, p);
                break;
            case 0:
                break;
            default:
                puts("Error, try again.\n");
        }
    } while (c != 0);
}

// Копирование узла
Node *copy_node(Node *NODE, int *bl)
{
    Node *p=NULL;

    p = (Node*)malloc(sizeof(Node));
    (p->info).category = (char*)malloc(MAXLEN*sizeof(char));
    (p->info).description = (char*)malloc(MAXLEN*sizeof(char));

    if((p->info).category!=NULL && (p->info).description!=NULL)
    {
        strcpy((p->info).category, (NODE->info).category);
        strcpy((p->info).description, (NODE->info).description);
        (p->info).expenses_income = (NODE->info).expenses_income;
        (p->info).money = (NODE->info).money;
    } else *bl = 0;

    return p;
}

void swap(Head *HEAD, int first, int second)
{
    Node *p_one, *p_two;
    Node *buff_one, *buff_two;
    int i;

    p_one = HEAD->first;
    for (i = 1; i < first - 1; i++)
        p_one = p_one->next; // Доходим до нужной позиции
    p_two = HEAD->first;
    for (i = 1; i < second - 1; i++) //Аналогично
        p_two = p_two->next;

    if (first != 1)
    {
        // Делаем саму перестановку
        buff_one = p_one->next;
        buff_two = p_two->next;
        p_one->next = buff_two;
        p_two->next = buff_one;
        buff_two->prev = p_one;
        buff_one->prev = p_two;
        p_one = buff_one->next;
        p_two = buff_two->next;
        buff_one->next = p_two;
        buff_two->next = p_one;
        if (buff_two == HEAD->last)
        {
            HEAD->last = buff_one;
        } else p_two->prev = buff_one;
    }
    else
    {
        buff_two = p_two->next;
        buff_one = p_one;
        HEAD->first = buff_two;
        p_two->next = buff_one;
        buff_two->prev = p_one;
        buff_one->prev = p_two;
        p_one = buff_one->next;
        p_two = buff_two->next;
        buff_one->next = p_two;
        buff_two->next = p_one;
        if (buff_two == HEAD->last)
        {
            HEAD->last = buff_one;
        }
        else p_two->prev = buff_one;
    }
}

// Высвобождение памяти узла
void clean_node(Node *node)
{
    //if((node->info).description != NULL)
        free((node->info).description);
    //if((node->info).category != NULL)
        free((node->info).category);
    (node->info).category = NULL;
    (node->info).description = NULL;
    free(node);
}

// Удаление узла
void remove_node(Head *my_head)
{
    Node *p;    // Указатели требуемые для удаления узла 
    int i,      // Переменная в цикле
        pos;    // Выбор позиции
    char c;

    printf("Want to see a list of notes? (1/any)\n");
    c = get_int();
    if (c == 1)
        print_managers(my_head);
    do
    {
        do
        {
            printf("Delete item numbered [From 1 to %d]: ", my_head->count);
            pos = get_int();
        } while (pos < 1 || pos>my_head->count);
        p = my_head->first;
        if (my_head->count > 1)
        {
            for (i = 1; i < pos; i++)
                p = p->next;
            if (pos == 1)
            {
                my_head->first = p->next;
                (p->next)->prev = NULL;
            }
            else if (pos == my_head->count)
            {
                my_head->last = p->prev;
                (p->prev)->next = NULL;
            }
            else
            {
                (p->prev)->next = p->next;
                (p->next)->prev = p->prev;
            }
        }
        else
        {
            my_head->first = NULL;
            my_head->last = NULL;
        }
        my_head->count--;
        clean_node(p);

        if (my_head->count > 0)
        {
            printf("Delete more? (1/any)\n");
            c = get_int();
        }
        else
            c = 1;
    } while ((c == 1) && my_head->count > 0);
}

// Сравнение двух очередных элементов в списке
int compare(Node *left, Node *right, int type)
{
    int result;

    switch (type)
    {
        case 1:
            if ((left->info).money > (right->info).money)
                result = 1;
            else if ((left->info).money < (right->info).money)
                result = -1;
            else
                result = 0;
            break;
        case 2:
            if ((left->info).expenses_income > (right->info).expenses_income)
                result = 1;
            else if ((left->info).expenses_income < (right->info).expenses_income)
                result = -1;
            else
                result = 0;
            break;
    }
    return result;
}

// Сортировка
void sort(Head *HEAD)
{
    int i, j,       // Переменные в цикле
        type;       // Вид сортировки
    int decrease;  // Enter - по убыванию. Иначе по возрастанию
    Node *p=NULL, *buff=NULL, *temp = NULL;

    do
    {
        printf("Choose sort number\n");
        printf("1 - By price, 2 - By income/expenses\n");
        type = get_int();
    } while (type<1 || type>2);
    if(type == 1)
    {
        printf("Sort Descending? (1/any)\n");
        decrease = get_int();
    }
    else
    {
        printf("Derive expenses first? (1/any)\n");
        decrease = get_int();
    }
    p = HEAD->first;
    for (i=1; i<=HEAD->count-1; i++)
    {
        buff = p->next;
        for (j=i+1; j<=HEAD->count; j++)
        {
            if ((decrease==1) ? (compare(buff, p, type) > 0) : (compare(buff, p, type) < 0))
            {
                swap(HEAD, i, j);
                temp = p;
                p = buff;
                buff = temp->next;
            }
            else
                buff = buff->next;
        }
        p = p->next;
    }
}

// Фильтр. Возвращает голову нового списка
Head *selected(Head *my_head, int *bl)
{
    Head *NEW_HEAD = NULL;
    Node *p = NULL;
    int i, expenses_income;
    float max_money = 0;
    char *category = NULL;
    NEW_HEAD = make_head(bl);

    printf("Will the new list consist only of income or expenses? Income - 1, Expenses - 2\n");
    expenses_income = get_int();
    printf("The new list will consist only of this category: \n");
    category = get_category();
    printf("The maximum amount. For example: if you enter 100, then amounts > 100 will not be displayed: ");
    max_money = get_float();

    p = my_head->first;
    for (i=0; i<my_head->count; i++)
    {
        if (((p->info).money <= max_money) && (strcmp((p->info).category, category)==0) && ((p->info).expenses_income == expenses_income))
            add_last(NEW_HEAD, copy_node(p, bl));
        p = p->next;
    }
    free(category);

    return NEW_HEAD;
}

// Высвобождение памяти списка
Head *clean_list(Head *HEAD)
{
    Node *p, *temp;
    int i;

    p = HEAD->first;
    for (i = 0; i < HEAD->count; i++)
    {
        temp = p;
        p = p->next;
        temp->next = NULL;
        temp->prev = NULL;
        clean_node(temp);
    }
    free(HEAD);
    return NULL;
}

// Редактирование узла
void edit_node(Head *list)
{
    int change_int,
        variant1,
        variant2,
        exit_flag;
    float change_float;
    
    char *change_str;    
    Node *temp_node = NULL;
    print_managers(list);
    do
    {
        puts("\nEnter number of element of list");
        printf(">");
        variant1 = get_int();
        if (variant1 > list->count || variant1 <= 0)
            printf("Number should be greater than 0 and less than length");
    }
    while(variant1 > list->count || variant1 <= 0);
    exit_flag = 1;
    do
    {
        temp_node = list->first;
        for(int i = 1; i < variant1; i++)
            temp_node = temp_node->next;
        puts("\nEdit info menu");
        puts("1. Edit expenses_income");
        puts("2. Edit category");
        puts("3. Edit description");
        puts("4. Edit money");
        puts("0. Return to back");
        variant2 = get_int();
        switch (variant2)
        {
            case 1:
                system(CLEAR);
                printf("Enter expenses or income. 1 - Income 2 - Expenses: ");
                change_int = get_int();
                (temp_node->info).expenses_income = change_int;
            break;
            case 2:
                system(CLEAR);
                printf("Enter category\n");
                change_str = get_category();
                free((temp_node->info).category);
                (temp_node->info).category = change_str;
            break;
            case 3:
                system(CLEAR);
                printf("Enter description\n");
                change_str = get_string();
                free((temp_node->info).description);
                (temp_node->info).description = change_str;
            break;
            case 4:
                system(CLEAR);
                printf("Enter money\n");
                change_float = get_float();
                (temp_node->info).money = change_float;
            break;
            case 0:
                exit_flag = 0;
            break;
            default:
                printf("ERROR");
            break;
        }
    }
    while(exit_flag);
}

// Поиск (1)
Head *search(Head *list, manager search_param, int field, int* bl)
{
    Head* search_result = NULL;
    Node* temp_node = NULL;
    
    search_result = make_head(bl);
    switch(field)
    {
        case 1:
            for (temp_node = list->first; temp_node; temp_node = temp_node->next)
                if ((temp_node->info).expenses_income == search_param.expenses_income)
                {
                    add_last(search_result, copy_node(temp_node, bl));
                }
            break;
        case 2:
            for (temp_node = list->first; temp_node; temp_node = temp_node->next)
                if (!strcmp((temp_node->info).category, search_param.category))
                {
                    add_last(search_result, copy_node(temp_node, bl));
                }
            break;
        case 3:
            for (temp_node = list->first; temp_node; temp_node = temp_node->next)
                if (!strcmp((temp_node->info).description, search_param.description))
                {
                    add_last(search_result, copy_node(temp_node, bl));
                }
            break;
        case 4:
            for (temp_node = list->first; temp_node; temp_node = temp_node->next)
                if ((temp_node->info).money == search_param.money)
                {
                    add_last(search_result, copy_node(temp_node, bl));
                }
            break;
    }
    
    return search_result;
}

// Поиск (2)
void search_managers(Head *list, int* bl)
{
    int variant,
        i;
    Head    *search_list = NULL,
            *temp        = NULL;

    manager search_param;
    int exit_flag;
    unsigned char flags[6];
    
    for (i = 0; i < 6; i++)
        flags[i] = 1;
    
    search_list = list;
    i = 0;
    do
    {
        puts("1 - Expenses/income");
        puts("2 - Category");
        puts("3 - Description");
        puts("4 - Money");

        variant = get_int(); 
        switch (variant)
        {
            case 1:
                if (flags[0] == 1)                    
                {
                    puts("Enter expenses or income. 1 - Income 2 - Expenses");
                    search_param.expenses_income = get_int();
                    flags[0] = 0;
                    temp = search_list;
                    search_list = search(search_list, search_param, 1, bl);
                    if(i != 0)
                        temp = clean_list(temp);
                    i++;
                }
                else
                    printf("You re-enter");
            break;
            case 2:
                if (flags[1] == 1)                    
                {
                    puts("Enter category");
                    search_param.category = get_category();
                    flags[1] = 0;
                    temp = search_list;
                    search_list = search(search_list, search_param, 2, bl);
                    if(i != 0)
                        temp = clean_list(temp);
                    i++;
                    free(search_param.category);
                }
                else
                    printf("You re-enter");
            break;
            case 3:
                if (flags[2] == 1)                    
                {
                    puts("Enter description");
                    search_param.description = get_string();
                    flags[2] = 0;
                    temp = search_list;
                    search_list = search(search_list, search_param, 3, bl);
                    if(i != 0)
                        temp = clean_list(temp);
                    i++;
                    free(search_param.description);
                }
                else
                    printf("You re-enter");
            break;
            case 4:
                if (flags[3] == 1)                    
                {
                    puts("Enter money");
                    search_param.money = get_int();
                    flags[3] = 0;
                    temp = search_list;
                    search_list = search(search_list, search_param, 4, bl);
                    if(i != 0)
                        temp = clean_list(temp);
                    i++;
                }
                else
                    printf("You re-enter");
            break;
            default:
                printf("Error");
            break;
        }
        
        if(i != 4)
        {
            puts("\nDo you want to choose more param? (1/any)");
            printf(">");
            exit_flag = get_int();
        }
        else
            exit_flag = 0;
    }
    while(exit_flag == 1);
    
    if (search_list != NULL && search_list->first != NULL)
    {
        print_managers(search_list);
        pause();
    }
    else
    {
        printf("Nothing found\n");
        pause();
    }

    if (i != 0)
        search_list = clean_list(search_list);
}