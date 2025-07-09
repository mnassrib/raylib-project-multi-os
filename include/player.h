#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    float radius;
    Color color;
} Player;

Player CreatePlayer(void);
void UpdatePlayer(Player *p);
void DrawPlayer(Player p);

#endif
