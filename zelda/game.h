// Core game types and API
#pragma once
#include <ncurses.h>

#include <stdbool.h>

#define MAP_W 100
#define MAP_H 100

#define MAX_ENEMIES 128
#define MAX_ARROWS 128
#define MAX_MESSAGES 4

// Input indices
enum { INPUT_UP=0, INPUT_DOWN, INPUT_LEFT, INPUT_RIGHT, INPUT_INTERACT };

typedef enum {
    TILE_GRASS='.',
    TILE_WALL ='#',
    TILE_TREE ='T',
    TILE_WATER='~',
    TILE_DOOR_LOCKED='D',
    TILE_DOOR_OPEN='O',
    TILE_NPC='N',
    TILE_HEART='h',
    TILE_ARROW='a'
} Tile;

typedef struct {
    int x, y;
    int hp;            // 1..?
    int type;          // 0=melee(heart dropper), 1=runner(arrow dropper)
    bool alive;
    double move_timer; // for pacing movement
} Enemy;

typedef struct {
    double x, y;  // sub-tile
    double dx, dy; // direction steps
    bool active;
} Arrow;

typedef struct {
    int key[8];
    int left_click;   // sword
    int right_click;  // bow
    int mouse_world_x;
    int mouse_world_y;
} InputState;

typedef struct {
    int x, y;
    int facing_x, facing_y; // last movement or aiming dir
    int hp;        // hearts
    int max_hp;
    int arrows;    // inventory
    double sword_cooldown;
    double hurt_timer; // invulnerability window
} Player;

typedef struct {
    // World
    char map[MAP_H][MAP_W];
    int level;        // 1..10
    int enemies_remaining;
    bool door_open;
    bool quit;

    // Camera top-left in world coords
    int camera_x, camera_y;

    // Entities
    Player player;
    Enemy enemies[MAX_ENEMIES];
    Arrow arrows[MAX_ARROWS];

    // Input
    InputState input;

    // UI / messages
    char message[128];
    double message_timer;
    bool dialog_active;

    // Sword animation (cheap sweep over 3 tiles)
    int sword_dx, sword_dy;     // last swing direction
    double sword_anim_time;     // 0..0.15 active
} Game;

void game_init(Game* g);
void game_update(Game* g, double dt);
void game_render(Game* g);
