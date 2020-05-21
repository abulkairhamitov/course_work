#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "./include/dbl_list.h"
#include "./include/common.h"
#include "./include/get.h"
#include "./include/w_file.h"

// Меню
int Menu(int q)
{
    int Q;
    system("cls");
    puts("MENU");
    switch(q)
    {
        case 0:
            puts("1 - Input data");
            puts("2 - Output data");
            puts("3 - Actions with the database");
            puts("4 - Filter");
            puts("5 - Output result");
            puts("6 - Help");
            puts("0 - Exit");
            break;
        case 1:
            puts("1 - Input from console");
            puts("2 - Input from file");
            puts("0 - Come back");
            break;
        case 12:
            puts("1 - Input from default file (database.txt)");
            puts("2 - Select a file");
            puts("0 - Come back");
            break;
        case 3:
            puts("1 - Swap any items");
            puts("2 - Remove any items");
            puts("3 - Sort database");
            puts("4 - Add item");
            puts("5 - Save changes to file");
            puts("6 - Edit element of list");
            puts("7 - Search manager");
            puts("0 - Come back");
            break;
        case 5:
            puts("1 - Console output");
            puts("2 - Output in file");
            puts("0 - Come back");
            break;
        case 52:
            puts("1 - Write to file by default(output.txt)");
            puts("2 - Select a file");
            puts("0 - Come back");
    }

    printf("Select menu item - ");
    scanf("%d", &Q);
    printf("\n");
    fflush(stdin);
    return Q;
}

// Справка
void Help()
{
    system("cls");
    printf("\tHelp\n");
    printf("  First you need to enter notes (your income or expenses). To enter the input press 1\n");
    printf("  Notes have the following characteristics:\n");
    printf("  Income or Cost. Category. Description of the note. Amount of money spent\n");
    printf("  For actions with the list, select item 3. Filter the list by the specified categories - item 4. Display the result - 5.\n");
}

int dbl_list()
{
    Head *HEAD      = NULL,     // Голова списка
         *NEW_HEAD  = NULL;     // Голова результирующего списка
    Node *p         = NULL;     // Очередной узел
    int Q,                      // Выбор пункта меню
        Q3, Q1, Q12, Q5, Q52,   // Выбор пункта подменю
        output = 0,             // Проверка на ввод входных данных
        bl = 1,                 // Проверка на выделение памяти
        valid_file,             // Валидация файла
        first,                  // Элемент сортировки
        buff,                   // Для swap first и second
        second;                 // Элемент сортировки
    char c = 0;                 // Ввод числа или Enter
    HEAD = make_head(&bl);      // Голова

    if(bl)
    {
        do 
        {
            Q = Menu(0);
            switch (Q)
            {
                case 1:     //input
                    output = 0;
                    if (HEAD->count)
                    {
                        HEAD = clean_list(HEAD);
                        HEAD = make_head(&bl);
                        if (NEW_HEAD)
                            NEW_HEAD = clean_list(NEW_HEAD);
                    }
                    do
                    {
                        Q1 = Menu(1);
                        switch (Q1)
                        {
                            case 1:
                                add_item(HEAD, &bl);
                                printf("Successful input.\n");
                                Q1=0;
                                break;
                            case 2:
                                do
                                {
                                    Q12 = Menu(12);
                                    switch (Q12)
                                    {
                                        case 1:
                                            valid_file = get_database(HEAD, 0); // database.txt
                                            if (valid_file == 1)
                                                printf("Successful input.\n");
                                            else if (valid_file == 0)
                                                printf("Error: Nonexistent file.\n");
                                            else if (valid_file == 2)
                                                printf("Error, file is empty.\n");
                                            else
                                                printf("Error reading from file.\n");
                                            Q12 = 0;
                                            break;
                                        case 2:
                                            valid_file = get_database(HEAD, 1); // enter the path of file
                                            if (valid_file==1)
                                                printf("Successful input.\n");
                                            else if (valid_file == 0)
                                                printf("Error: Nonexistent file.\n");
                                            else if (valid_file == 2)
                                                printf("Error, file is empty.\n");
                                            else
                                                printf("Error reading from file.\n");
                                            Q12 = 0;
                                            break;
                                        case 0:
                                            break;
                                        default:
                                            puts("Error, try again.\n");
                                    }
                                } while (Q12 != 0 && bl);

                                Q1 = 0;
                                break;
                            case 0:
                                break;
                            default:
                                puts("Try again.");
                        }
                    } while(Q1 != 0 && bl);

                    break;
                case 2:     //output
                    if (HEAD->count)
                        print_managers(HEAD);
                    else
                        printf("No input to print!\n");
                    break;
                case 3:
                    if (HEAD->count != 0)
                    {
                        do
                        {
                            Q3 = Menu(3);
                            switch (Q3)
                            {
                                case 1:
                                    if (HEAD->count > 1)
                                        do
                                        {
                                            do
                                            {
                                                system("cls");
                                                printf("Do you want see list of managers? (y/n)\n");
                                                c = getchar();
                                                if (c == 'Y' || c == 'y')
                                                    print_managers(HEAD);
                                                printf("Enter first item number [from 1 to %d]: ", HEAD->count);
                                                first = get_int();
                                                printf("Enter second item number [from 1 to %d]: ", HEAD->count);
                                                second = get_int();
                                            } while ((first<1 || second>HEAD->count) || (second<1 || first>HEAD->count));
                                            if (first>second)
                                                {
                                                    buff = first;
                                                    first = second;
                                                    second = buff;
                                                }
                                            swap(HEAD, first, second);
                                            puts("Once more swap? (y/n)");
                                            c = getch();
                                        } while (c != 'n');
                                    else
                                    {
                                        Q3=0;
                                        puts("The list must have more than one item.");
                                    }
                                    break;
                                case 2:
                                    remove_node(HEAD);
                                    break;
                                case 3:
                                    sort(HEAD);
                                    puts("Successfully sorted.");
                                    system("pause");
                                    break;
                                case 4:
                                    add_item(HEAD, &bl);
                                    break;
                                case 5:
                                    valid_file = write_to_file(HEAD, 1);
                                    if (valid_file == 1)
                                        puts("Successful write to file");
                                    else
                                        puts("Error write to file");
                                    system("pause");
                                    break;
                                case 6:
                                    edit_node(HEAD);
                                    break;
                                case 7:
                                    search_managers(HEAD, &bl);
                                    break;
                                case 0:
                                    Q3=0;
                                    break;
                                default:
                                    puts("Try again!");
                                    break;
                            }
                        } while (Q3 != 0 && HEAD->count && bl);
                    }
                    else
                        printf("No input to actions!\n");
                    break;
                case 4:     //process
                    if (HEAD->count)
                    {
                        NEW_HEAD = selected(HEAD, &bl);
                        output = 1;
                    }
                    else
                        printf("No input to process!\n");
                    break;
                case 5:     //output result
                    if (output)
                        do
                        {
                            Q5 = Menu(5);
                            switch (Q5)
                            {
                                case 1:
                                    if (NEW_HEAD->count) print_managers(NEW_HEAD);
                                    else printf("Managers not found.\n");
                                    Q5=0;
                                    break;
                                case 2:
                                    do
                                    {
                                        Q52 = Menu(52);
                                        switch (Q52)
                                        {
                                            case 1:
                                                if (NEW_HEAD->count) valid_file = write_to_file(NEW_HEAD, 0);
                                                else printf("Managers not found.\n");
                                                if (valid_file == 1)
                                                    puts("Successful write to file.");
                                                else
                                                    puts("Error writing to file.");
                                                Q52 = 0;
                                                break;
                                            case 2:
                                                if (NEW_HEAD->count) valid_file = write_to_file(NEW_HEAD, 1);
                                                else printf("Managers not found.\n");
                                                if (valid_file == 1)
                                                    puts("Successful write to file.");
                                                else
                                                    puts("Error writing to file.");
                                                Q52 = 0;
                                                break;
                                            case 0:
                                                break;
                                            default:
                                                puts("Error, try again.\n");
                                        }
                                    } while (Q52 != 0 && bl);

                                    Q5=0;
                                    break;
                                case 0:
                                    break;
                                default:
                                    puts("Try again.");
                            }
                        } while(Q5 != 0 && bl);
                    else
                        printf("No processed data to output!\n");
                    break;
                case 6:     //help
                    Help();
                    break;
                case 0:
                    break;
                default:
                    printf("Error! Try again!\n");
                    break;
            }
            system("pause");
        } while (Q && bl);
    } else printf("Error memory");
    // Высвобождение памяти
    if (HEAD->count != 0)
        HEAD = clean_list(HEAD);
    if (NEW_HEAD)
        NEW_HEAD = clean_list(NEW_HEAD);
    return 0;
}