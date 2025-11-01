#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h> // API d'affichage terminal
#include "snake.h"   // Types et dimensions du plateau

// Fonctions de dessin basées sur ncurses
void draw_border(void);                   // Bordures du plateau
void draw_snake(Point snake[], int length); // Serpent (tête + corps)
void draw_food(Point food);               // Nourriture
void draw_hud(int score);                 // HUD (score & aide)
void draw_game_over(int score);           // Écran de fin

#endif /* RENDER_H */
