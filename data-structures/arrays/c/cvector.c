#include "data-structures/arrays/c/cvector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

cvector* cvector_new() {
  cvector* obj = malloc(sizeof(cvector));
  obj->size_bytes = 0;
  obj->capacity_ints = 0;
  obj->data = NULL;
  return obj;
}

void cvector_delete(cvector* const obj) { free(obj); }

int cvector_size_ints(const cvector* const obj) {
  // Will round down if size_bytes is not an even multiple of sizeof(int).
  return obj->size_bytes / sizeof(int);
}

void cvector_resize_ints(cvector* const obj, const int size_ints) {
  cvector_resize_bytes(obj, size_ints * sizeof(int));
}

int cvector_capacity_ints(const cvector* const obj) {
  return obj->capacity_ints;
}

bool cvector_is_empty(const cvector* const obj) {
  return obj->size_bytes == 0 ? true : false;
}

int cvector_at_int(const cvector* const obj, int index) {
  assert(obj->size_bytes > index * sizeof(int));
  return obj->data[index];
}

void cvector_push_int(cvector* const obj, int value) {
  int new_index = cvector_size_ints(obj);
  cvector_resize_ints(obj, new_index + 1);
  cvector_set_int(obj, new_index, value);
}

void cvector_set_int(cvector* const obj, const int index, const int value) {
  if (index >= cvector_size_ints(obj)) {
    cvector_resize_ints(obj, index + 1);
  }
  obj->data[index] = value;
}

void cvector_insert_int(cvector* const obj, int index, int value) {
  int new_size = cvector_size_ints(obj) + 1;
  cvector_resize_ints(obj, new_size);  // Will clobber extra bytes.
  for (int source_index = new_size - 1; source_index > index; source_index--) {
    cvector_set_int(obj, source_index, cvector_at_int(obj, source_index - 1));
  }
  cvector_set_int(obj, index, value);
}

void cvector_prepend_int(cvector* const obj, int value) {
  cvector_insert_int(obj, 0, value);
}

int cvector_pop_int(cvector* const obj) {
  int last_index = cvector_size_ints(obj) - 1;
  int value = cvector_at_int(obj, last_index);
  cvector_resize_ints(obj, last_index);
  return value;
}

void cvector_delete_int(cvector* const obj, int index) {
  int new_size = cvector_size_ints(obj) - 1;
  for (int source_index = new_size; source_index > index; source_index--) {
    cvector_set_int(obj, source_index - 1, cvector_at_int(obj, source_index));
  }
  cvector_resize_ints(obj, new_size);  // Will leave off extra bytes.
}

int cvector_size_bytes(const cvector* const obj) { return obj->size_bytes; }

void cvector_resize_bytes(cvector* const obj, const int size_bytes) {
  // If the new size is larger than the current capacity.
  if (size_bytes > obj->capacity_ints * sizeof(int)) {
    // Create new data space for data big enough.
    int new_capacity_ints =
        cvector_util_determine_min_capacity_ints_from_size_bytes(size_bytes);
    int* new_data = malloc(new_capacity_ints * sizeof(int));

    // Copy the old data to the new space.
    memcpy(new_data, obj->data, obj->size_bytes);

    // Free the old data space.
    free(obj->data);

    // Setup object with new data space.
    obj->data = new_data;
    obj->capacity_ints = new_capacity_ints;
  }

  // Wether we had to make more space or not, update the size.
  obj->size_bytes = size_bytes;
}

void cvector_set_byte(cvector* const obj, const int index, uint8_t byte) {
  if (index >= cvector_size_bytes(obj)) {
    cvector_resize_bytes(obj, index + 1);
  }
  *((uint8_t*)obj->data + index) = byte;
}

int cvector_util_round_up_to_power_of_two(int number) {
  if (number > 0) {
    number--;
    for (int shift = 1; shift <= sizeof(number) * 4; shift *= 2) {
      number |= number >> shift;
    }
    number++;
    return number;
  }
  return 1;
}

int cvector_util_determine_min_capacity_ints_from_size_bytes(int size_bytes) {
  int capacity = 0;
  if (size_bytes > 0) {
    int size_ints = size_bytes / sizeof(int);
    if (size_bytes % sizeof(int) > 0) {
      size_ints++;
    }
    capacity = cvector_util_round_up_to_power_of_two(size_ints);
  }
  return capacity;
}

uint8_t cvector_at_byte(const cvector* const obj, int index) {
  assert(obj->size_bytes > index);
  return *((uint8_t*)obj->data + index);
}

void cvector_push_byte(cvector* const obj, uint8_t value) {
  int new_index = cvector_size_bytes(obj);
  cvector_resize_bytes(obj, new_index + 1);
  cvector_set_byte(obj, new_index, value);
}

void cvector_insert_byte(cvector* const obj, int index, uint8_t value) {
  int new_size = cvector_size_bytes(obj) + 1;
  cvector_resize_bytes(obj, new_size);
  for (int source_index = new_size - 1; source_index > index; source_index--) {
    cvector_set_byte(obj, source_index, cvector_at_byte(obj, source_index - 1));
  }
  cvector_set_byte(obj, index, value);
}

void cvector_prepend_byte(cvector* const obj, int value) {
  cvector_insert_byte(obj, 0, value);
}

uint8_t cvector_pop_byte(cvector* const obj) {
  int last_index = cvector_size_bytes(obj) - 1;
  uint8_t value = cvector_at_byte(obj, last_index);
  cvector_resize_bytes(obj, last_index);
  return value;
}

void cvector_delete_byte(cvector* const obj, int index) {
  int new_size = cvector_size_bytes(obj) - 1;
  for (int source_index = new_size; source_index > index; source_index--) {
    cvector_set_byte(obj, source_index - 1, cvector_at_byte(obj, source_index));
  }
  cvector_resize_bytes(obj, new_size);  // Will leave off extra bytes.
}