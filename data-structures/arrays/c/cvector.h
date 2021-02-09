#ifndef DATA_STRUCTURES_ARRAYS_C_CVECTOR_H_
#define DATA_STRUCTURES_ARRAYS_C_CVECTOR_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
  int size;
  int capacity;
} cvector;

cvector *cvector_new();
void cvector_delete(cvector *obj);
int cvector_size(const cvector *obj);
void cvector_resize(cvector *obj, const int size);
int cvector_capacity(const cvector* obj);
bool cvector_is_empty(const cvector* obj);
uint8_t cvector_at(const cvector* obj, int index);


#endif // DATA_STRUCTURES_ARRAYS_C_CVECTOR_H_
