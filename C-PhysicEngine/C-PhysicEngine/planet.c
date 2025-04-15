#include "planet.h"
#define WINDOW_SIZE 1080
#define SCALE_FACTOR (WINDOW_SIZE / 2.0f / 5906380.0f) // Pluton à 5 906 380 km du Soleil

void scalePosition(vec2f* pos) {
    pos->x *= SCALE_FACTOR;
    pos->y *= SCALE_FACTOR;
}

void createCircleShape(Presset* body) {
    body->shape = sfCircleShape_create();
    if (body->shape != NULL) {
        sfCircleShape_setRadius(body->shape, body->radius);
        sfCircleShape_setPosition(body->shape, vector2f(body->pos.x, body->pos.y));
        sfCircleShape_setTexture(body->shape,getTexture(body->name),NULL);
    }
}
void updatePlanetPos(Presset* planet) {
    if (planet != NULL) {
        sfCircleShape_setPosition(planet->shape, planet->pos);
    }
}
#pragma region Planets
void initSun(Presset* sun) {
    sun->name = "sun";
    sun->pos = vector2f(0.0f, 0.0f);
    scalePosition(&sun->pos);
    sun->velocity = vector2f(0.0f, 0.0f);
    sun->mass = 1989000.0f;
    sun->radius = 695700.0f * SCALE_FACTOR;
    createCircleShape(sun);
}
void initMercury(Presset* mercury) {
    mercury->name = "mercury";
    mercury->pos = vector2f(57900.0f, 0.0f);
    scalePosition(&mercury->pos);
    mercury->velocity = vector2f(0.0f, 47.87f);
    mercury->mass = 330.11f;
    mercury->radius = 2439.7f * SCALE_FACTOR;
    createCircleShape(mercury);
}
void initVenus(Presset* venus) {
    venus->name = "venus";
    venus->pos = vector2f(108200.0f, 0.0f);
    scalePosition(&venus->pos);
    venus->velocity = vector2f(0.0f, 35.02f);
    venus->mass = 4868.5f;
    venus->radius = 6051.8f * SCALE_FACTOR;
    createCircleShape(venus);
}
void initEarth(Presset* earth) {
    earth->name = "earth";
    earth->pos = vector2f(149600.0f, 0.0f);
    scalePosition(&earth->pos);
    earth->velocity = vector2f(0.0f, 29.78f);
    earth->mass = 5972.0f;
    earth->radius = 6371.0f * SCALE_FACTOR;
    createCircleShape(earth);
}
void initMoon(Presset* moon) {
    moon->name = "moon";
    moon->pos = vector2f(149600.0f + 384.4f, 0.0f);
    scalePosition(&moon->pos);
    moon->velocity = vector2f(0.0f, 29.78f + 1.022f);
    moon->mass = 73.5f;
    moon->radius = 1737.0f * SCALE_FACTOR;
    createCircleShape(moon);
}
void initMars(Presset* mars) {
    mars->name = "mars";
    mars->pos = vector2f(227940.0f, 0.0f);
    scalePosition(&mars->pos);
    mars->velocity = vector2f(0.0f, 24.077f);
    mars->mass = 641.71f;
    mars->radius = 3389.5f * SCALE_FACTOR;
    createCircleShape(mars);
}
void initJupiter(Presset* jupiter) {
    jupiter->name = "jupiter";
    jupiter->pos = vector2f(778330.0f, 0.0f);
    scalePosition(&jupiter->pos);
    jupiter->velocity = vector2f(0.0f, 13.07f);
    jupiter->mass = 1898000.0f;
    jupiter->radius = 69911.0f * SCALE_FACTOR;
    createCircleShape(jupiter);
}
void initSaturn(Presset* saturn) {
    saturn->name = "saturn";
    saturn->pos = vector2f(1429400.0f, 0.0f);
    scalePosition(&saturn->pos);
    saturn->velocity = vector2f(0.0f, 9.69f);
    saturn->mass = 568340.0f;
    saturn->radius = 58232.0f * SCALE_FACTOR;
    createCircleShape(saturn);
}
void initUranus(Presset* uranus) {
    uranus->name = "uranus";
    uranus->pos = vector2f(2870990.0f, 0.0f);
    scalePosition(&uranus->pos);
    uranus->velocity = vector2f(0.0f, 6.81f);
    uranus->mass = 86810.0f;
    uranus->radius = 25362.0f * SCALE_FACTOR;
    createCircleShape(uranus);
}
void initNeptune(Presset* neptune) {
    neptune->name = "neptune";
    neptune->pos = vector2f(4495100.0f, 0.0f);
    scalePosition(&neptune->pos);
    neptune->velocity = vector2f(0.0f, 5.43f);
    neptune->mass = 102410.0f;
    neptune->radius = 24622.0f * SCALE_FACTOR;
    createCircleShape(neptune);
}
void initPluto(Presset* pluto) {
    pluto->name = "pluto";
    pluto->pos = vector2f(5906380.0f, 0.0f);
    scalePosition(&pluto->pos);
    pluto->velocity = vector2f(0.0f, 4.74f);
    pluto->mass = 13.03f;
    pluto->radius = 1188.3f * SCALE_FACTOR;
    createCircleShape(pluto);
}
#pragma endregion

void initPlanet(Planet* planet) {
    initSun(&planet->sun);
    initMercury(&planet->mercury);
    initVenus(&planet->venus);
    initEarth(&planet->earth);
    initMoon(&planet->moon);
    initMars(&planet->mars);
    initJupiter(&planet->jupiter);
    initSaturn(&planet->saturn);
    initUranus(&planet->uranus);
    initNeptune(&planet->neptune);
    initPluto(&planet->pluto);
}

void updatePlanets(){
    
}

void displayPlanets(sfRenderWindow* window){
    sfRenderWindow_drawCircleShape(window, planet.sun.shape, NULL);
    sfRenderWindow_drawCircleShape(window, planet.mercury.shape, NULL);
    sfRenderWindow_drawCircleShape(window, planet.venus.shape, NULL);
    sfRenderWindow_drawCircleShape(window, planet.earth.shape, NULL);
    sfRenderWindow_drawCircleShape(window, planet.moon.shape, NULL);
    sfRenderWindow_drawCircleShape(window, planet.mars.shape, NULL);
    sfRenderWindow_drawCircleShape(window, planet.jupiter.shape, NULL);
    sfRenderWindow_drawCircleShape(window, planet.saturn.shape, NULL);
    sfRenderWindow_drawCircleShape(window, planet.uranus.shape, NULL);
    sfRenderWindow_drawCircleShape(window, planet.neptune.shape, NULL);
    sfRenderWindow_drawCircleShape(window, planet.pluto.shape, NULL);
}

void destroyPlanets(){
}
