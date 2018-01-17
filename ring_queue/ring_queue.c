#include <malloc.h>
#include <string.h>

#include "ring_queue.h"

typedef struct ring_queue
{
    size_t max_elements;
    __uint8_t data_size;

    void *data;
    __uint8_t *full;

    size_t pop_ptr;
    size_t push_ptr;
} ring_queue_t;

ring_queue_t *new_ring_queue(size_t max_elements, __uint8_t data_size)
{
    ring_queue_t *ret = malloc(sizeof(ring_queue_t));

    ret->max_elements = max_elements;
    ret->data_size = data_size;

    ret->data = calloc(max_elements, data_size);
    ret->full = calloc(max_elements / 8 + 1, 1);

    ret->pop_ptr = 0;
    ret->push_ptr = 0;

    return ret;
}

void free_ring_queue(ring_queue_t *queue)
{
    free(queue->data);
    free(queue->full);
    free(queue);
}

__uint8_t get_filled(ring_queue_t *queue, size_t ptr)
{
    return (__uint8_t) ((queue->full[ptr / 8] >> (ptr % 8)) & 1);
}

void set_filled(ring_queue_t *queue, size_t ptr, __uint8_t value)
{
    if(get_filled(queue, ptr) != value)
    {
        queue->full[ptr / 8] &= ~(1 << (ptr % 8));
        queue->full[ptr / 8] |= ((value & 1) << (ptr % 8));
    }
}

size_t queue_size(ring_queue_t *queue)
{
    if(queue->push_ptr > queue->pop_ptr)
    {
        return queue->push_ptr - queue->pop_ptr;
    }

    if(queue->push_ptr == queue->pop_ptr)
    {
        //queue is either completely full or completely empty, so check an element
        return get_filled(queue, 0) ? queue->max_elements : 0;
    }

    if(queue->push_ptr < queue->pop_ptr)
    {
        return queue->push_ptr + queue->max_elements - queue->pop_ptr;
    }
}

void queue_push(ring_queue_t *queue, void *value)
{
    if(!get_filled(queue, queue->push_ptr))
    {
        memcpy(queue->data + queue->data_size * queue->push_ptr, value, queue->data_size);
        set_filled(queue, queue->push_ptr, 1);

        queue->push_ptr++;
        if(queue->push_ptr == queue->max_elements)
        {
            queue->push_ptr = 0;
        }
    }
    else
    {
        //TODO: blocking?
        fprintf(stderr, "Not enough space in queue to push %p\n", value);
    }
}

void queue_pop(ring_queue_t *queue, void *address)
{
    if(queue_size(queue))
    {
        memcpy(address, queue->data + queue->data_size * queue->pop_ptr, queue->data_size);
        set_filled(queue, queue->pop_ptr, 0);

        queue->pop_ptr++;
        if(queue->pop_ptr == queue->max_elements)
        {
            queue->pop_ptr = 0;
        }
    }
    else
    {
        //TODO: blocking?
        fprintf(stderr, "Could not pop queue, is empty\n");
    }
}