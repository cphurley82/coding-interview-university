#include "data-structures/arrays/c/cvector.h"

#include "stdlib.h"

cvector* cvector_new() {
    cvector* obj = malloc(sizeof(cvector));
    obj->size = 0;
    return obj;
}

int cvector_size(cvector* obj) {
    return obj->size;
}