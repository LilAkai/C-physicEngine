/******************************
@Program: lilSolar
@author: lilAkai_
@help: luriaReimeiko
@date: 15/04/2025 (dd/mm/yyyy)
@version: beta-v0.1
******************************/

//TODO faire les gravités entre les planetes

#include "view.h"
#include "source.h"
#include "trajectory.h"
#include "grid.h"

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

        sfRenderWindow_clear(window, sfBlack);
        /*↓↓↓display↓↓↓*/
        drawGrid(window, 35.f);
        displayView(window);
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