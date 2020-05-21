#ifndef LIST_H
#define LIST_H
#define MAXSTR 128

typedef struct
{
    // Описание полей
    int expenses_income;
    char *category;     // Категория затрата/дохода
    char *description;  // Описание (комментарий) к покупке
    float money;        // Количество потраченных/заработанных денег
} manager;

typedef struct manager_elem
{
    manager info;
    struct manager_elem *next;
    struct manager_elem *prev;
} Node; // Очередной элемент (узел) списка

typedef struct
{
    int count;
    Node *first;
    Node *last;
} Head; // Голова списки

#endif // LIST_H

Head *make_head(int *bl); // Создание головы

Node *create_node(int *bl); // Создание узла

char *get_category();                           // Ввод категории 

void fill_node(manager *list, int *bl);

void add_item(Head *HEAD, int *bl);   // Добавление элемента в список

void print_managers(Head *my_head);             // Вывод заметок

void *add_first(Head *my_head, Node *new_node); // Добавление элемента в начало

void *add_last(Head *my_head, Node *new_node); // Добавление элемента в конец

void insert(Head *my_head, Node *new_node); // Добавление элемента в n-ую позицию

Node *copy_node(Node *NODE, int *bl);           // Копирование элемента списка и возвращает копию

void swap(Head *HEAD, int first, int second);

void remove_node(Head *my_head);

int compare(Node *left, Node *right, int type);         // Сравнение элементов списка для сортировки

void sort(Head *HEAD);                                  // Сортировка по цене или доходам/затратам

Head *selected(Head *my_head, int *bl);                 // Фильтр по заметкам по минимальной цене и категории

Node *clean_node(Node *node);

Head *clean_list(Head *HEAD);

void edit_node(Head *list);

Head *search(Head *list, manager search_param, int field, int* bl);

void search_managers(Head *list, int* bl);