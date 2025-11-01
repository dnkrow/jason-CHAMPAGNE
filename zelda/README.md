# Zelda (Terminal)

Un mini-jeu type Zelda en terminal (ncurses), avec 10 niveaux de 100x100, clic gauche pour l'épée, clic droit pour tirer des flèches, déplacements aux flèches directionnelles. Sur la première carte, parle au PNJ (touche `E`) qui t'explique l'objectif et indique d'avancer vers le haut pour sauver la princesse. Tue tous les monstres pour ouvrir la porte en haut et passer au niveau suivant.

## Compilation

- Dépendance: `ncurses` (Linux: `sudo apt install libncurses5-dev` ou `libncurses-dev`)

```
cd zelda
make
./zelda_game
```

## Contrôles

- Flèches: se déplacer
- Souris clic gauche: attaque à l'épée (case adjacente vers le clic)
- Souris clic droit: tirer une flèche (direction du clic)
- E: parler/interagir (PNJ)
- Q: quitter

## Détails de gameplay

- 3 coeurs au départ. Certains monstres peuvent lâcher un coeur (soin) et d'autres des flèches (rare).
- Les cartes font 100x100; la vue défile autour du joueur.
- La porte en haut s'ouvre après avoir éliminé tous les ennemis du niveau.
- 10 niveaux; victoire après le niveau 10.

