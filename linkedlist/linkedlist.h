#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>

struct linked_list_element
{
    struct linked_list_element *prev;
    struct linked_list_element *next;

    int value;
};

struct linked_list
{
    struct linked_list_element *first_element;
    struct linked_list_element *last_element;

    int size;
};

struct linked_list *ll_new()
{
    struct linked_list *list = malloc(sizeof(struct linked_list));
    list->size = 0;

    return list;
}

void ll_print(struct linked_list *list)
{
    struct linked_list_element *current = list->first_element;

    printf("[");
    for(int i = 0; i < list->size - 1; i++)
    {
        printf("%i, ", current->value);
        current = current->next;
    }

    printf("%i]\n", current->value);
}

int ll_get(struct linked_list *list, int index)
{
    struct linked_list_element *target = list->first_element;

    for(int i = 0; i < index; i++)
    {
        target = target->next;
    }

    return target->value;
}

void ll_set(struct linked_list *list, int index, int value)
{
    struct linked_list_element *target = list->first_element;

    for(int i = 0; i < index; i++)
    {
        target = target->next;
    }

    target->value = value;
}

void ll_append(struct linked_list *list, int value)
{
    struct linked_list_element *new_element = malloc(sizeof(struct linked_list_element));
    new_element->value = value;

    if(list->size == 0)
    {
        list->first_element = new_element;
        list->last_element = new_element;
    }
    else
    {
        new_element->prev = list->last_element;
        list->last_element->next = new_element;

        list->last_element = new_element;
    }

    ++list->size;
}

void ll_add(struct linked_list *list, int index, int value)
{
    struct linked_list_element *new_element = malloc(sizeof(struct linked_list_element));
    new_element->value = value;

    if(index == 0)
    {
        new_element->next = list->first_element;
        list->first_element->prev = new_element;

        list->first_element = new_element;
    }
    else
    {
        struct linked_list_element *target = list->first_element;

        for(int i = 1; i < index; i++)
        {
            target = target->next;
        }

        new_element->prev = target;
        new_element->next = target->next;

        target->next->prev = new_element;
        target->next = new_element;
    }

    ++list->size;
}

void ll_remove(struct linked_list *list, int index)
{
    struct linked_list_element *target = list->first_element;

    if(list->size == 1)
    {
        list->first_element = NULL;
        list->last_element = NULL;
    }
    else if(index == 0)
    {
        target->next->prev = NULL;
        list->first_element = target->next;
    }
    else if(index == list->size - 1)
    {
        target = list->last_element;
        target->prev->next = NULL;
        list->last_element = target->prev;
    }
    else
    {
        for(int i = 0; i < index; i++)
        {
            target = target->next;
        }

        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    free(target);
    --list->size;
}

#endif //LINKEDLIST_LINKEDLIST_H