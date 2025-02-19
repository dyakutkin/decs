#pragma once

#include <stdbool.h>
#include <stdint.h>

#define component(component_name, ...) .component_name = {._base.is_set = true, __VA_ARGS__}

typedef struct {
  bool is_set;
} BaseComponent;

bool BaseComponent__is_set(void *c);

typedef struct {
  BaseComponent _base;
  char *name;
} PersonComponent;

typedef struct {
  BaseComponent _base;
  int32_t x;
  int32_t y;
} PositionComponent;

typedef struct {
  BaseComponent _base;
} PlayerComponent;
