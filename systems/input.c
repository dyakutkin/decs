#include <raylib.h>

#include "../events.h"

#include "input.h"

bool input_system(AList *events, EntityID player_id) {
  int x, y;
  bool got_input;
  if (IsKeyDown(KEY_RIGHT)) {
    x = 1;
    y = 0;
    got_input = true;
  }
  AList__append(events, &(MoveEvent){
                            .delta = (VecDelta){.x = x, .y = y},
                            .entity_id = player_id,
                        });
  return got_input;
}
