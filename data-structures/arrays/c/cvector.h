#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  int size_ints;
  int capacity_ints;
  int *data;
} cvector;

cvector *cvector_new();
void cvector_delete(cvector *const obj);
int cvector_size_ints(const cvector *const obj);
void cvector_resize_ints(cvector *const obj, const int size_ints);
int cvector_capacity_ints(const cvector *const obj);
bool cvector_is_empty(const cvector *const obj);
uint8_t cvector_at_int(const cvector *const obj, int index);
void cvector_set_int(cvector *const obj, const int index, const int value);

// Internal utility functions.
int cvector_round_up_to_power_of_two(int number);