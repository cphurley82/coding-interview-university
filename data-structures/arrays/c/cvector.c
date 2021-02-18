#include "data-structures/arrays/c/cvector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

cvector *cvector_new() {
  cvector *obj = malloc(sizeof(cvector));
  obj->size_ints = 0;
  obj->capacity_ints = 0;
  obj->data = NULL;
  return obj;
}

void cvector_delete(cvector *const obj) { free(obj); }

int cvector_size_ints(const cvector *const obj) { return obj->size_ints; }

void cvector_resize_ints(cvector *const obj, const int size_ints) {
  // If the new size is larger than the current capacity.
  if (size_ints > obj->capacity_ints) {
    // Create new data space for data big enough.
    int new_capacity_ints = cvector_round_up_to_power_of_two(size_ints);
    int *new_data = malloc(new_capacity_ints);

    // Copy the old data to the new space.
    memcpy(new_data, obj->data, obj->size_ints);

    // Free the old data space.
    free(obj->data);

    // Setup object with new data space.
    obj->data = new_data;
    obj->capacity_ints = size_ints;
  }

  // Wether we had to make more space or not, update the size.
  obj->size_ints = size_ints;
}

int cvector_capacity_ints(const cvector *const obj) {
  return obj->capacity_ints;
}

bool cvector_is_empty(const cvector *const obj) {
  return obj->size_ints == 0 ? true : false;
}

uint8_t cvector_at_int(const cvector *const obj, int index) {
  assert(obj->size_ints > index * sizeof(int));
  return obj->data[index];
}

void cvector_set_int(cvector *const obj, const int index, const int value) {
  if (index * sizeof(int) >= obj->size_ints) {
    cvector_resize_ints(obj, index + sizeof(int));
  }
  obj->data[index] = value;
}

int cvector_round_up_to_power_of_two(int number) {
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