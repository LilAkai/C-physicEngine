#include "planet.h"
#define WINDOW_SIZEX 1920
#define WINDOW_SIZEY 1080
#define CENTER_X (WINDOW_SIZEX / 2.f)
#define CENTER_Y (WINDOW_SIZEY / 2.f)

#define SCALE 200.f

#define SIM_G 5.8e-22f
#define SOFTENING 7.f

#define EARTH_MOON_DISTANCE 0.00257f
#define MOON_ORBIT_RADIUS (EARTH_MOON_DISTANCE * SCALE)
#define MOON_BOOST_FACTOR 300.f

void createCircleShape(Planet* body) {
    body->shape = sfCircleShape_create();
    if (body->shape != NULL) {
        sfCircleShape_setRadius(body->shape, body->radius);
        sfCircleShape_setOrigin(body->shape, vec2f(body->radius, body->radius));
        sfCircleShape_setPosition(body->shape, body->pos);
        sfCircleShape_setTexture(body->shape, getTexture(body->name), NULL);
    }
}

void pushNewPlanet(const char* name, float orbitDistanceReal, float mass, float radius) {
    // orbitDistanceReal sera donné en UA ou unité adaptée et sera converti en pixels.
    Planet* body = malloc(sizeof(Planet));
    body->name = name;
    body->mass = mass;
    body->radius = radius;
    body->historySize = 500;
    body->history = malloc(body->historySize * sizeof(vector2f));
    body->historyIndex = 0;

    if (strcmp(name, "sun") == 0) {
        body->pos = vec2f(CENTER_X, CENTER_Y);
        body->velocity = vec2f(0.f, 0.f);
    }
    else if (strcmp(name, "moon") == 0) {
        Planet* earth = planetList->getData(planetList, 3);
        if (!earth) return;
        float orbitRadius = MOON_ORBIT_RADIUS; // par exemple 2.f
        body->pos = vec2f(earth->pos.x + orbitRadius, earth->pos.y);
        vector2f radial = subVec2f(body->pos, earth->pos); // radial = (orbitRadius, 0)
        float len = sqrt(radial.x * radial.x + radial.y * radial.y);
        if (len == 0.f) len = 1.f;
        vector2f normalizedRadial = vec2f(radial.x / len, radial.y / len);
        // Calculer la tangente en tournant le vecteur radial de -90° pour tenir compte de l'axe Y positif vers le bas.
        vector2f tangent = vec2f(normalizedRadial.y, -normalizedRadial.x);
        float relSpeed = sqrt(SIM_G * earth->mass / orbitRadius) * MOON_BOOST_FACTOR;
        body->velocity = vec2f(earth->velocity.x + tangent.x * relSpeed,
            earth->velocity.y + tangent.y * relSpeed);
    }
    else {
        // Pour une planète qui orbite autour du Soleil,
        // orbitDistanceReal est la distance réelle (exprimée dans UA ou unité choisie)
        // La distance en pixels
        float orbitDistancePix = orbitDistanceReal * SCALE;
        body->pos = vec2f(CENTER_X + orbitDistancePix, CENTER_Y);
        Planet* sun = planetList->getData(planetList, 0);
        float orbitalSpeed = sqrt(SIM_G * sun->mass / orbitDistancePix);
        // Pour que l'orbite soit tangente, la vitesse est initialisée verticalement négative
        body->velocity = vec2f(0.f, -orbitalSpeed);
    }
    createCircleShape(body);
    planetList->push_back(&planetList, body);
}

vector2f computeAcceleration(Planet* planet) {
    int numPlanets = planetList->size(planetList);
    vector2f totalAcceleration = vec2f(0.f, 0.f);
    for (int j = 0; j < numPlanets; j++) {
        Planet* other = planetList->getData(planetList, j);
        if (other == planet) continue;
        vector2f direction = subVec2f(other->pos, planet->pos);
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance < 1.f) distance = 1.f;
        float softenedDistanceSq = distance * distance + SOFTENING * SOFTENING;
        float accMag = (SIM_G * other->mass) / softenedDistanceSq;
        // Pour la Lune, renforcer l'effet de la Terre
        if (strcmp(planet->name, "moon") == 0 && strcmp(other->name, "earth") == 0)
            accMag *= MOON_BOOST_FACTOR;
        totalAcceleration.x += accMag * (direction.x / distance);
        totalAcceleration.y += accMag * (direction.y / distance);
    }
    return totalAcceleration;
}

void initPlanets() {
    planetList = STD_LIST_CREATE(Planet, 0);
    // Ici orbitDistanceReal est en UA ou en unité relative.
    // On place le Soleil au centre (pas de conversion)
    pushNewPlanet("sun", 0.f, 1.989e27, 50.f);
    // Par exemple, Mercury à 0.39 UA, Venus à 0.72 UA, Earth à 1 UA, Mars à 1.52 UA, etc.
    pushNewPlanet("mercury", 0.39f, 3.3011e20, 5.f);
    pushNewPlanet("venus", 0.72f, 4.8675e21, 6.f);
    pushNewPlanet("earth", 1.f, 5.97237e21, 6.f);
    // La Lune ne prend pas de distance réelle ici, elle est calculée par rapport à la Terre.
    pushNewPlanet("moon", 0.f, 7.342e19, 2.f);
    pushNewPlanet("mars", 1.52f, 6.4171e20, 4.f);
    pushNewPlanet("jupiter", 5.2f, 1.8982e24, 20.f);
    pushNewPlanet("saturn", 9.54f, 5.6834e23, 18.f);
    pushNewPlanet("uranus", 19.19f, 8.6810e22, 14.f);
    pushNewPlanet("neptune", 30.06f, 1.02413e23, 14.f);
    pushNewPlanet("pluto", 39.48f, 1.303e19, 3.f);
}

void updatePlanets() {
    int numPlanets = planetList->size(planetList);
    for (int i = 1; i < numPlanets; i++) {
        Planet* planet = planetList->getData(planetList, i);
        vector2f acceleration = computeAcceleration(planet);
        planet->velocity.x += acceleration.x * dt;
        planet->velocity.y += acceleration.y * dt;
        planet->pos.x += planet->velocity.x * dt;
        planet->pos.y += planet->velocity.y * dt;
        sfCircleShape_setPosition(planet->shape, planet->pos);
    }
    if (keyPressed(Tab)) {
        destroyPlanets();
        initPlanets();
        dtMult = 10.f;
    }
}

void displayPlanets(sfRenderWindow* window) {
    for (int i = 0; i < planetList->size(planetList); i++) {
        Planet* body = planetList->getData(planetList, i);
        sfRenderWindow_drawCircleShape(window, body->shape, NULL);
    }
}

void destroyPlanets() {
    for (int i = 0; i < planetList->size(planetList); i++) {
        planetList->erase(&planetList, i);
    }
}