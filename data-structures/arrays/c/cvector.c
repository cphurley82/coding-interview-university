#include "data-structures/arrays/c/cvector.h"

#include <assert.h>
#include <stdlib.h>

cvector *cvector_new()
{
    cvector *obj = malloc(sizeof(cvector));
    obj->size = 0;
    obj->capacity = 0;
    return obj;
}

void cvector_delete(cvector *obj) { free(obj); }

int cvector_size(const cvector *obj) { return obj->size; }

void cvector_resize(cvector *obj, const int size)
{
    obj->size = size;
    obj->capacity = size;
}

int cvector_capacity(const cvector *obj) { return obj->capacity; }

bool cvector_is_empty(const cvector *obj)
{
    return obj->size == 0 ? true : false;
}

uint8_t cvector_at(const cvector *obj, int index)
{
    assert(obj->size > index);
    return 0;
}