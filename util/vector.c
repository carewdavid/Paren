#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"

struct Vector *vec_create(const size_t element_size, const size_t initial_capacity){
  assert(element_size > 0);
  assert(initial_capacity > 0);
  struct Vector *vec = malloc(sizeof(struct Vector));
  assert(vec);
  vec->data = malloc(element_size * initial_capacity);
  assert(vec->data);
  memset(vec->data, 0, element_size * initial_capacity);
  vec->element_size = element_size;
  vec->capacity = initial_capacity;
  vec->len = 0;

  return vec;
}
  
static struct Vector *grow_vector(struct Vector *vec){
  vec->capacity *= 2;
  vec->data = realloc(vec->data, vec->capacity);
  return vec;
}

//Set index `index` in the vector to item, reallocating if necessary
void vec_set(struct Vector *vec, const void *const item, const size_t index){
  assert(vec);
  if(vec->len == vec->capacity){
    vec = grow_vector(vec);
  }
  memcpy(vec->data, item, vec->element_size);
}


//Append an element to the end of the vector
void vec_push(struct Vector *vec, const void *const item){
  vec_set(vec, item, vec->len);
  vec->len++;
}


//Get the item at index `index`. Returns NULL if no element is present
void *vec_get(struct Vector *vec, size_t const index){
  assert(vec);
  assert(index >= 0);
  assert(index < vec->len);
  char *buf = vec->data;
  return buf + (vec->element_size * index);
}
