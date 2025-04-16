#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "SFML/Graphics.h"
#include "SFML/Audio.h"
#include "SFML/System.h"
#include "CSTL/List.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <Windows.h>

#define NULL2f vec2f(0.f,0.f)
#define NULL2i vector2i(0,0)
#define printf_d(string, ...) DebugPrint(string, __VA_ARGS__)
#define dt getDeltaTime()

#define FOR_EACH_LIST(list, type, it_name, data_container_name, func) \
  for (int it_name = 0; it_name < list->size(list); it_name++) { \
    type* data_container_name = list->getData(list,it_name);\
    func }

extern const float sunGravity;
extern const float mercuryGravity;
extern const float venusGravity;
extern const float earthGravity;
extern const float moonGravity;
extern const float marsGravity;
extern const float jupiterGravity;
extern const float saturnGravity;
extern const float uranusGravity;
extern const float neptuneGravity;
extern const float plutoGravity;

typedef struct sfVector2d {
	double x;
	double y;
}sfVector2d;

#define PI 3.14159265358979323846264338327950288419716
#define RAD2DEG 57.295779f
#define DEG2RAD 0.017453f


extern const float e;
extern const float tau;
extern const float phi;
extern const float epsilon;
extern const double gravitionalConstant;

float mouseWheelDirection;
float dtMult;

#define vector2f sfVector2f
#define vector2i sfVector2i
#define WINDOWED sfDefaultStyle
#define BORDERLESS sfNone

vector2i mousePos;
vector2i globalMousePos;

#pragma region PS5
#define LSTICK_RIGHT(id) sfJoystick_getAxisPosition(id,sfJoystickX) >15
#define LSTICK_LEFT(id) -sfJoystick_getAxisPosition(id,sfJoystickX) >15
#define LSTICK_DOWN(id) sfJoystick_getAxisPosition(id,sfJoystickY) >15
#define LSTICK_UP(id) -sfJoystick_getAxisPosition(id,sfJoystickY) >15

//joystick droit
#define RSTICK_RIGHT(id) sfJoystick_getAxisPosition(id,sfJoystickU) >15
#define RSTICK_LEFT(id) -sfJoystick_getAxisPosition(id,sfJoystickU) >15
#define RSTICK_DOWN(id) sfJoystick_getAxisPosition(id,sfJoystickV) >15
#define RSTICK_UP(id) -sfJoystick_getAxisPosition(id,sfJoystickV) >15

#define RT(id) sfJoystick_getAxisPosition(id,sfJoystickZ)>10
#define LT(id) -sfJoystick_getAxisPosition(id,sfJoystickZ)>10
//DPAD
#define DPAD_RIGHT(id) sfJoystick_getAxisPosition(id,sfJoystickPovX) >15
#define DPAD_LEFT(id) -sfJoystick_getAxisPosition(id,sfJoystickPovX) >15
#define DPAD_DOWN(id) -sfJoystick_getAxisPosition(id,sfJoystickPovY) >15
#define DPAD_UP(id) sfJoystick_getAxisPosition(id,sfJoystickPovY) >15

#define A_PRESSED(id) sfJoystick_isButtonPressed(id,0)
#define B_PRESSED(id) sfJoystick_isButtonPressed(id,1)
#define X_PRESSED(id) sfJoystick_isButtonPressed(id,2)
#define Y_PRESSED(id) sfJoystick_isButtonPressed(id,3)
#define RB_PRESSED(id) sfJoystick_isButtonPressed(id,5)
#define LB_PRESSED(id) sfJoystick_isButtonPressed(id,4)
#define START_PRESSED(id) sfJoystick_isButtonPressed(id,7)
#define SELECT_PRESSED(id) sfJoystick_isButtonPressed(id,6)
#define RSTICK_PRESSED(id) sfJoystick_isButtonPressed(id,9)
#define LSTICK_PRESSED(id) sfJoystick_isButtonPressed(id,8)
#pragma endregion

#define keyPressed(id) sfKeyboard_isKeyPressed(sfKey##id)
#define scanPressed(id) sfKeyboard_isScancodePressed(sfScan##id)
#define mousePressed(id) sfMouse_isButtonPressed(sfMouse##id)

/*
@brief Check if the mouse is inside the sprite
@param _sprite: The sprite to check
*/
sfBool buttonBox(sfSprite* _sprite);

void DebugPrint(const char* const string, ...);

inline char* SOUND_PATH(const char* name) {
	const char* root = "../Resources/sounds/";
	const char* ext = ".wav";

	size_t len = strlen(root) + strlen(name) + strlen(ext) + 1;
	char* path = malloc(len);
	if (!path)
		return NULL;

	strcpy(path, root);
	strcat(path, name);
	strcat(path, ext);

	return path;
}
inline char* MUSIC_PATH(const char* name) {
	const char* root = "../Resources/musics/";
	const char* ext = ".ogg";

	size_t len = strlen(root) + strlen(name) + strlen(ext) + 1;
	char* path = malloc(len);
	if (!path)
		return NULL;

	strcpy(path, root);
	strcat(path, name);
	strcat(path, ext);

	return path;
}
inline sfTexture* getTexture(const char* name){
	const char* root = "../Resources/textures/";
	const char* ext = ".png";

	size_t len = strlen(root) + strlen(name) + strlen(ext) + 1;
	char* path = malloc(len);
	if (!path)
		return NULL;

	strcpy(path, root);
	strcat(path, name);
	strcat(path, ext);	

	return sfTexture_createFromFile(path, NULL);
}

void initTools();
void restartClock();
float getDeltaTime();

inline int iRand(int _min, int _max) {
	if (_max > _min)
		return rand() % (_max - _min + 1) + _min;
	else
		return _min;
}

#ifndef CLAMP
#define CLAMP(VAL, MIN, MAX) (((VAL) < (MIN)) ? (MIN) : (((VAL) > (MAX)) ? (MAX) : (VAL)))
#endif

/*
@brief Check if two circles are colliding
@param _pos1: The position of the first circle
@param _pos2: The position of the second circle
@param _rayon1: The radius of the first circle
@param _rayon2: The radius of the second circle
@return sfTrue if the circles are colliding, sfFalse otherwise
@note This function uses the Pythagorean theorem to check if the distance between the two circles is less than or equal to the sum of their radii.
*/
sfBool circleCollision(sfVector2f _pos1, sfVector2f _pos2, float _rayon1, float _rayon2);

/*
@brief Check if two rectangles are colliding
@param _box1: The first rectangle
@param _box2: The second rectangle
@return sfTrue if the rectangles are colliding, sfFalse otherwise
@note This function checks if the two rectangles overlap by checking their left, right, top, and bottom edges.
*/
sfBool Rectangle_Collision(sfFloatRect _box1, sfFloatRect _box2);

inline bool PointInCircle(sfVector2f _pos, sfVector2f _circle_pos, float _rayon)
{
	return ((_pos.x - _circle_pos.x) * (_pos.x - _circle_pos.x) + (_pos.y - _circle_pos.y) * (_pos.y - _circle_pos.y) < _rayon * _rayon);
}

/*
@brief Check if a circle is colliding with a rectangle
@param pos: The position of the circle
@param radius: The radius of the circle
@param _rect: The rectangle to check
@return sfTrue if the circle is colliding with the rectangle, sfFalse otherwise
@note This function checks if the distance between the circle and the rectangle is less than or equal to the radius of the circle.
*/
inline sfBool CircleRect_Collision(sfVector2f pos, float radius, sfFloatRect _rect){
	float testX = pos.x;
	float testY = pos.y;

	if (pos.x < _rect.left) testX = _rect.left;
	else if (pos.x > _rect.left + _rect.width) testX = _rect.left + _rect.width;
	if (pos.y < _rect.top) testY = _rect.top;
	else if (pos.y > _rect.top + _rect.height) testY = _rect.top + _rect.height;

	float distX = pos.x - testX;
	float distY = pos.y - testY;
	float distance = (float)sqrt((distX * distX) + (distY * distY));

	if (distance <= radius) {
		return sfTrue;
	}
	return sfFalse;
}

/*
@brief Create a sfFloatRect
@param _left: The left position of the rectangle
@param _top: The top position of the rectangle
@param _width: The width of the rectangle
@param _height: The height of the rectangle
@return A sfFloatRect with the given parameters
*/
sfFloatRect FlRect(float _left, float _top, float _width, float _height);

/*
* @brief Create a sfIntRect
* @param _left: The left position of the rectangle
* @param _top: The top position of the rectangle
* @param _width: The width of the rectangle
* @param _height: The height of the rectangle
* @return A sfIntRect with the given parameters
*/
sfIntRect IntRect(int _left, int _top, int _width, int _height);

/*
@brief Check if two floats are approximately equal
@param _a: The first float
@param _b: The second float
@return true if the floats are approximately equal, false otherwise
@note This function uses a tolerance value to check if the two floats are approximately equal. The tolerance is based on the value of the first float and a small epsilon value.
*/
inline bool isApproxEqualf(float _a, float _b) {
	if (_a == _b) return true;

	float tolerance = epsilon * fabsf(_a);
	if (tolerance < epsilon) tolerance = epsilon;

	return (fabsf(_a - _b) < tolerance);
}

/*
@brief Check if two sfVector2f are approximately equal
@param _x: The first sfVector2f
@param _y: The second sfVector2f
@return true if the sfVector2f are approximately equal, false otherwise
@note This function uses the isApproxEqualf function to check if the x and y components of the two sfVector2f are approximately equal.
*/
inline bool isApproxEqual2f(sfVector2f _x, sfVector2f _y) {
	return isApproxEqualf(_x.x, _y.x) && isApproxEqualf(_x.y, _y.y);
}

/*
@brief create a random
@return color with random RGB values
*/
inline sfColor randomColor() {
	sfColor tmp = sfColor_fromRGB(iRand(25,255),iRand(25,255),iRand(25,255));	
	return tmp; 
}

/*
@brief Create a sfVector2f
@param a: The x component of the vector
@param b: The y component of the vector
@return A sfVector2f with the given parameters
*/
inline vector2f vec2f(float a, float b) {
	sfVector2f tmp = { a, b };
	return tmp;
}

/*
@brief Create a sfVector2i
@param a: The x component of the vector
@param b: The y component of the vector
@return A sfVector2i with the given parameters
*/
inline vector2i vec2i(int a, int b) {
	sfVector2i tmp = { a, b };
	return tmp;
}

inline vector2i vec2f2i(vector2f vec) {
	vector2i tmp = vec2i(vec.x,vec.y);
	return tmp;
}
inline vector2f vec2i2f(vector2i vec) {
	vector2f tmp = vec2f(vec.x,vec.y);
	return tmp;
}

/*
@brief Add two sfVector2f
@param a: The first vector
@param b: The second vector
@return A sfVector2f with the sum of the two vectors
*/
inline vector2f addVec2f(vector2f a, vector2f b) {
	return (sfVector2f) { a.x + b.x, a.y + b.y };
}

/*
@brief Subtract two sfVector2f
@param a: The first vector
@param b: The second vector
@return A sfVector2f with the difference of the two vectors
*/
inline vector2f subVec2f(vector2f a, vector2f b) {
	return (sfVector2f) { a.x - b.x, a.y - b.y };
}

/*
@brief Multiply a sfVector2f by a float
@param a: The vector to multiply
@param b: The float to multiply by
@return A sfVector2f with the product of the vector and the float
*/
inline vector2f multiplyVec2f(vector2f a, float b) {
	return (sfVector2f) { a.x* b, a.y* b };
}

/*
@brief Divide a sfVector2f by a float
@param a: The vector to divide
@param b: The float to divide by
@return A sfVector2f with the quotient of the vector and the float
*/
inline vector2f divideVec2f(vector2f a, float b) {
	return (sfVector2f) { a.x / b, a.y / b };
}

/*
@brief Get the magnitude of a sfVector2f
@param vec: The vector to get the magnitude of
@return The magnitude of the vector
*/
inline float getMagnitude(vector2f vec){
	return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
}

/*
@brief Normalize a sfVector2f
@param vec: The vector to normalize
@return A normalized sfVector2f 
*/
inline vector2f normalizeVec2f(vector2f vec){
	float magnitude = getMagnitude(vec);
	if (magnitude == 0.f)
		return (sfVector2f) { 0.f, 0.f };
	return divideVec2f(vec, magnitude);
}

/*
@brief Get the dot product of two sfVector2f
@param vec1: The first vector
@param vec2: The second vector
@return The dot product of the two vectors
*/
inline float dotProduct(vector2f vec1, vector2f vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

/*
@brief Linear interpolation between two floats
@param a: The first float
@param b: The second float
@param t: The interpolation factor
@return The interpolated float
*/
inline float lerp(float a, float b, float t) {
	return (b - a) * t + a;
}
/*
@brief Linear interpolation between two sfVector2f
@param vec1: The first vector
@param vec2: The second vector
@param t: The interpolation factor
@return The interpolated vector

*/
inline vector2f lerpVec(vector2f vec1, vector2f vec2, float t) {
	return  (sfVector2f) { lerp(vec1.x, vec2.x, t), lerp(vec1.y, vec2.y, t) };
}
/*
@brief Convert polar coordinates to euclidean coordinates
@param _polCoords: The polar coordinates to convert
@return The euclidean coordinates
*/
inline sfVector2f polCoordsToEuclCoords(sfVector2f _polCoords){
	return ((sfVector2f) { _polCoords.x* (cosf(_polCoords.y)), _polCoords.x* (sinf(_polCoords.y)) });
}

inline sfVector2f GetVectorFromAngle(sfVector2f pos, float lenght, float angle){
	angle *= DEG2RAD;

	float x = pos.x + lenght * cosf(angle);
	float y = pos.y + lenght * sinf(angle);

	return vec2f(x, y);
}


/*inline bool unitTestCreateVector(vec2f a, vec2f b, vec2f expected);
inline bool unitTestAddVector(vec2f a, vec2f b, vec2f expected);
inline bool unitTestSubVector(vec2f a, vec2f b, vec2f expected);
inline bool unitTestMultiplyVector(vec2f a, float b, vec2f expected);
inline bool unitTestDivideVector(vec2f a, float b, vec2f expected);
inline bool unitTestGetMagnitude(vec2f _vec, vec2f expected);
inline bool unitTestNormalize(vec2f _vec, vec2f expected);
inline bool unitTestDotProduct(vec2f _vec1,vec2f _vec2, vec2f expected);
inline bool unitTestLerp(float a, float b, float t, float expected);
inline bool unitTestLerpVector(vec2f _vec1, vec2f _vec2, float t, vec2f expected);*/

#pragma region Dorian
// \short Signs any real value
const float sign(const float _val);

float moveToward(float _from, float _to, float _step); // step is always absolute
#pragma endregion

#pragma region Dono
int isTextHovered(sfText* _text, sfVector2i _mousePos);
#pragma endregion