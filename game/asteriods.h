#ifndef ASTEROID_H_
#define ASTEROID_H_

#include <raylib.h>

typedef enum AsteroidSize
{
	SMALL = 1,
	MEDIUM = 2,
	LARGE = 4,
}AsteroidSize;

#define ASTEROID_ROT_SPEED_MIN 5
#define ASTEROID_ROT_SPEED_MAX 240

typedef struct Asteroid
{
	bool active;
	Vector2 position;
	float rotation;
	float rotationSpeed;
	Vector2 velocity;
	AsteroidSize size;
}Asteroid;

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity,AsteroidSize size);
void UpdateAsteroid(Asteroid* asteroid, float frametime);
void AsteroidDraw(Asteroid asteroid);
#endif