# VacancesPro

Application React simulant une plateforme de réservation de logements. Projet prêt à être lancé avec [Vite](https://vitejs.dev/).

## Prise en main

```bash
cd airbnb
npm install
npm run dev
```

Le serveur de développement s’exécute par défaut sur [http://localhost:5173](http://localhost:5173).

## Build de production

```bash
npm run build
```

Les fichiers prêts à être déployés sont générés dans le dossier `dist/`.

## Déploiement rapide

- **Netlify** : connecter le dépôt, définir `npm run build` comme commande de build et `dist` comme dossier de publication.
- **Vercel** : importer le projet, laisser la détection automatique (framework Vite).
- **GitHub Pages** : utiliser `npm run build` puis publier le contenu de `dist/` (ex. via la branche `gh-pages`).

## Structure

```
airbnb/
├── index.html
├── package.json
├── vite.config.js
└── src
    ├── App.jsx
    ├── main.jsx
    ├── styles.css
    └── components/
```

Chaque page (Accueil, Recherche, Détails, etc.) dispose de son propre composant dans `src/components`.
