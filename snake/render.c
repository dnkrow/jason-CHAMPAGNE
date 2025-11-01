#include "render.h" // Interface de rendu basée sur ncurses

// Dessine la bordure du terrain (haut/bas/gauche/droite)
void draw_border(void)
{
    for (int x = 0; x < BOARD_WIDTH; ++x) // Ligne du haut et du bas
    {
        mvaddch(0, x, '#');               // Case (y=0, x) = '#'
        mvaddch(BOARD_HEIGHT - 1, x, '#'); // Case (y=max, x) = '#'
    }
    for (int y = 0; y < BOARD_HEIGHT; ++y) // Colonne gauche et droite
    {
        mvaddch(y, 0, '#');                // Case (y, x=0) = '#'
        mvaddch(y, BOARD_WIDTH - 1, '#');  // Case (y, x=max) = '#'
    }
}

// Dessine le serpent: tête 'O', corps 'o'
void draw_snake(Point snake[], int length)
{
    mvaddch(snake[0].y, snake[0].x, 'O');    // Tête
    for (int i = 1; i < length; ++i)         // Corps
    {
        mvaddch(snake[i].y, snake[i].x, 'o');
    }
}

// Dessine la nourriture à sa position
void draw_food(Point food)
{
    mvaddch(food.y, food.x, '*');
}

// Affiche le HUD (score et rappel pour quitter)
void draw_hud(int score)
{
    mvprintw(BOARD_HEIGHT, 0, "Score: %d  Quit: Q", score);
}

// Affiche l'écran de fin de partie centré
void draw_game_over(int score)
{
    mvprintw(BOARD_HEIGHT / 2, (BOARD_WIDTH - 20) / 2, "Game Over! Score: %d", score);
    mvprintw(BOARD_HEIGHT / 2 + 1, (BOARD_WIDTH - 24) / 2, "Press any key to exit...");
}
