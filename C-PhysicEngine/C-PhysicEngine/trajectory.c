#include "trajectory.h"
sfMutex* trajectoryMutex;
sfVertexArray* trajectoryArray;

void initMutex(){
    trajectoryMutex = sfMutex_create();
}

void trajectoryThreadFunction(void* arg) {
    vector2f futurePositions[100];
    while (1) {
        for (int i = 0; i < planetList->size(planetList); i++) {
            Planet* body = planetList->getData(planetList, i);
            predictTrajectoryThreadSafe(body, futurePositions);
        }

        sfSleep(sfMilliseconds(100)); // Pause pour éviter de surcharger le CPU
    }
}

void predictTrajectory(Planet* planet, vector2f* futurePositions) {
    vector2f tempPos = planet->pos;
    vector2f tempVelocity = planet->velocity;
    vector2f tempAcceleration = computeAcceleration(planet);

    float dtSim = dt * 10.f;

    for (int i = 0; i < 100; i++) {
        vector2f newAcceleration = computeAcceleration(planet);

        // Intégration de Verlet : Position mise à jour avec la vitesse et l'accélération précédente
        tempPos.x += tempVelocity.x * dtSim + 0.5f * tempAcceleration.x * dtSim * dtSim;
        tempPos.y += tempVelocity.y * dtSim + 0.5f * tempAcceleration.y * dtSim * dtSim;

        // Mise à jour de la vitesse
        tempVelocity.x += 0.5f * (tempAcceleration.x + newAcceleration.x) * dtSim;
        tempVelocity.y += 0.5f * (tempAcceleration.y + newAcceleration.y) * dtSim;

        tempAcceleration = newAcceleration;
        futurePositions[i] = tempPos;
    }
}


void initTrajectories() {
    trajectoryArray = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(trajectoryArray, sfLines);
}

#define MAX_TRAIL_LENGTH 2000

void updateTrajectories() {
    sfVertexArray_clear(trajectoryArray); // On vide le tableau global avant de le réremplir

    int numPlanets = planetList->size(planetList);
    for (int i = 0; i < numPlanets; i++) {
        Planet* planet = planetList->getData(planetList, i);
        vector2f acceleration = computeAcceleration(planet);

        // Mise à jour de la physique : vitesses et positions
        planet->velocity.x += acceleration.x * dt;
        planet->velocity.y += acceleration.y * dt;
        planet->pos.x += planet->velocity.x * dt;
        planet->pos.y += planet->velocity.y * dt;
        sfCircleShape_setPosition(planet->shape, planet->pos);

        // Ajout de la position actuelle dans l'historique : allocation dynamique si nécessaire
        if (planet->historyIndex < planet->historySize) {
            planet->history[planet->historyIndex] = planet->pos;
            planet->historyIndex++;
        }
        else {
            planet->historySize *= 2;
            planet->history = realloc(planet->history, planet->historySize * sizeof(vector2f));
            planet->history[planet->historyIndex] = planet->pos;
            planet->historyIndex++;
        }

        // Si l'historique dépasse la longueur maximale, on supprime le plus ancien point.
        if (planet->historyIndex > MAX_TRAIL_LENGTH) {
            memmove(planet->history, planet->history + 1, (planet->historyIndex - 1) * sizeof(vector2f));
            planet->historyIndex--;
        }

        // Création des segments de l'orbite pour cette planète.
        if (planet->historyIndex >= 2) {
            for (int j = 0; j < planet->historyIndex - 1; j++) {
                sfVertex v1, v2;
                // Le segment entre le point j et le point j+1
                v1.position = planet->history[j];
                v1.color = sfColor_fromRGB(255, 255, 255);
                v2.position = planet->history[j + 1];
                v2.color = sfColor_fromRGB(255, 255, 255);
                sfVertexArray_append(trajectoryArray, v1);
                sfVertexArray_append(trajectoryArray, v2);
            }
        }
    }
}

void drawTrajectories(sfRenderWindow* window) {
    int numPlanets = planetList->size(planetList);
    for (int i = 0; i < numPlanets; i++) {
        if (sfVertexArray_getVertexCount(trajectoryArray) > 0) {
            sfRenderWindow_drawVertexArray(window, trajectoryArray, NULL);
        }
    }
}

void predictTrajectoryThreadSafe(Planet* planet, vector2f* futurePositions) {
    sfMutex_lock(trajectoryMutex);
    predictTrajectory(planet, futurePositions);
    sfMutex_unlock(trajectoryMutex);
}

void drawFutureTrajectories(sfRenderWindow* window) {
    vector2f futurePositions[100];

    for (int i = 0; i < planetList->size(planetList); i++) {
        Planet* body = planetList->getData(planetList, i);
        predictTrajectory(body, futurePositions);

        for (int j = 0; j < 100; j++) {
            sfCircleShape* point = sfCircleShape_create();
            sfCircleShape_setRadius(point, 2.f);
            sfCircleShape_setPosition(point, futurePositions[j]);
            sfRenderWindow_drawCircleShape(window, point, NULL);
            sfCircleShape_destroy(point);
        }
    }
    sfMutex_unlock(trajectoryMutex);
}

void cleanUp(sfThread* trajectoryThread) {
    sfThread_terminate(trajectoryThread);
    sfMutex_destroy(trajectoryMutex);
}
