#include "asteriods.h"
#include "raymath.h"

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size)
{
	return (Asteroid)
	{
		.active = true,
		.position = position,
		.velocity = velocity,
		.size = size,
		.rotation = GetRandomValue(0, 360),
		.rotationSpeed = GetRandomValue(ASTEROID_ROT_SPEED_MIN, ASTEROID_ROT_SPEED_MAX)
	};
}


void UpdateAsteroid(Asteroid* asteroid, float frametime)
{
	if(!asteroid->active)
	{
		return;
	}

	asteroid->position = Vector2Add(asteroid->position,
	Vector2Scale(asteroid->velocity,frametime));
	asteroid->rotation += asteroid->rotationSpeed * frametime;
	
}

void AsteroidDraw(Asteroid asteroid)
{
	if (!asteroid.active)
	{
		return;
	}

	DrawPolyLines(asteroid.position,3,16 *(int)(asteroid.size),asteroid.rotation,WHITE);
}