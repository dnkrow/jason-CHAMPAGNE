# Snake terminal

## Prérequis
- Un compilateur C compatible C11 (ex. `gcc`)
- La bibliothèque de développement `ncurses` (`libncurses5-dev` ou `ncurses-devel` selon la distribution)

## Compilation
```bash
gcc main.c -std=c11 -Wall -Wextra -pedantic -lncurses -o snake_game
```

## Lancement
```bash
./snake_game
```

## Contrôles
- Flèches de direction ou touches `ZQSD` pour diriger le serpent
- `Q` pour quitter la partie

## Notes
- La fenêtre doit faire au moins 30 colonnes par 21 lignes pour afficher la zone de jeu et le score.
- Le score et un message de fin apparaissent lorsque la partie se termine.
