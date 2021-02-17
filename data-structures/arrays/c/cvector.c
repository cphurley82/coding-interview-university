#include "data-structures/arrays/c/cvector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

cvector *cvector_new() {
  cvector *obj = malloc(sizeof(cvector));
  obj->size_bytes = 0;
  obj->capacity_bytes = 0;
  obj->data = NULL;
  return obj;
}

void cvector_delete(cvector *const obj) { free(obj); }

int cvector_size(const cvector *const obj) { return obj->size_bytes; }

void cvector_resize(cvector *const obj, const int size_bytes) {
  // If the new size is larger than the current capacity.
  if (size_bytes > obj->capacity_bytes) {
    // Create new data space for data big enough.
    int new_capacity = size_bytes / sizeof(int) + sizeof(int);
    int *new_data = malloc(new_capacity);

    // Copy the old data to the new space.
    memcpy(new_data, obj->data, obj->size_bytes);

    // Free the old data space.
    free(obj->data);

    // Setup object with new data space.
    obj->data = new_data;
    obj->capacity_bytes = new_capacity;
  }

  // Wether we had to make more space or not, update the size.
  obj->size_bytes = size_bytes;
}

int cvector_capacity(const cvector *const obj) { return obj->capacity_bytes; }

bool cvector_is_empty(const cvector *const obj) {
  return obj->size_bytes == 0 ? true : false;
}

uint8_t cvector_at(const cvector *const obj, int index) {
  assert(obj->size_bytes > index * sizeof(int));
  return obj->data[index];
}

void cvector_set(cvector *const obj, const int index, const int value) {
  if (index * sizeof(int) >= obj->size_bytes) {
    cvector_resize(obj, index + sizeof(int));
  }
  obj->data[index] = value;
}