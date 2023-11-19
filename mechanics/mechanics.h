#pragma once

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    int x;
    int y;
} Vector2Int;

typedef struct {
    Vector2 position;
    Vector2 velocity;
} Object;

void init_mechanics();
