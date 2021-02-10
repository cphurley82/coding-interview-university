#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  int size;
  int capacity;
} cvector;

cvector *cvector_new();
void cvector_delete(cvector *obj);
int cvector_size(const cvector *obj);
void cvector_resize(cvector *obj, const int size);
int cvector_capacity(const cvector *obj);
bool cvector_is_empty(const cvector *obj);
uint8_t cvector_at(const cvector *obj, int index);
