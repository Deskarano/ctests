#ifndef RING_QUEUE_RING_QUEUE_H
#define RING_QUEUE_RING_QUEUE_H

typedef struct ring_queue ring_queue_t;

ring_queue_t *new_ring_queue(unsigned long max_elements, unsigned char data_size);
void free_ring_queue(ring_queue_t *queue);

void queue_push(ring_queue_t *queue, void *value);
void queue_pop(ring_queue_t *queue, void *addr);

unsigned long queue_size(ring_queue_t *queue);

#endif //RING_QUEUE_RING_QUEUE_H