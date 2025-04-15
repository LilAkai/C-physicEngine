#include "planet.h"

void main(int argc, char** argv) {
    sfVideoMode mode = { 1000,1000,32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "Pang", BORDERLESS, NULL);

    initTools();
    /*↓↓↓init↓↓↓*/
    initPlanets();
    /*↑↑↑init↑↑↑*/

    sfEvent event;
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_requestFocus(window);
        mousePos = sfMouse_getPositionRenderWindow(window);
        restartClock();
        sfJoystick_update();
        //gestion des events
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
        }

        /*↓↓↓updates↓↓↓*/
        updatePlanets();
        /*↑↑↑updates↑↑↑*/
        sfRenderWindow_clear(window, sfBlack);

        /*↓↓↓display↓↓↓*/
        displayPlanets(window);
        /*↑↑↑display↑↑↑*/
        sfRenderWindow_display(window);
    }

    /*↓↓↓destroy↓↓↓*/
    /*↑↑↑destroy↑↑↑*/
    sfRenderWindow_destroy(window);
}