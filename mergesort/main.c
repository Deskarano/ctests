#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct mergeArgs
{
    int *arr;
    int from;
    int to;
};

void printArray(int *arr, int from, int to)
{
    for(int i = from; i < to; i++)
    {
        printf("%i ", arr[i]);
    }

    printf("\n");
}

void merge(int *arr, int from1, int to1, int from2, int to2)
{
    int *backup = malloc((to2 - from1) * sizeof(int));

    for(int i = 0; i < to2 - from1; i++)
    {
        backup[i] = arr[from1 + i];
    }

    int ptr1 = from1;
    int ptr2 = from2;
    int resultptr = from1;

    while(ptr1 < to1 && ptr2 < to2)
    {
        if(backup[ptr1 - from1] < backup[ptr2 - from1])
        {
            arr[resultptr] = backup[ptr1 - from1];
            ptr1++;
        }
        else
        {
            arr[resultptr] = backup[ptr2 - from1];
            ptr2++;
        }

        resultptr++;
    }

    while(ptr1 < to1)
    {
        arr[resultptr] = backup[ptr1 - from1];
        ptr1++;
        resultptr++;
    }

    while(ptr2 < to2)
    {
        arr[resultptr] = backup[ptr2 - from1];
        ptr2++;
        resultptr++;
    }

    free(backup);
}

void *mergeSort(void *args)
{
    int *arr = ((struct mergeArgs *) args)->arr;
    int from = ((struct mergeArgs *) args)->from;
    int to = ((struct mergeArgs *) args)->to;

    int boundary = (from + to) / 2;

    if(from + 1 != boundary)
    {
        struct mergeArgs newArgs;
        newArgs.arr = arr;
        newArgs.from = from;
        newArgs.to = boundary;

        mergeSort(&newArgs);
    }

    if(boundary + 1 != to)
    {
        struct mergeArgs newArgs;
        newArgs.arr = arr;
        newArgs.from = boundary;
        newArgs.to = to;

        mergeSort(&newArgs);
    }

    merge(arr, from, boundary, boundary, to);
    return NULL;
}

void mergeSortMultithread(int *arr, int from, int to, int numThreads)
{
    struct mergeArgs args[numThreads];
    pthread_t threads[numThreads];

    for(int i = 0; i < numThreads; i++)
    {
        args[i].arr = arr;
        args[i].from = i * (to - from) / numThreads;
        args[i].to = (i + 1) * (to - from) / numThreads;

        printf("creating thread %i\n", i);
        pthread_create(&threads[i], NULL, mergeSort, &args[i]);
    }

    for(int i = 0; i < numThreads; i++)
    {
        printf("joining to thread %i\n", i);
        pthread_join(threads[i], NULL);
        
        if(i != 0)
        {
            merge(arr, 0, args[i - 1].to, args[i].from, args[i].to);
        }
    }
}

int isSorted(int *arr, int arrLength)
{
    for(int i = 1; i < arrLength; i++)
    {
        if(arr[i - 1] > arr[i])
        {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[])
{
    int length = 50000000;
    int threads = 6;

    int *arr = malloc(length * sizeof(int));

    srand((unsigned int) time(NULL));

    for(int i = 0; i < length; i++)
    {
        arr[i] = rand() % length;
    }

    mergeSortMultithread(arr, 0, length, threads);
    printf("%i", isSorted(arr, length));
}