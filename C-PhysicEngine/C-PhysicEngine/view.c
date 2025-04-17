#include "view.h"

sfView* view;
vector2f viewOrigin = {960.f,540.f};
sfFloatRect viewRect = {0.f,0.f,1920.f,1080.f};
float viewZoom = 1.f;
float totalZoom = 1.f;

float viewAngle = 0.f;
vector2f lastMousePos;


void initView(){
	view = sfView_createFromRect(viewRect);
	sfView_setCenter(view,viewOrigin);
	sfView_zoom(view, viewZoom);
}

void updateView(sfRenderWindow* window) {
    sfVector2i mousePosPixel = sfMouse_getPositionRenderWindow(window);
    sfVector2f mousePosWorld = sfRenderWindow_mapPixelToCoords(window, mousePosPixel, view);

    if (mousePressed(Left) && sfRenderWindow_hasFocus(window)) {
        // Calcul du vecteur de déplacement en fonction de la souris
        vector2f dir = subVec2f(lastMousePos, vec2i2f(mousePos));

        // Appliquer la rotation du mouvement selon l'angle de la vue
        float angleRad = viewAngle * DEG2RAD; // Convertir en radians
        float rotatedX = cosf(angleRad) * dir.x - sinf(angleRad) * dir.y;
        float rotatedY = sinf(angleRad) * dir.x + cosf(angleRad) * dir.y;

        vector2f move = { rotatedX * totalZoom, rotatedY * totalZoom};

        // Déplacer la vue en fonction de l'orientation
        sfView_move(view, move);
    }

    // Gestion de la rotation de la caméra avec la souris
    if (mousePressed(Right)) {
        if (mousePos.y > lastMousePos.y || mousePos.x > lastMousePos.x) {
            viewAngle += 3.f;
        }
        if (mousePos.y < lastMousePos.y || mousePos.x < lastMousePos.x) {
            viewAngle -= 3.f;
        }
    }

    // Gestion du zoom basé sur l'emplacement du curseur
    if (mouseWheelDirection > 0.f) {
        viewZoom -= 0.1f;
        totalZoom *= 0.9f;
    }
    if (mouseWheelDirection < 0.f) {
        viewZoom += 0.1f;
        totalZoom *= 1.1f;
    }

    // Ajuster le centre de la vue pour que le point sous la souris reste fixe pendant le zoom
    sfVector2f newCenter = sfView_getCenter(view);
    newCenter.x += (mousePosWorld.x - newCenter.x) * (1.f - viewZoom);
    newCenter.y += (mousePosWorld.y - newCenter.y) * (1.f - viewZoom);
    sfView_setCenter(view, newCenter);

    // Appliquer les mises à jour de zoom et rotation
    sfView_zoom(view, viewZoom);
    sfView_setRotation(view, viewAngle);

    lastMousePos = vec2i2f(mousePos);
    viewZoom = 1.f;

    // Réinitialisation de la vue
    if (scanPressed(Grave)) {
        sfView_reset(view, viewRect);
        dtMult = 10.f;
    }
}


void displayView(sfRenderWindow* window){
	sfRenderWindow_setView(window, view);
}
