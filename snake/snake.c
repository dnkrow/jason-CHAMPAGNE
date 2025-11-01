#include "snake.h"   // Déclarations partagées: types, constantes et prototypes

#include <stdlib.h>   // rand

// Compare deux points pour l'égalité de coordonnées
bool point_equals(Point a, Point b)
{
    return a.x == b.x && a.y == b.y; // Vrai si mêmes x et y
}

// Indique si le point p est sur l'un des segments du serpent
bool point_on_snake(Point p, Point snake[], int length)
{
    for (int i = 0; i < length; ++i)   // Parcourt tous les segments
    {
        if (point_equals(p, snake[i])) // Test d'égalité avec le segment i
        {
            return true;               // Trouvé: p est sur le serpent
        }
    }
    return false;                      // Non trouvé: p est libre
}

// Génère une position aléatoire pour la nourriture, à l'intérieur de la bordure,
// en évitant toute case occupée par le serpent.
Point random_food(Point snake[], int length)
{
    Point food;                        // Candidat nourriture
    do
    {
        // bornes [1 .. BOARD_WIDTH-2] et [1 .. BOARD_HEIGHT-2] pour rester dans la bordure
        food.x = (rand() % (BOARD_WIDTH - 2)) + 1;
        food.y = (rand() % (BOARD_HEIGHT - 2)) + 1;
    } while (point_on_snake(food, snake, length)); // Re-tire tant que sur le serpent
    return food;                      // Position valide
}

// Déplace le serpent en insérant la nouvelle tête et en décalant les segments
// Retourne l'ancien segment de queue (utile pour grandir ensuite)
Point move_snake(Point snake[], int length, Point new_head)
{
    Point old_tail = snake[length - 1];   // Sauvegarde l'ancienne queue
    for (int i = length - 1; i > 0; --i)  // Décale les segments vers l'arrière
    {
        snake[i] = snake[i - 1];          // Le segment i prend la place du précédent
    }
    snake[0] = new_head;                   // Insère la nouvelle tête en [0]
    return old_tail;                       // Renvoie l'ancienne queue
}

// Fait grandir le serpent d'un segment en réutilisant l'ancien bout de queue
void grow_snake(Point snake[], int *length, Point tail_segment)
{
    if (*length < MAX_SNAKE_LENGTH)        // Ne pas dépasser la capacité
    {
        snake[*length] = tail_segment;     // Ajoute un segment identique à l'ancienne queue
        (*length)++;                        // Incrémente la longueur
    }
}
