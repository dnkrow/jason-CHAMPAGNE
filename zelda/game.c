// Core game logic
#include "game.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

static int clampi(int v, int lo, int hi) { if (v < lo) return lo; if (v > hi) return hi; return v; }

static int is_blocking(char t) {
    return (t == TILE_WALL || t == TILE_TREE || t == TILE_WATER || t == TILE_DOOR_LOCKED);
}

static void message(Game* g, const char* msg) {
    strncpy(g->message, msg, sizeof(g->message)-1);
    g->message[sizeof(g->message)-1] = 0;
    g->message_timer = 2.5;
}

static void clear_map(Game* g) {
    for (int y = 0; y < MAP_H; ++y) {
        for (int x = 0; x < MAP_W; ++x) {
            g->map[y][x] = TILE_GRASS;
        }
    }
}

static void generate_level(Game* g) {
    clear_map(g);
    // Borders
    for (int x = 0; x < MAP_W; ++x) { g->map[0][x] = TILE_WALL; g->map[MAP_H-1][x] = TILE_WALL; }
    for (int y = 0; y < MAP_H; ++y) { g->map[y][0] = TILE_WALL; g->map[y][MAP_W-1] = TILE_WALL; }

    // Random decor: trees and water patches
    for (int i = 0; i < 400 + g->level * 15; ++i) {
        int x = 1 + rand() % (MAP_W-2);
        int y = 1 + rand() % (MAP_H-2);
        char t = (rand()%100 < 60) ? TILE_TREE : TILE_WATER;
        // scatter small blobs
        for (int dy = -1; dy <= 1; ++dy) for (int dx = -1; dx <= 1; ++dx) {
            int xx = clampi(x+dx, 1, MAP_W-2); int yy = clampi(y+dy, 1, MAP_H-2);
            if (rand()%100 < 50) g->map[yy][xx] = t;
        }
    }

    // Carve spawn area at bottom center
    int sx0 = MAP_W/2 - 6, sy0 = MAP_H - 12;
    for (int y = sy0; y < sy0 + 10; ++y) {
        for (int x = sx0; x < sx0 + 12; ++x) g->map[y][x] = TILE_GRASS;
    }

    // Door at top center (locked initially)
    int door_x = MAP_W/2; // just under the border wall
    g->map[0][door_x] = TILE_WALL;
    g->map[1][door_x] = TILE_DOOR_LOCKED;

    // Place NPC only on level 1 near spawn
    if (g->level == 1) {
        g->map[sy0+3][MAP_W/2] = TILE_NPC;
    }
}

static void place_player(Game* g) {
    // Place near bottom center in cleared area
    g->player.x = MAP_W/2;
    g->player.y = MAP_H - 8;
    g->player.facing_x = 0; g->player.facing_y = -1;
}

static void spawn_enemies(Game* g) {
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        g->enemies[i].alive = false;
    }
    int to_spawn = 6 + g->level * 4;
    if (to_spawn > MAX_ENEMIES) to_spawn = MAX_ENEMIES;
    int count = 0; int attempts = 0;
    while (count < to_spawn && attempts < to_spawn * 50) {
        ++attempts;
        int x = 2 + rand() % (MAP_W-4);
        int y = 2 + rand() % (MAP_H-20); // avoid bottom spawn area
        if (!is_blocking(g->map[y][x])) {
            // Choose type
            int type = (rand()%100 < 50) ? 0 : 1;
            g->enemies[count].x = x; g->enemies[count].y = y;
            g->enemies[count].type = type;
            g->enemies[count].hp = (type==0)?2:1;
            g->enemies[count].alive = true;
            g->enemies[count].move_timer = 0.0;
            ++count;
        }
    }
    g->enemies_remaining = count;
}

static void clear_arrows(Game* g) { for (int i = 0; i < MAX_ARROWS; ++i) g->arrows[i].active = false; }

void game_init(Game* g) {
    memset(g, 0, sizeof(*g));
    g->level = 1;
    g->player.max_hp = 3;
    g->player.hp = g->player.max_hp;
    g->player.arrows = 5;
    g->player.sword_cooldown = 0.0;
    g->dialog_active = false;
    g->sword_anim_time = 0.0; g->sword_dx = 0; g->sword_dy = -1;
    generate_level(g);
    place_player(g);
    spawn_enemies(g);
    clear_arrows(g);
    message(g, "Niveau 1: parle au PNJ (E) et va vers le haut.");
}

static void center_camera(Game* g) {
    int maxh, maxw; getmaxyx(stdscr, maxh, maxw);
    int view_h = maxh - 2; int view_w = maxw;
    int cx = g->player.x - view_w/2;
    int cy = g->player.y - view_h/2;
    g->camera_x = clampi(cx, 0, MAP_W - view_w);
    g->camera_y = clampi(cy, 0, MAP_H - view_h);
}

static int can_move_to(Game* g, int x, int y) {
    x = clampi(x, 0, MAP_W-1); y = clampi(y, 0, MAP_H-1);
    if (is_blocking(g->map[y][x])) return 0;
    // Block moving into NPC tile to help interaction
    if (g->map[y][x] == TILE_NPC) return 0;
    return 1;
}

static void try_move_player(Game* g, int dx, int dy) {
    if (dx==0 && dy==0) return;
    int nx = g->player.x + dx;
    int ny = g->player.y + dy;
    g->player.facing_x = dx; g->player.facing_y = dy;
    if (nx < 0 || ny < 0 || nx >= MAP_W || ny >= MAP_H) return;
    char t = g->map[ny][nx];
    if (t == TILE_DOOR_LOCKED) {
        if (g->enemies_remaining > 0) {
            message(g, "Porte verrouillée: élimine tous les monstres !");
            return;
        } else {
            // Open and advance
            g->map[ny][nx] = TILE_DOOR_OPEN;
            g->door_open = true;
            // Move into door triggers level change
            g->player.x = nx; g->player.y = ny;
            // Advance level after a short message
            g->level++;
            if (g->level > 10) {
                g->quit = true;
                message(g, "Bravo ! Tu as sauvé la princesse !");
                return;
            }
            generate_level(g);
            place_player(g);
            spawn_enemies(g);
            clear_arrows(g);
            message(g, "Nouveau niveau !");
            return;
        }
    }
    if (can_move_to(g, nx, ny)) { g->player.x = nx; g->player.y = ny; }
}

static void interact(Game* g) {
    // Check adjacent tiles for NPC
    for (int dy=-1; dy<=1; ++dy) for (int dx=-1; dx<=1; ++dx) {
        if (abs(dx)+abs(dy) != 1) continue;
        int nx = g->player.x + dx, ny = g->player.y + dy;
        if (nx<0||ny<0||nx>=MAP_W||ny>=MAP_H) continue;
        if (g->map[ny][nx] == TILE_NPC) {
            g->dialog_active = true;
            if (g->level == 1) {
                message(g, "PNJ: Avance vers le haut, tue tous les monstres et sauve la princesse !");
            } else {
                message(g, "PNJ: Courage, la princesse t'attend plus haut !");
            }
            return;
        }
    }
}

static void sword_attack(Game* g, int tx, int ty) {
    // Attack on adjacent tile in direction towards (tx,ty). Fallback to facing direction.
    int dx = 0, dy = 0;
    if (tx >= 0 && ty >= 0) {
        int vx = tx - g->player.x; int vy = ty - g->player.y;
        if (abs(vx) > abs(vy)) { dx = (vx>0)?1:-1; dy = 0; }
        else if (abs(vy) > 0) { dy = (vy>0)?1:-1; dx = 0; }
    }
    if (dx==0 && dy==0) { dx = g->player.facing_x; dy = g->player.facing_y; if (dx==0 && dy==0) dy=-1; }
    // record swing for animation
    g->sword_dx = dx; g->sword_dy = dy; g->sword_anim_time = 0.001;
    int ax = g->player.x + dx; int ay = g->player.y + dy;
    // Damage enemies on that tile
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        if (!g->enemies[i].alive) continue;
        if (g->enemies[i].x == ax && g->enemies[i].y == ay) {
            g->enemies[i].hp -= 1;
            if (g->enemies[i].hp <= 0) {
                g->enemies[i].alive = false;
                g->enemies_remaining--;
                // Drop chance depending on type
                int r = rand()%100;
                if (g->enemies[i].type == 0) {
                    if (r < 25) g->map[ay][ax] = TILE_HEART;
                } else {
                    if (r < 12) g->map[ay][ax] = TILE_ARROW;
                }
                if (g->enemies_remaining <= 0) {
                    message(g, "La porte s'ouvrira maintenant !");
                    // Turn door to open
                    for (int x=0;x<MAP_W;++x) if (g->map[1][x]==TILE_DOOR_LOCKED) g->map[1][x] = TILE_DOOR_OPEN;
                }
            }
        }
    }
}

static void fire_arrow(Game* g, int tx, int ty) {
    if (g->player.arrows <= 0) { message(g, "Plus de flèches !"); return; }
    // Direction towards target (normalize to 8-dir unit step)
    int vx = (tx>=0? tx : g->player.x + g->player.facing_x) - g->player.x;
    int vy = (ty>=0? ty : g->player.y + g->player.facing_y) - g->player.y;
    if (vx==0 && vy==0) { vx = g->player.facing_x; vy = g->player.facing_y; if (vx==0 && vy==0) { vy=-1; } }
    double len = sqrt((double)(vx*vx + vy*vy));
    if (len < 0.001) return;
    double dx = vx/len; double dy = vy/len;
    // Find slot
    for (int i = 0; i < MAX_ARROWS; ++i) {
        if (!g->arrows[i].active) {
            g->arrows[i].active = true;
            g->arrows[i].x = g->player.x + 0.5;
            g->arrows[i].y = g->player.y + 0.5;
            g->arrows[i].dx = dx * 20.0/60.0; // ~20 tiles/sec
            g->arrows[i].dy = dy * 20.0/60.0;
            g->player.arrows--;
            return;
        }
    }
}

static void pickup(Game* g) {
    char t = g->map[g->player.y][g->player.x];
    if (t == TILE_HEART) {
        if (g->player.hp < g->player.max_hp) {
            g->player.hp++;
            g->map[g->player.y][g->player.x] = TILE_GRASS;
            message(g, "+1 coeur");
        }
    } else if (t == TILE_ARROW) {
        g->player.arrows += 5;
        if (g->player.arrows > 99) g->player.arrows = 99;
        g->map[g->player.y][g->player.x] = TILE_GRASS;
        message(g, "+5 flèches");
    }
}

static void update_enemies(Game* g, double dt) {
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        Enemy* e = &g->enemies[i];
        if (!e->alive) continue;
        e->move_timer += dt;
        double pace = (e->type==1) ? 0.15 : 0.30; // runners move faster
        if (e->move_timer >= pace) {
            e->move_timer = 0.0;
            int dx=0, dy=0;
            if (abs(g->player.x - e->x) > abs(g->player.y - e->y)) dx = (g->player.x > e->x)?1:-1;
            else dy = (g->player.y > e->y)?1:-1;
            int nx = e->x + dx, ny = e->y + dy;
            if (nx==g->player.x && ny==g->player.y) {
                if (g->player.hurt_timer <= 0.0) {
                    g->player.hp -= 1;
                    g->player.hurt_timer = 0.6;
                    message(g, "Aïe !");
                    if (g->player.hp <= 0) {
                        g->quit = true;
                        message(g, "Game Over :(");
                        return;
                    }
                }
            } else if (!is_blocking(g->map[ny][nx])) {
                // Avoid stepping on items to not block player pickup
                if (g->map[ny][nx] != TILE_HEART && g->map[ny][nx] != TILE_ARROW && g->map[ny][nx] != TILE_NPC)
                    { e->x = nx; e->y = ny; }
            }
        }
    }
}

static void update_arrows(Game* g) {
    for (int i = 0; i < MAX_ARROWS; ++i) {
        Arrow* a = &g->arrows[i];
        if (!a->active) continue;
        double nx = a->x + a->dx;
        double ny = a->y + a->dy;
        int tx = (int)nx; int ty = (int)ny;
        if (tx < 0 || ty < 0 || tx >= MAP_W || ty >= MAP_H || is_blocking(g->map[ty][tx])) {
            a->active = false; continue;
        }
        // Hit enemy?
        for (int j = 0; j < MAX_ENEMIES; ++j) {
            Enemy* e = &g->enemies[j]; if (!e->alive) continue;
            if (e->x == tx && e->y == ty) {
                e->hp -= 1; a->active = false;
                if (e->hp <= 0) {
                    e->alive = false; g->enemies_remaining--;
                    int r = rand()%100;
                    if (e->type == 0) { if (r < 25) g->map[ty][tx] = TILE_HEART; }
                    else { if (r < 12) g->map[ty][tx] = TILE_ARROW; }
                    if (g->enemies_remaining <= 0) {
                        message(g, "La porte s'ouvrira maintenant !");
                        for (int x=0;x<MAP_W;++x) if (g->map[1][x]==TILE_DOOR_LOCKED) g->map[1][x] = TILE_DOOR_OPEN;
                    }
                }
                break;
            }
        }
        if (a->active) { a->x = nx; a->y = ny; }
    }
}

void game_update(Game* g, double dt) {
    // Timers
    if (g->player.sword_cooldown > 0.0) g->player.sword_cooldown -= dt;
    if (g->player.hurt_timer > 0.0) g->player.hurt_timer -= dt;
    if (g->message_timer > 0.0) g->message_timer -= dt;
    if (g->sword_anim_time > 0.0) { g->sword_anim_time += dt; if (g->sword_anim_time > 0.15) g->sword_anim_time = 0.0; }

    // Input: movement
    int mdx=0, mdy=0;
    if (g->input.key[INPUT_UP]) { mdy = -1; }
    else if (g->input.key[INPUT_DOWN]) { mdy = 1; }
    else if (g->input.key[INPUT_LEFT]) { mdx = -1; }
    else if (g->input.key[INPUT_RIGHT]) { mdx = 1; }
    try_move_player(g, mdx, mdy);

    if (g->input.key[INPUT_INTERACT]) interact(g);

    // Mouse attacks
    if (g->input.left_click && g->player.sword_cooldown <= 0.0) {
        sword_attack(g, g->input.mouse_world_x, g->input.mouse_world_y);
        g->player.sword_cooldown = 0.25; // 250ms
    }
    if (g->input.right_click) {
        fire_arrow(g, g->input.mouse_world_x, g->input.mouse_world_y);
    }

    // Pick up items underfoot
    pickup(g);

    // Update entities
    update_enemies(g, dt);
    update_arrows(g);

    // Center camera each frame
    center_camera(g);
}
