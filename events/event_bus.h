#include <stdlib.h>

#define CONCAT(x, y) x##y
#define CONCAT3(x, y, z) x##y##z

// Placeholder type to avoid static analysis errors.
#ifndef TYPE
#define TYPE char
#endif

#define AList(T) CONCAT(AList_, T)
typedef struct {
  TYPE *events;
  size_t len;
  size_t cap;
} AList(TYPE);

#define ALIST_ALLOC(T) CONCAT3(AList_, T, __alloc)
AList(TYPE) ALIST_ALLOC(TYPE)(size_t init_cap) {
  return (AList(TYPE)){
      .events = (TYPE *)malloc(init_cap * sizeof(TYPE)),
      .len = 0,
      .cap = init_cap,
  };
}

#define ALIST_FREE(T) CONCAT3(AList_, T, __free)
void ALIST_FREE(TYPE)(AList(TYPE) *self) {
  free(self->events);
}

#define ALIST_APPEND(T) CONCAT3(AList_, T, __append)
void ALIST_APPEND(TYPE)(AList(TYPE) * self, TYPE value) {
  if (self->len == self->cap) {
    size_t new_cap = self->cap * 2;
    self->events = (TYPE *)realloc(self->events, sizeof(TYPE) * new_cap);
  }
  self->events[self->len] = value;
  self->len++;
}

#define ALIST_CLEAR(T) CONCAT3(AList_, T, __clear)
void ALIST_CLEAR(TYPE)(AList(TYPE) *self) {
  ALIST_FREE(TYPE)(self);
  self->events =  (TYPE *)malloc(self->cap* sizeof(TYPE));
  self->len = 0;
}

