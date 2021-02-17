#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  int size_bytes;
  int capacity_bytes;
  int *data;
} cvector;

cvector *cvector_new();
void cvector_delete(cvector *const obj);
int cvector_size(const cvector *const obj);
void cvector_resize(cvector *const obj, const int size);
int cvector_capacity(const cvector *const obj);
bool cvector_is_empty(const cvector *const obj);
uint8_t cvector_at(const cvector *const obj, int index);
void cvector_set(cvector *const obj, const int index, const int value);