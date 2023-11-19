#pragma once

#include <stdbool.h>
#include "mechanics/mechanics.h"
#include "ui/controls.h"

typedef struct {
    bool gameover;
    Vector2 player_start_position;
} S_GAME_DATA ;

extern S_GAME_DATA GAME_DATA;