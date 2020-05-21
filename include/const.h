#ifndef CONST_H
#define CONST_H
#define cat_num 5

//Категории затрат/доходов
char *categories[cat_num] = 
{
    "Food", 
    "Transport",
    "Clothes", 
    "Social", 
    "Other"
};

#endif

#ifdef __linux__
    #define CLEAR "clear"
#else
    #define CLEAR "cls"
#endif