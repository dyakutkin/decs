#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ArrayListStruct(elem_type)                                             \
  struct {                                                                     \
    size_t cap;                                                                \
    size_t len;                                                                \
    size_t elem_size;                                                          \
    elem_type *data;                                                           \
  }

#define ArrayList(elem_type) ArrayList_##elem_type
#define ArrayList_define(elem_type)                                            \
  typedef ArrayListStruct(elem_type) ArrayList(elem_type)

ArrayList_define(void);

#define ArrayList_new(var_name, type, init_cap)                                \
  ArrayList(type) var_name = {0};                                              \
  _ArrayList_init((ArrayList(void) *)&var_name, sizeof(type), init_cap)

#define ArrayList_append(list, value)                                          \
  _ArrayList_append((ArrayList(void) *)&list, &value)

#define ArrayList_free(self) _ArrayList_free((ArrayList(void) *)&self)
#define ArrayList_trim_back(self) _ArrayList_trim_back((ArrayList(void) *)&self)

void _ArrayList_init(ArrayList(void) * self, size_t elem_size, size_t init_cap);
void _ArrayList_append(ArrayList(void) * self, void *element);
void _ArrayList_free(ArrayList(void) * self);
void _ArrayList_clear(ArrayList(void) * self);
void _ArrayList_trim_back(ArrayList(void) * self);

ArrayList_define(int);
ArrayList_define(size_t);
