#pragma once
#include "planet.h"

void initMutex();
void initTrajectories();
void trajectoryThreadFunction(void* arg);
void predictTrajectory(Planet* planet, vector2f* futurePositions);
void predictTrajectoryThreadSafe(Planet* planet, vector2f* futurePositions);
void updateTrajectories();

void drawTrajectories(sfRenderWindow* window);
void drawFutureTrajectories(sfRenderWindow* window);

void cleanUp(sfThread* trajectoryThread);