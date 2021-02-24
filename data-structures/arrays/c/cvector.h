#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  int size_bytes;
  int capacity_ints;
  int* data;
} cvector;

cvector* cvector_new();
void cvector_delete(cvector* const obj);
bool cvector_is_empty(const cvector* const obj);

int cvector_size_ints(const cvector* const obj);
void cvector_resize_ints(cvector* const obj, const int size_ints);
int cvector_capacity_ints(const cvector* const obj);
void cvector_set_int(cvector* const obj, const int index, const int value);
int cvector_at_int(const cvector* const obj, int index);
void cvector_push_int(cvector* const obj, int value);
void cvector_insert_int(cvector* const obj, int index, int value);

int cvector_size_bytes(const cvector* const obj);
void cvector_resize_bytes(cvector* const obj, const int size_bytes);
void cvector_set_byte(cvector* const obj, const int index, uint8_t byte);
uint8_t cvector_at_byte(const cvector* const obj, int index);
void cvector_push_byte(cvector* const obj, uint8_t value);
void cvector_insert_byte(cvector* const obj, int index, uint8_t value);

// Internal utility functions.
int cvector_util_round_up_to_power_of_two(int number);
int cvector_util_determine_min_capacity_ints_from_size_bytes(int size_bytes);