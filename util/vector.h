struct Vector {
  void *data;
  size_t element_size;
  size_t capacity;
  size_t len;
};

struct Vector *vec_create(const size_t element_size, const size_t initial_capacity);
//Append an element to the end of the vector
void vec_push(struct Vector *vec, const void *const item);

//Set index `index` in the vector to item, reallocating if necessary
void vec_set(struct Vector *vec, const void *const item, const size_t index);

//Get the item at index `index`. Returns NULL if no element is present
void *vec_get(struct Vector *vec, size_t const index);
