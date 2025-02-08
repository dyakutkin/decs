#pragma once

#include "entity.h"
#include "stdio.h"
#include "stdlib.h"

#define MAX_ENTITIES 100
#define MAX_ARCHETYPES 100

typedef struct {
  Entity entities[MAX_ENTITIES];
} BaseEntityStore;

typedef struct {
  BaseEntityStore *store;
  bool (*matcher)(Entity *e);
} Arch;

typedef struct {
  BaseEntityStore _base;
  Arch **archetypes;
  size_t archetypes_amount;
} EntityStore;

EntityStore EntityStore__new();

bool EntityStore__register_arch(EntityStore *self, Arch *arch);
