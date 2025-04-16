#include "lilakai.h"

typedef struct Planet {
	sfCircleShape* shape;
	
	vector2f pos;
	vector2f velocity; //en Km/h
	double mass; //en tonnes
	float radius; //en Km
	const char* name; 
	
	vector2f* history;
    int historyIndex;
    int historySize;
}Planet;
stdList* planetList;

void initPlanets();
void updatePlanets();
void displayPlanets(sfRenderWindow* window);
void destroyPlanets();

vector2f computeAcceleration(Planet* planet);
