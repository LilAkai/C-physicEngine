#include "planet.h"

void main(int argc, char** argv) {
    sfVideoMode mode = { 1920,1080,32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "Pang", BORDERLESS, NULL);

    initTools();
    /*↓↓↓init↓↓↓*/
    initPlanets();
    /*↑↑↑init↑↑↑*/

    sfEvent event;
    while (sfRenderWindow_isOpen(window)) {
        mousePos = sfMouse_getPositionRenderWindow(window);
        restartClock();
        //gestion des events
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
        }
        if (keyPressed(Escape))
            sfRenderWindow_close(window);

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