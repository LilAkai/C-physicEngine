/******************************
@Program: lilSolar
@author: lilAkai_
@help: luriaReimeiko
@date: 15/04/2025 (dd/mm/yyyy)
@version: beta-v0.1
******************************/

#include "view.h"
#include "source.h"
#include "trajectory.h"

void main(int argc, char** argv) {
    sfVideoMode mode = { 1920,1080,32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "lilSolar", WINDOWED, NULL);
    sfRenderWindow_setMouseCursorVisible(window, true);

    loadClaim();
    initTools();
    /*↓↓↓init↓↓↓*/
    initTrajectories();
    initMutex();
    initPlanets();
    initView();
    /*↑↑↑init↑↑↑*/

    sfThread* trajectoryThread = sfThread_create(&trajectoryThreadFunction, NULL);
    sfThread_launch(trajectoryThread);

    sfEvent event;
    while (sfRenderWindow_isOpen(window)) {
        restartClock();
        
        //gestion des events
        mouseWheelDirection = 0;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
            if (event.type == sfEvtMouseMoved) {
                mousePos = sfMouse_getPositionRenderWindow(window);
            }
            if (event.type == sfEvtMouseWheelScrolled) {
                mouseWheelDirection = event.mouseWheelScroll.delta;
            }
        }
        if (keyPressed(Escape))
            sfRenderWindow_close(window);
        if (keyPressed(Add))
            dtMult += 0.01f;
        if (keyPressed(Subtract))
            dtMult -= 0.01f;

        /*↓↓↓updates↓↓↓*/
        updateView(window);
        updatePlanets();
        updateTrajectories();
        /*↑↑↑updates↑↑↑*/

        printf_d("Nombre de planètes : %d\n", planetList->size(planetList));
        for (int i = 0; i < planetList->size(planetList); i++) {
            Planet* body = planetList->getData(planetList, i);
            printf("Planète %s, historique : %d positions\n", body->name, body->historyIndex);
        }

        sfRenderWindow_clear(window, sfBlack);
        displayView(window);
        /*↓↓↓display↓↓↓*/
        drawTrajectories(window);
        displayPlanets(window);
        //drawFutureTrajectories(window);
        /*↑↑↑display↑↑↑*/
        sfRenderWindow_display(window);
    }

    /*↓↓↓destroy↓↓↓*/
    saveClaim();
    cleanUp(trajectoryThread);
    /*↑↑↑destroy↑↑↑*/
    sfRenderWindow_destroy(window);
}