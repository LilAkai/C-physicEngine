#include "lilakai.h"

typedef struct Presset {
	sfCircleShape* shape;
	
	vec2f pos;
	vec2f velocity; //en Km
	float mass; //en Tonnes
	float radius; //en Km
	char* name;
}Presset;
typedef struct Planet{
	Presset sun;
	Presset mercury;
	Presset venus;
	Presset earth;
	Presset moon;
	Presset mars;
	Presset jupiter;
	Presset saturn;
	Presset uranus;
	Presset neptune;
	Presset pluto;
}Planet;
Planet planet;

void initPlanets();
void updatePlanets();
void displayPlanets(sfRenderWindow* window);
void destroyPlanets();