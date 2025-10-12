#include "array.h"

void ConstructArray(Array *a, size_t initialSize)
{
    a->array = calloc(initialSize, sizeof(uintptr_t));
    a->used = 0;
    a->size = initialSize;
}

void ArrayInsert(Array *a, uintptr_t element)
{
    if (a->used == a->size)
    {
        a->size *= 2;
        a->array = realloc(a->array, a->size * sizeof(uintptr_t));
    }
    a->array[a->used++] = element;
}

void ArrayRemove(Array *a, int i)
{
    if (i < 0 || (size_t)i >= a->used)
        return;
    
    for (size_t j = 0; j < a->used - 1; j++)
    {
        a->array[j] = a->array[j + 1];
    }

    a->used--;
}

void ArrayFree(Array *a)
{
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}