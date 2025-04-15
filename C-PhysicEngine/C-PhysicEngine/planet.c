#include "planet.h"
#define WINDOW_SIZE 1080
#define SCALE_FACTOR (WINDOW_SIZE / 2.0f / 5906380.0f) // Pluton à 5 906 380 km du Soleil
#define CENTER_X (WINDOW_SIZE / 2.0f)
#define CENTER_Y (WINDOW_SIZE / 2.0f)
#define MASS_SCALE 1e-6  // Réduction des masses
#define RADIUS_SCALE 1e-3 // Réduction des rayons
const double sunMass = 1989000.f;

void scalePosition(vector2f pos) {
    pos.x *= SCALE_FACTOR;
    pos.y *= SCALE_FACTOR;
}

void createCircleShape(Planet* body) {
    body->shape = sfCircleShape_create();
    if (body->shape != NULL) {
        sfCircleShape_setRadius(body->shape, body->radius);
        sfCircleShape_setPosition(body->shape, body->pos);
        sfCircleShape_setOrigin(body->shape, vec2f(body->radius, body->radius));
        sfCircleShape_setTexture(body->shape, getTexture(body->name), NULL);
    }
    else printf_d("%s init failed: %d", body->name, __LINE__);
}

void pushNewPlanet(const char* name, float pos, float velocity,float mass,float radius) {
    Planet* body = malloc(sizeof(Planet));

    body->pos = vec2f(pos,CENTER_Y);
    scalePosition(body->pos);

    body->velocity = vec2f(0.f, sqrt(6.674e-11 * sunMass / 149600000.0f));
    body->mass = mass;
    body->radius = radius * SCALE_FACTOR;
    body->name = name;

    createCircleShape(body);

    planetList->push_back(&planetList, body);
}

void initPlanets() {
    planetList = STD_LIST_CREATE(Planet, 0);
    pushNewPlanet("sun", 540.0f, 540.0f, 1.989f, 695.7f);
    pushNewPlanet("mercury", 547.0f, 540.0f, 0.00033f, 2.4397f);
    pushNewPlanet("venus", 554.0f, 540.0f, 0.0048685f, 6.0518f);
    pushNewPlanet("earth", 563.0f, 540.0f, 0.005972f, 6.371f);
    pushNewPlanet("moon", 563.4f, 540.0f, 0.0000735f, 1.737f);
    pushNewPlanet("mars", 573.0f, 540.0f, 0.00064171f, 3.3895f);
    pushNewPlanet("jupiter", 618.0f, 540.0f, 1.898f, 69.911f);
    pushNewPlanet("saturn", 682.0f, 540.0f, 0.56834f, 58.232f);
    pushNewPlanet("uranus", 827.0f, 540.0f, 0.08681f, 25.362f);
    pushNewPlanet("neptune", 993.0f, 540.0f, 0.10241f, 24.622f);
    pushNewPlanet("pluto", 1120.0f, 540.0f, 0.00001303f, 1.1883f);
}

void updatePlanets() {
    for (int i = 1; i < planetList->size(planetList); i++){
        Planet* sun = planetList->getData(planetList, 0);
        Planet* planet = planetList->getData(planetList, i);

        vector2f direction = subVector(sun->pos, planet->pos);
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

        // Éviter la division par zéro
        if (distance < 1.0f) return;

        // Calcul de la force gravitationnelle
        float force = (gravitionalConstant * sunMass * planet->mass) / (distance * distance);
        vector2f acceleration = vec2f(force * direction.x / planet->mass, force * direction.y / planet->mass);        

        // Mise à jour des vitesses
        planet->velocity.x += acceleration.x * dt;
        planet->velocity.y += acceleration.y * dt;

        // Mise à jour des positions
        planet->pos.x += planet->velocity.x * dt;
        planet->pos.y += planet->velocity.y * dt;

        //printf_d("%s pos moved\n", planet->name);
        printf_d("\n\n%s pos(%g,%g) | velo(%g,%g) | deltaTime : %g\n\n", planet->name, planet->pos.x, planet->pos.y, planet->velocity.x, planet->velocity.y, dt);

        // Mise à jour graphique
        sfCircleShape_setPosition(planet->shape, planet->pos);
    }
}


void displayPlanets(sfRenderWindow* window) {
    for (int i = 0; i < planetList->size(planetList); i++){
        Planet* body = planetList->getData(planetList, i);
        sfRenderWindow_drawCircleShape(window, body->shape, NULL);
    }
}

void destroyPlanets(){
}
