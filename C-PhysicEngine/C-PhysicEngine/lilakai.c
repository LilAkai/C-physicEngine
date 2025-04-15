#include "lilakai.h"

sfTime sftime;
sfClock* sfclock;

const float e = 2.71828f;
const float tau = 6.28318f;
const float phi = 1.61803f;
const float epsilon = 0.00001f;


const float sunGravity = 27400.f; // 274 m/s^2
const float mercuryGravity = 377.f; // 3.7 m/s^2
const float venusGravity = 910.f; // 8.87 m/s^2
const float earthGravity = 980.f; // 9.8 m/s^2
const float moonGravity = 162.f; // 1.62 m/s^2
const float marsGravity = 370.f; // 3.7 m/s^2
const float jupiterGravity = 2495.f; // 24.79 m/s^2
const float saturnGravity = 1070.f; // 10.44 m/s^2
const float uranusGravity = 890.f; // 8.69 m/s^2
const float neptuneGravity = 1100.f; // 11.15 m/s^2
const float plutoGravity = 620.f; // 6.2 m/s^2

sfBool buttonBox(sfSprite* _sprite) {
	if ((mousePos.x > sfSprite_getPosition(_sprite).x && mousePos.x < sfSprite_getPosition(_sprite).x + sfSprite_getTextureRect(_sprite).width) && (mousePos.y > sfSprite_getPosition(_sprite).y && mousePos.y < sfSprite_getPosition(_sprite).y + sfSprite_getTextureRect(_sprite).height))
		return true;
	else return false;
}

void DebugPrint(const char* const string, ...){
#ifdef _DEBUG
	va_list args;
	va_start(args, string);
	vprintf(string, args);
	va_end(args);
#endif // _DEBUG
}

void initTools(){
	sfclock = sfClock_create();
	srand(time(NULL));
}

void restartClock(){
	sftime = sfClock_restart(sfclock);
}

float getDeltaTime(){
	if (sfTime_asSeconds(sftime) < 0.1f)
		return sfTime_asSeconds(sftime);
	else return 0.1f;
}

sfBool circleCollision(sfVector2f _pos1, sfVector2f _pos2, float _radius1, float _radius2){
	sfVector2f dist = { _pos1.x - _pos2.x,_pos1.y - _pos2.y };
	if ((dist.x * dist.x) + (dist.y * dist.y) <= (_radius1 + _radius2) * (_radius1 + _radius2))
		return true;
	return false;
}
sfBool Rectangle_Collision(sfFloatRect _box1, sfFloatRect _box2)
{
	if ((_box2.left >= _box1.left + _box1.width)
		|| (_box2.left + _box2.width <= _box1.left)
		|| (_box2.top >= _box1.top + _box1.height)
		|| (_box2.top + _box2.height <= _box1.top))
		return false;
	else
		return true;
}
sfFloatRect FlRect(float _left, float _top, float _width, float _height){
	sfFloatRect rectTmp = { _left, _top,  _width, _height };
	return rectTmp;
}

sfIntRect IntRect(int _left, int _top, int _width, int _height){
	sfIntRect rectTmp = { _left, _top,  _width, _height };
	return rectTmp;		
}

#pragma region Dorian
const float sign(const float val){
	return val > 0 ? +1.0f : (val < 0 ? -1.0f : 0.0f);
}

float moveToward(float from, float to, float step){ // step is always absolute
	return abs(to - from) <= step ? to : from + sign(to - from) * step;
}
#pragma endregion

#pragma region Dono
int isTextHovered(sfText* text, sfVector2i mousePos){
	sfFloatRect textBounds = sfText_getGlobalBounds(text); // Recupere les limites
	return sfFloatRect_contains(&textBounds, mousePos.x, mousePos.y); // Verifie si la souris est sur le texte
}
#pragma endregion