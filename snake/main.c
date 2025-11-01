//
// Fichier: main.c
// Rôle: point d'entrée du jeu Snake. Initialise ncurses,
//       gère la boucle de jeu (entrée, logique, rendu),
//       puis nettoie et quitte proprement.
//

#include <ncurses.h>   // Bibliothèque pour l'affichage en texte (ncurses)
#include <stdbool.h>   // Booléens true/false
#include <stdlib.h>    // srand, rand
#include <time.h>      // time pour initialiser le RNG

#include "render.h"   // Déclarations des fonctions de rendu
#include "snake.h"    // Constantes, types et logique du serpent

int main(void)
{
	// --- Initialisation de ncurses ---
	initscr();                  // Initialise l'écran ncurses
	cbreak();                   // Mode cbreak: lecture caractère par caractère
	noecho();                   // Ne pas afficher les touches tapées
	curs_set(0);                // Cache le curseur
	keypad(stdscr, true);       // Active les touches spéciales (flèches, etc.)
	nodelay(stdscr, true);      // getch() devient non bloquant

	// --- Initialisation du générateur aléatoire ---
	srand((unsigned int)time(NULL)); // Graine aléatoire basée sur l'heure

	// --- État initial du jeu ---
	Point snake[MAX_SNAKE_LENGTH]; // Tableau contenant les segments du serpent
	int snake_length = 4;           // Longueur initiale du serpent
	int dx = 1;                     // Direction horizontale (+1 = droite)
	int dy = 0;                     // Direction verticale (0 = immobile verticalement)

	// Positionner le serpent au centre, horizontalement vers la gauche
	for (int i = 0; i < snake_length; ++i)
	{
		// Début de la boucle d'initialisation des segments
		snake[i].x = BOARD_WIDTH / 2 - i; // Décale chaque segment d'une colonne
		snake[i].y = BOARD_HEIGHT / 2;    // Même ligne pour tous les segments
	}
	// Fin de la boucle d'initialisation

	Point food = random_food(snake, snake_length); // Génère une nourriture hors du serpent
	int score = 0;                                  // Score de départ
	bool running = true;                            // Drapeau de boucle de jeu

	// --- Boucle principale du jeu ---
	while (running)
	{
		int ch = getch(); // Lecture non bloquante de la dernière touche
		switch (ch)       // Gestion du contrôle du serpent
		{
		case KEY_UP:      // Flèche haut
		case 'w':         // w/W (ZQSD ou WASD)
		case 'W':
			if (dy != 1)    // Empêche l'inversion immédiate (pas de 180°)
			{
				dx = 0;       // Déplacement vertical uniquement
				dy = -1;      // Vers le haut
			}
			break;           // Fin du cas "haut"
		case KEY_DOWN:    // Flèche bas
		case 's':
		case 'S':
			if (dy != -1)   // Pas d'inversion directe vers le bas
			{
				dx = 0;       // Déplacement vertical uniquement
				dy = 1;       // Vers le bas
			}
			break;           // Fin du cas "bas"
		case KEY_LEFT:    // Flèche gauche
		case 'a':
		case 'A':
			if (dx != 1)    // Pas d'inversion directe vers la gauche
			{
				dx = -1;      // Vers la gauche
				dy = 0;       // Déplacement horizontal uniquement
			}
			break;           // Fin du cas "gauche"
		case KEY_RIGHT:   // Flèche droite
		case 'd':
		case 'D':
			if (dx != -1)   // Pas d'inversion directe vers la droite
			{
				dx = 1;       // Vers la droite
				dy = 0;       // Déplacement horizontal uniquement
			}
			break;           // Fin du cas "droite"
		case 'q':         // Quitter
		case 'Q':
			running = false; // Sortir proprement de la boucle
			continue;        // Passe au test de boucle suivant
		default:
			break;            // Aucune touche pertinente: ne rien faire
		}

		// Calcul de la nouvelle tête en appliquant (dx, dy)
		Point new_head = {snake[0].x + dx, snake[0].y + dy};

		// --- Détection des collisions ---
		if (new_head.x <= 0 || new_head.x >= BOARD_WIDTH - 1 ||
			new_head.y <= 0 || new_head.y >= BOARD_HEIGHT - 1 ||
			point_on_snake(new_head, snake, snake_length))
		{
			// Collision avec un mur ou avec soi-même: fin de partie
			running = false;
			break; // Quitte la boucle de jeu
		}

		// Déplace le serpent: insère la nouvelle tête et récupère l'ancienne queue
		Point old_tail = move_snake(snake, snake_length, new_head);

		// --- Gestion de la nourriture ---
		if (point_equals(new_head, food))
		{
			grow_snake(snake, &snake_length, old_tail); // Ajoute un segment au bout
			score += 10;                                // Incrémente le score
			food = random_food(snake, snake_length);   // Place une nouvelle nourriture
		}

		// --- Rendu de la frame ---
		clear();                 // Efface l'écran
		draw_border();           // Dessine la bordure du terrain
		draw_food(food);         // Dessine la nourriture
		draw_snake(snake, snake_length); // Dessine le serpent
		draw_hud(score);         // Affiche le score et l'aide

		refresh();               // Affiche à l'écran
		napms(TICK_MSEC);        // Petite pause (vitesse du jeu)
	}

	// Fin de la boucle principale du jeu

	// --- Fin de partie / Écran Game Over ---
	nodelay(stdscr, false);    // Repasser getch() en bloquant pour attendre une touche
	draw_game_over(score);     // Affiche le message de fin
	refresh();                 // Met à jour l'affichage
	getch();                   // Attend une touche de l'utilisateur

	// --- Nettoyage ---
	endwin();                  // Restaure le terminal
	return 0;                  // Code de sortie OK
}
