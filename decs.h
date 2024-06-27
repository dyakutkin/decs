/*Dumb ECS.*/

#include "components.h"

#define DECS_ENTITIES_MAX 8000000

#define DECS_sys(name) void name(ComponentsStore *components_store)
#define DECS_eiter() for (int entity_id = 0; entity_id < DECS_ENTITIES_MAX; entity_id++)
#define DECS_q(predicates) \
    if (!(predicates))     \
        continue;

/*Entity's component fetching helper.*/
#define DECS_ec(component_type_name) components_store->component_type_name[entity_id]

#define DECS_register_component(component_type_name, store_name)                                  \
    component_type_name **store_name = malloc(sizeof(component_type_name *) * DECS_ENTITIES_MAX); \
    do                                                                                            \
    {                                                                                             \
        for (int i = 0; i < DECS_ENTITIES_MAX; i++)                                               \
        {                                                                                         \
            store_name[i] = NULL;                                                                 \
        }                                                                                         \
        components_store->component_type_name = store_name;                                       \
    } while (0)

typedef struct
{
    PersonComponent **PersonComponent;
    PositionComponent **PositionComponent;
    PlayerComponent **PlayerComponent;
} ComponentsStore;
