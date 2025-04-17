#include "grid.h"

#include <SFML/Graphics.h>
#include <math.h>

// Fonction pour dessiner la grille.
// fixedPixelSpacing : espacement en pixels souhaité (par exemple 50 px)
void drawGrid(sfRenderWindow* window, float fixedPixelSpacing){
    // Sauvegarder la vue actuelle
    sfView* currentView = sfRenderWindow_getView(window);
    // Créer une copie de la vue pour le dessin de la grille
    sfView* gridView = sfView_copy(currentView);
    // Supprimer la rotation pour que la grille reste horizontale/verticale
    sfView_setRotation(gridView, 0);
    // Appliquer la vue "non tourné" pour le dessin de la grille
    sfRenderWindow_setView(window, gridView);

    // Récupérer les paramètres de la grille depuis gridView
    sfVector2f viewCenter = sfView_getCenter(gridView);
    sfVector2f viewSize = sfView_getSize(gridView);

    // Calculer le rectangle visible en utilisant la vue non tournée
    sfFloatRect viewRect;
    viewRect.left = viewCenter.x - viewSize.x * 0.5f;
    viewRect.top = viewCenter.y - viewSize.y * 0.5f;
    viewRect.width = viewSize.x;
    viewRect.height = viewSize.y;

    // Taille de la fenêtre (en pixels), nécessaire pour la conversion
    sfVector2u windowSize = sfRenderWindow_getSize(window);
    // Conversion : unités du monde par pixel (supposant un zoom uniforme)
    float worldUnitsPerPixel = viewSize.x / windowSize.x;
    // Calcul de l'espacement en unités du monde pour obtenir fixedPixelSpacing pixels sur l'écran
    float effectiveSpacing = fixedPixelSpacing * worldUnitsPerPixel;

    // Déterminer les positions de départ, arrondies vers le bas, afin d'aligner la grille
    float startX = floor(viewRect.left / effectiveSpacing) * effectiveSpacing;
    float startY = floor(viewRect.top / effectiveSpacing) * effectiveSpacing;

    // Créer un sfVertexArray pour tracer la grille en mode sfLines
    sfVertexArray* gridArray = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(gridArray, sfLines);

    // Tracer les lignes verticales
    for (float x = startX; x <= viewRect.left + viewRect.width; x += effectiveSpacing) {
        sfVertex v1, v2;
        v1.position = (sfVector2f){ x, viewRect.top };
        v2.position = (sfVector2f){ x, viewRect.top + viewRect.height };
        v1.color = sfColor_fromRGB(30, 30, 30);
        v2.color = sfColor_fromRGB(30, 30, 30);
        sfVertexArray_append(gridArray, v1);
        sfVertexArray_append(gridArray, v2);
    }

    // Tracer les lignes horizontales
    for (float y = startY; y <= viewRect.top + viewRect.height; y += effectiveSpacing) {
        sfVertex v1, v2;
        v1.position = (sfVector2f){ viewRect.left, y };
        v2.position = (sfVector2f){ viewRect.left + viewRect.width, y };
        v1.color = sfColor_fromRGB(30, 30, 30);
        v2.color = sfColor_fromRGB(30, 30, 30);
        sfVertexArray_append(gridArray, v1);
        sfVertexArray_append(gridArray, v2);
    }

    // Dessiner la grille
    sfRenderWindow_drawVertexArray(window, gridArray, NULL);

    // Libérer le sfVertexArray et détruire la vue temporaire
    sfVertexArray_destroy(gridArray);
    sfView_destroy(gridView);

    // Restaurer la vue d'origine pour le reste du dessin
    sfRenderWindow_setView(window, currentView);
}