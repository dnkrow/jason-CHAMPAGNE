#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h> // Pour le type bool

// Dimensions du plateau, en caractères (bordure incluse)
#define BOARD_WIDTH 30   // Largeur totale (colonnes)
#define BOARD_HEIGHT 20  // Hauteur totale (lignes)

// Durée d'attente entre deux frames (en millisecondes)
#define TICK_MSEC 120

// Longueur maximale théorique du serpent (toutes les cases internes)
#define MAX_SNAKE_LENGTH ((BOARD_WIDTH - 2) * (BOARD_HEIGHT - 2))

// Représente une position 2D sur le plateau
typedef struct
{
    int x; // Colonne (0 à BOARD_WIDTH-1)
    int y; // Ligne   (0 à BOARD_HEIGHT-1)
} Point;

// Utilitaires sur les points/serpent
bool point_equals(Point a, Point b);                                  // Compare deux points
bool point_on_snake(Point p, Point snake[], int length);               // Teste la présence d'un point sur le serpent
Point random_food(Point snake[], int length);                          // Calcule une position de nourriture libre
Point move_snake(Point snake[], int length, Point new_head);           // Déplace le serpent et renvoie l'ancienne queue
void grow_snake(Point snake[], int *length, Point tail_segment);       // Ajoute un segment au serpent

#endif /* SNAKE_H */
