#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "./include/dbl_list.h"
#include "./include/get.h"
#include "./include/const.h"


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
    printf("|Expenses/Income| category|          Description|       Money|\n");
    printf("|_______________|_________|_____________________|____________|\n");
    p = my_head->first;
    for (i = 0; i < my_head->count; i++)
    {
        if( (p->info).expenses_income == 1)
        {
            printf("|         Income|%9.22s|%21.22s|%12.0f|\n", (p->info).category, (p->info).description, (p->info).money);
            printf("|_______________|_________|_____________________|____________|\n");
        } else
        {
            printf("|        Expense|%9.22s|%21.22s|%12.0f|\n", (p->info).category, (p->info).description, (p->info).money);
            printf("|_______________|_________|_____________________|____________|\n");
        }
        p = p->next;
    }
}

char *get_category() // Выбор категории. Возвращает число (пункт в списка категории)
{
    char c;     // Переменная для "fflush"
    int q,      // Выбор пункта из списка категорий 
        i;      // Индекс категории
    for (i = 0; i < cat_num; i++)
        printf("%d. %s\n", i+1, categories[i]);
    do
    {
        scanf("%d", &q);
        if (q <= 0 || q > (int)sizeof(categories)/sizeof(char*))
            printf("You entered an invalid value, try again: \n");
    } while (q <= 0 || q > (int)sizeof(categories)/sizeof(char*));
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Your choice %s\n", categories[q-1]);
    return categories[q-1];
}

void fill_node(manager *list, int *bl) // Ввод очередной структуры
{
    system("cls");
    char c;
    list->category = (char*)malloc(MAXLEN*sizeof(char));
    list->description = (char*)malloc(MAXLEN*sizeof(char));
    while ((c = getchar()) != '\n' && c != EOF);
    if (list->category && list->description)
    {
        do
        {
            printf("Choose this income or expense. Income - 1, expense - 2\n");
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
    else *bl = 0;
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
    } else;
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
    char c;
    do
    {
        printf("1 - Add node to start\n2 - Add node to end\n3 - Insert node\nPress 0 to stop\n");
        c = getchar();
        if (c != 48) p = create_node(bl);
        switch (c)
        {
            case 49:
                add_first(HEAD, p);
                break;
            case 50:
                add_last(HEAD, p);
                break;
            case 51:
                insert(HEAD, p);
                break;
            case 48:
                break;
            default:
                puts("Error, try again.\n");
        }
    } while (c != 48);
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
Node *clean_node(Node *node)
{
    free((node->info).description);
    (node->info).description = NULL;
    free(node);
    return NULL;
}

// Удаление узла
void remove_node(Head *my_head)
{
    Node *p;    // Указатели требуемые для удаления узла 
    int i,      // Переменная в цикле
        pos;    // Выбор позиции
    char c;

    printf("Want to see a list of notes? (y/n)\n");
    c = getchar();
    if (c == 'y' || c == 'Y')
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
            for (i = 1; i < pos - 1; i++)
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
            printf("Delete more? (y/n)\n");
            c = getchar();
        }
        else
            c = 'y';
    } while ((c == 'y' || c == 'Y') && my_head->count > 0);
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
    char decrease;  // Enter - по убыванию. Иначе по возрастанию
    Node *p=NULL, *buff=NULL, *temp = NULL;

    do
    {
        printf("Choose sort number\n");
        printf("1 - By price, 2 - By income/expenses\n");
        type = get_int();
    } while (type<1 || type>2);
    if(type == 1)
    {
        printf("Sort Descending? (y/n)");
        decrease = getchar();
    }
    else
    {
        printf("Derive expenses first? (y/n)");
        decrease = getchar();
    }
    p = HEAD->first;
    for (i=1; i<=HEAD->count-1; i++)
    {
        buff = p->next;
        for (j=i+1; j<=HEAD->count; j++)
        {
            if ((decrease=='y') ? (compare(buff, p, type) > 0) : (compare(buff, p, type) < 0))
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
    printf("The maximum amount. For example: if you enter 100, then amounts> 100 will not be displayed: ");
    max_money = get_float();

    p = my_head->first;
    for (i=0; i<my_head->count; i++)
    {
        if (((p->info).money <= max_money) && (strcmp((p->info).category, category)==0) && ((p->info).expenses_income == expenses_income))
            add_last(NEW_HEAD, copy_node(p, bl));
        p = p->next;
    }

    return NEW_HEAD;
}

// Высвобождение памяти списка
Head *clean_list(Head *HEAD)
{
    Node *p, *temp;
    int i;

    p = HEAD->first;
    HEAD->count = 0;
    for (i = 0; i < HEAD->count; i++)
    {
        temp = p;
        p = p->next;
        temp->next = NULL;
        temp->prev = NULL;
        temp = clean_node(temp);
    }
    free(HEAD);
    return NULL;
}

void edit_node(Head *list)
{
    int change_int,
        variant1,
        variant2,
        exit_flag;
    float change_float;
    
    char *change_str;    
    Node *temp_node = NULL;
    change_str = (char*)malloc(MAXLEN*sizeof(char));
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
                system("cls");
                printf("Enter expenses or income. 1 - Income 2 - Expenses: ");
                change_int = get_int();
                (temp_node->info).expenses_income = change_int;
            break;
            case 2:
                system("cls");
                (temp_node->info).category = get_category();
            break;
            case 3:
                system("cls");
                printf("Enter description");
                change_str = get_string();
                free((temp_node->info).description);
                (temp_node->info).description = change_str;
            break;
            case 4:
                system("cls");
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

Head *search(Head *list, manager search_param, int field, int* bl)
{
    Head* search_result = NULL;
    Node* temp_node = NULL;
    Node* cp_node = NULL;
    
    search_result = make_head(bl);
    switch(field)
    {
        case 1:
            for (temp_node = list->first; temp_node; temp_node = temp_node->next)
                if ((temp_node->info).expenses_income == search_param.expenses_income)
                {
                    cp_node = copy_node(temp_node, bl);
                    add_last(search_result, cp_node);
                }
            break;
        case 2:
            for (temp_node = list->first; temp_node; temp_node = temp_node->next)
                if (!strcmp((temp_node->info).category, search_param.category))
                {
                    cp_node = copy_node(temp_node, bl);
                    add_last(search_result, cp_node);
                }
            break;
        case 3:
            for (temp_node = list->first; temp_node; temp_node = temp_node->next)
                if (!strcmp((temp_node->info).description, search_param.description))
                {
                    cp_node = copy_node(temp_node, bl);
                    add_last(search_result, cp_node);
                }
            break;
        case 4:
            for (temp_node = list->first; temp_node; temp_node = temp_node->next)
                if ((temp_node->info).money == search_param.money)
                {
                    cp_node = copy_node(temp_node, bl);
                    add_last(search_result, cp_node);
                }
            break;
    }
    
    return search_result;
}

void search_managers(Head *list, int* bl)
{
    int variant,
        i;
    Head *search_list = NULL,
         *temp = NULL;

    manager search_param;
    char exit_flag;
    unsigned char flags[6];
    
    for (i = 0; i < 6; i++)
        flags[i] = 1;
    
    search_list = make_head(bl);
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
                    if(i == 0)
                        search_list = search(list, search_param, 1, bl);
                    else
                        search_list = search(search_list, search_param, 1, bl);
                    if (i != 0)
                        temp = clean_list(temp);
                    i++;
                }
                else
                    printf("You re-enter");
            break;
            case 2:
                if (flags[1] == 1)                    
                {
                    search_param.category = get_category();
                    flags[1] = 0;
                    temp = search_list;
                    if(i == 0)
                        search_list = search(list, search_param, 2, bl);
                    else
                        search_list = search(search_list, search_param, 2, bl);
                    if (i != 0)
                        temp = clean_list(temp);
                    i++;
                }
                else
                    printf("You re-enter");
            break;
            case 3:
                if (flags[2] == 1)                    
                {
                    search_param.description = get_string();
                    flags[2] = 0;
                    if(i == 0)
                        search_list = search(list, search_param, 3, bl);
                    else
                        search_list = search(search_list, search_param, 3, bl);
                    if (i != 0)
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
                    search_param.money = get_int();
                    flags[3] = 0;
                    temp = search_list;
                    if(i == 0)
                        search_list = search(list, search_param, 4, bl);
                    else
                        search_list = search(search_list, search_param, 4, bl);
                    if (i != 0)
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
            puts("\nDo you want to choose more param? Press y, else any key");
            printf(">");
            exit_flag = getchar();
        }
        else
            exit_flag = 'n';
    }
    while(exit_flag == 'Y' || exit_flag == 'y');
    
    if (search_list != NULL && search_list->first != NULL)
    {
        print_managers(search_list);
        system("pause");
    }
    else
    {
        printf("Nothing found\n");
        system("pause");
    }

    if (i != 0)
        search_list = clean_list(search_list);
    if (i > 2)
        temp = clean_list(temp);
}