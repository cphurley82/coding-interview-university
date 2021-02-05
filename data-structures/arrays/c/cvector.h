#ifndef DATA_STRUCTURES_ARRAYS_C_CVECTOR_H_
#define DATA_STRUCTURES_ARRAYS_C_CVECTOR_H_

typedef struct {
  int size;
} cvector;


cvector* cvector_new();

int cvector_size(cvector* obj);

#endif // DATA_STRUCTURES_ARRAYS_C_CVECTOR_H_
