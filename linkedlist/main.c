#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linkedlist.h"

int main()
{
    struct linked_list *list = ll_new();
    int num_elements = 100000;

    for(int i = 0; i < num_elements; i++)
    {
        ll_append(list, rand() % num_elements);
    }

    while(list->size != 0)
    {
        if(list->size % 100 == 0)
        {
            printf("%i\n", list->size);
        }

        ll_remove(list, rand() % list->size);
    }
}