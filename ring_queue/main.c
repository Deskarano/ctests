#include <stdio.h>

#include "ring_queue.h"

int main()
{
    ring_queue_t *queue = new_ring_queue(100, sizeof(int));
    int *pop;

    for(int i = 0; i < 75; i++)
    {
        queue_push(queue, &i);
        printf("Pushed %i\n", i);
    }

    printf("Size: %i\n", queue_size(queue));
    print_full(queue);

    for(int i = 0; i < 50; i++)
    {
        queue_pop(queue, pop);
        printf("Popped %i\n", *pop);
    }

    printf("%i\n", queue_size(queue));
    print_full(queue);

    for(int i = 0; i < 75; i++)
    {
        queue_push(queue, &i);
        printf("Pushed %i\n", i);
    }

    printf("%i\n", queue_size(queue));
    print_full(queue);

    for(int i = 0; i < 100; i++)
    {
        queue_pop(queue, pop);
        printf("Popped %i\n", *pop);
    }

    printf("%i\n", queue_size(queue));
    print_full(queue);
    free_ring_queue(queue);
}