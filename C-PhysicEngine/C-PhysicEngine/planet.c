#include "planet.h"

// Définition des constantes d'affichage et de conversion
#define WINDOW_SIZEX 1920
#define WINDOW_SIZEY 1080
#define CENTER_X (WINDOW_SIZEX / 2.f)
#define CENTER_Y (WINDOW_SIZEY / 2.f)
#define ORBIT_MULTIPLIER 5.f

// Constante gravitationnelle en simulation (adaptée pour utiliser les vraies masses)
// La valeur de 5.8e-22f a été obtenue (approximativement) pour obtenir des orbites réalistes
// dans vos unités (pixels, secondes) sachant que, par exemple, pour la Terre : 
// orbitDistance = (563 - 540)*5 = 115 pixels et M_sun ? 1.989e27.
// Ainsi, v = sqrt( SIM_G * 1.989e27 / 115 ) ? 100 pixels/s.
#define SIM_G 5.8e-22f

// Pour éviter les singularités lorsque des corps se rapprochent trop,
// le softening est appliqué dans le calcul des forces.
#define SOFTENING 7.f

void createCircleShape(Planet* body) {
    body->shape = sfCircleShape_create();
    if (body->shape != NULL) {
        sfCircleShape_setRadius(body->shape, body->radius);
        sfCircleShape_setOrigin(body->shape, vec2f(body->radius, body->radius));
        sfCircleShape_setPosition(body->shape, body->pos);
        sfCircleShape_setTexture(body->shape, getTexture(body->name), NULL);
    }
    else {
        printf_d("%s init failed: %d", body->name, __LINE__);
    }
}

/*
  La fonction pushNewPlanet crée et positionne chaque corps.

  Pour le Soleil (nom "sun") :
    - Il est placé au centre de l'écran et reste fixe.

  Pour chacun des autres corps :
    - Le paramètre "pos" sert de référence pour définir la distance orbitale
      (orbitDistance = (pos - 540) * ORBIT_MULTIPLIER).
    - La position est alors : (CENTER_X + orbitDistance, CENTER_Y).
    - La vitesse orbitale idéale pour une orbite circulaire est calculée par :
         v = sqrt( SIM_G * M_sun / orbitDistance )
      Ici, M_sun est la masse du Soleil,
      que nous récupérons depuis le premier élément de planetList (déjà créé).
    - La vitesse initiale est orientée verticalement (tangente à une orbite circulaire
      pour un corps situé à droite du Soleil).
*/
void pushNewPlanet(const char* name, float pos, float velocity, float mass, float radius) {
    Planet* body = malloc(sizeof(Planet));

    if (strcmp(name, "sun") == 0) {
        // Le Soleil est au centre et reste fixe
        body->pos = vec2f(CENTER_X, CENTER_Y);
        body->velocity = vec2f(0.f, 0.f);
    }
    else {
        // Calcul de la distance orbitale en pixels
        float orbitDistance = (pos - 540.f) * ORBIT_MULTIPLIER;
        // Position sur l'axe horizontal par rapport au centre (Soleil)
        body->pos = vec2f(CENTER_X + orbitDistance, CENTER_Y);
        // Récupération du Soleil déjà créé dans planetList
        Planet* sun = planetList->getData(planetList, 0);
        // Calcul de la vitesse orbitale idéale pour une orbite circulaire
        float orbitalSpeed = sqrt(SIM_G * sun->mass / orbitDistance);
        // Vitesse initiale (tangente à l'orbite, ici verticale vers le haut)
        body->velocity = vec2f(0.f, -orbitalSpeed);
    }

    body->mass = mass;   // Masse en kg (dans vos unités, par ex. 1.989e27 pour le Soleil)
    body->radius = radius; // Rayon d'affichage en pixels (indépendant de la masse réelle)
    body->name = name;

    createCircleShape(body);
    planetList->push_back(&planetList, body);
}

/*
  computeAcceleration calcule l'accélération exercée sur une planète
  par la contribution gravitationnelle de tous les autres corps de la simulation.

  Pour chaque corps "other" différent de la planète considérée,
   - On calcule le vecteur direction,
   - On applique un softening lorsque la distance est faible,
   - L'accélération résultante est :
         a = SIM_G * other->mass / (distance^2 + SOFTENING^2)
     dans la direction (normalisée) allant de la planète vers "other".
*/
vector2f computeAcceleration(Planet* planet) {
    int numPlanets = planetList->size(planetList);
    vector2f totalAcceleration = vec2f(0.f, 0.f);

    for (int j = 0; j < numPlanets; j++) {
        Planet* other = planetList->getData(planetList, j);
        if (other == planet)
            continue;
        vector2f direction = subVector(other->pos, planet->pos);
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance < 1.f)
            distance = 1.f;
        float softenedDistanceSq = distance * distance + SOFTENING * SOFTENING;
        float accelerationMagnitude = (SIM_G * other->mass) / softenedDistanceSq;
        totalAcceleration.x += accelerationMagnitude * (direction.x / distance);
        totalAcceleration.y += accelerationMagnitude * (direction.y / distance);
    }
    return totalAcceleration;
}

/*
  initPlanets initialise le système avec les vraies masses (en kg, ici réduites d'un facteur 1e?3)
  et d'autres paramètres d'affichage.

  Les valeurs "pos" servent ici de référence pour déterminer l'orbite relative.
  Par exemple, la Terre a un "pos" de 563, ce qui donne :
    orbitDistance = (563 - 540) * ORBIT_MULTIPLIER = 23 * 5 = 115 pixels
  Puis la vitesse initiale est calculée en fonction de la masse du Soleil fourni dans l'appel précédent.
*/
void initPlanets() {
    planetList = STD_LIST_CREATE(Planet, 0);
    pushNewPlanet("sun", 540.f, 0.f, 1.989e27, 50.f);
    pushNewPlanet("mercury", 547.f, 0.f, 3.3011e20, 5.f);
    pushNewPlanet("venus", 554.f, 0.f, 4.8675e21, 6.f);
    pushNewPlanet("earth", 563.f, 0.f, 5.97237e21, 6.f);
    pushNewPlanet("moon", 563.4f, 0.f, 7.342e19, 2.f);
    pushNewPlanet("mars", 573.f, 0.f, 6.4171e20, 4.f);
    pushNewPlanet("jupiter", 618.f, 0.f, 1.8982e24, 20.f);
    pushNewPlanet("saturn", 682.f, 0.f, 5.6834e23, 18.f);
    pushNewPlanet("uranus", 827.f, 0.f, 8.6810e22, 14.f);
    pushNewPlanet("neptune", 993.f, 0.f, 1.02413e23, 14.f);
    pushNewPlanet("pluto", 1120.f, 0.f, 1.303e19, 3.f);
}

/*
  updatePlanets met à jour la position de chaque corps selon la méthode d'Euler.
  Chaque planète voit sa vitesse et position modifiées par l'accélération calculée
  via computeAcceleration (qui cumule l'influence gravitationnelle de tous les autres).
*/
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

    // Démonstration de réinitialisation si besoin (par exemple en appuyant sur Tab)
    if (keyPressed(Tab)) {
        destroyPlanets();
        initPlanets();
    }
}

void displayPlanets(sfRenderWindow* window) {
    int n = planetList->size(planetList);
    for (int i = 0; i < n; i++) {
        Planet* body = planetList->getData(planetList, i);
        sfRenderWindow_drawCircleShape(window, body->shape, NULL);
    }
}

void destroyPlanets() {
    for (int i = 0; i < planetList->size(planetList); i++) {
        planetList->erase(&planetList, i);
    }
}