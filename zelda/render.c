#include "render.h"

#include <string.h>

static void draw_tile(int sy, int sx, char t) {
    chtype ch = ' ';
    attr_t attr = A_NORMAL;
    switch (t) {
        case TILE_GRASS: ch = '.'; attr = COLOR_PAIR(2); break;
        case TILE_WALL: ch = '#'; attr = COLOR_PAIR(7) | A_BOLD; break;
        case TILE_TREE: ch = 'T'; attr = COLOR_PAIR(3) | A_BOLD; break;
        case TILE_WATER: ch = '~'; attr = COLOR_PAIR(4) | A_BOLD; break;
        case TILE_DOOR_LOCKED: ch = 'D'; attr = COLOR_PAIR(1) | A_BOLD; break;
        case TILE_DOOR_OPEN: ch = 'O'; attr = COLOR_PAIR(6) | A_BOLD; break;
        case TILE_NPC: ch = 'N'; attr = COLOR_PAIR(5) | A_BOLD; break;
        case TILE_HEART: ch = 'H'; attr = COLOR_PAIR(1) | A_BOLD; break;
        case TILE_ARROW: ch = 'A'; attr = COLOR_PAIR(6) | A_BOLD; break;
        default: ch = t; break;
    }
    attron(attr);
    mvaddch(sy, sx, ch);
    attroff(attr);
}

static void init_colors_once(void) {
    static int inited = 0; if (inited) return; inited = 1;
    if (has_colors()) { start_color(); use_default_colors(); }
    init_pair(1, COLOR_RED, -1);     // hearts, locked door
    init_pair(2, COLOR_GREEN, -1);   // grass
    init_pair(3, COLOR_GREEN, -1);   // trees
    init_pair(4, COLOR_CYAN, -1);    // water
    init_pair(5, COLOR_YELLOW, -1);  // NPC / UI
    init_pair(6, COLOR_MAGENTA, -1); // open door / arrows
    init_pair(7, COLOR_WHITE, -1);   // walls
}

void game_render(Game* g) {
    init_colors_once();
    erase();
    int maxh, maxw; getmaxyx(stdscr, maxh, maxw);
    int view_h = maxh - 2; int view_w = maxw;
    // Draw map view window
    for (int sy = 0; sy < view_h; ++sy) {
        int wy = g->camera_y + sy; if (wy < 0 || wy >= MAP_H) continue;
        for (int sx = 0; sx < view_w; ++sx) {
            int wx = g->camera_x + sx; if (wx < 0 || wx >= MAP_W) continue;
            draw_tile(sy, sx, g->map[wy][wx]);
        }
    }
    // Draw enemies
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        Enemy* e = &g->enemies[i]; if (!e->alive) continue;
        int sx = e->x - g->camera_x; int sy = e->y - g->camera_y;
        if (sx>=0 && sy>=0 && sx<view_w && sy<view_h) {
            attron(COLOR_PAIR(7)|A_BOLD);
            mvaddch(sy, sx, (e->type==0)?'g':'r');
            attroff(COLOR_PAIR(7)|A_BOLD);
        }
    }
    // Draw player
    int psx = g->player.x - g->camera_x; int psy = g->player.y - g->camera_y;
    if (psx>=0 && psy>=0 && psx<view_w && psy<view_h) {
        attron(COLOR_PAIR(5)|A_BOLD);
        mvaddch(psy, psx, '@');
        attroff(COLOR_PAIR(5)|A_BOLD);
    }
    // Draw sword animation (simple red sweep of 3 tiles)
    if (g->sword_anim_time > 0.0) {
        int phase = (int)(g->sword_anim_time / 0.05); if (phase > 2) phase = 2; if (phase < 0) phase = 0;
        int sx = -1, sy = -1;
        if (g->sword_dx != 0) {
            // horizontal sweep
            int off = (g->sword_dx > 0) ? (phase - 1) : (1 - phase);
            sx = psx + off; sy = psy;
        } else {
            // vertical sweep
            int off = (g->sword_dy > 0) ? (phase - 1) : (1 - phase);
            sx = psx; sy = psy + off;
        }
        attron(COLOR_PAIR(1)|A_BOLD);
        if (g->sword_dx != 0) {
            for (int i = -1; i <= 1; ++i) {
                int bx = sx + i, by = sy;
                if (bx>=0 && by>=0 && bx<view_w && by<view_h) mvaddch(by, bx, '-');
            }
        } else {
            for (int i = -1; i <= 1; ++i) {
                int bx = sx, by = sy + i;
                if (bx>=0 && by>=0 && bx<view_w && by<view_h) mvaddch(by, bx, '|');
            }
        }
        attroff(COLOR_PAIR(1)|A_BOLD);
    }
    // Draw arrows
    for (int i = 0; i < MAX_ARROWS; ++i) {
        Arrow* a = &g->arrows[i]; if (!a->active) continue;
        int sx = (int)a->x - g->camera_x; int sy = (int)a->y - g->camera_y;
        if (sx>=0 && sy>=0 && sx<view_w && sy<view_h) {
            attron(COLOR_PAIR(6)|A_BOLD);
            mvaddch(sy, sx, '-');
            attroff(COLOR_PAIR(6)|A_BOLD);
        }
    }

    // UI panel bottom (2 lines)
    int y = view_h;
    attron(A_REVERSE);
    for (int x = 0; x < maxw; ++x) mvaddch(y, x, ' ');
    for (int x = 0; x < maxw; ++x) mvaddch(y+1, x, ' ');
    attroff(A_REVERSE);
    // Info: hearts, arrows, level, enemies remaining
    mvprintw(y, 1, "PV: %d/%d  Fleches: %d  Niveau: %d  Ennemis: %d", g->player.hp, g->player.max_hp, g->player.arrows, g->level, g->enemies_remaining);
    mvprintw(y+1, 1, "Deplacement: fleches  |  E: parler  |  Souris: gauche=epee, droite=arc  |  Q: quitter");
    if (g->message_timer > 0.0 && strlen(g->message)>0) {
        int len = (int)strlen(g->message);
        int startx = maxw - len - 2; if (startx < 0) startx = 0;
        mvprintw(y, startx, "%s", g->message);
    }

    refresh();
}
