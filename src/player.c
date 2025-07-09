#include "player.h"
#include "raylib.h"

Player CreatePlayer(void) {
    Player p;
    p.position = (Vector2){400, 300};
    p.radius = 30;
    p.color = BLUE;
    return p;
}

void UpdatePlayer(Player *p) {
    if (IsKeyDown(KEY_RIGHT)) p->position.x += 5;
    if (IsKeyDown(KEY_LEFT))  p->position.x -= 5;
    if (IsKeyDown(KEY_UP))    p->position.y -= 5;
    if (IsKeyDown(KEY_DOWN))  p->position.y += 5;
}

void DrawPlayer(Player p) {
    DrawCircleV(p.position, p.radius, p.color);
}
