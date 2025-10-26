#ifndef DYNARRAY_H
#define DYNARRAY_H
#include <stdlib.h>
#include <stdint.h>

typedef struct Array
{
    uintptr_t* array;
    size_t size;
    size_t used;
} Array;

void ConstructArray(Array *a, size_t initialSize);
void ArrayInsert(Array *a, uintptr_t element);
void ArrayRemove(Array *a, int i);
void ArrayFree(Array *a);
uintptr_t ArrayGet(Array *a, int i);

#endif