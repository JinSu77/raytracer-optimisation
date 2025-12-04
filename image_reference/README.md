# Images de Référence

Ce dossier contient les images de référence pour les tests de régression visuelle.

## Génération de l'image de référence

Pour générer l'image de référence `two-spheres-on-plane.png`, exécutez depuis le répertoire `build` :

```bash
cd build
./raytracer ../scenes/two-spheres-on-plane.json ../image_reference/two-spheres-on-plane.png
```

## Utilisation

Une fois l'image de référence générée, le test `test_image_comparison` :
1. Génère une nouvelle image **en mémoire** (sans la sauvegarder)
2. Compare l'image en mémoire avec l'image de référence pixel par pixel
3. Signale toute différence (régression visuelle)

## Workflow

1. **Première fois** : Générer l'image de référence avec le code correct (non-optimisé)
2. **Après optimisation** : Relancer les tests
3. **Si différence détectée** :
   - Vérifier si c'est une régression (bug)
   - Ou une amélioration intentionnelle (alors mettre à jour la référence)

## Format

- Format : PNG
- Dimensions : Définies dans le fichier de scène (ex: 1920x1080)
- Couleur : RGB avec valeurs entre 0.0 et 1.0
