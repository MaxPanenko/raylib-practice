#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "asteriods.h"
#include "asteriods.c"

const int width = 600;
const int height = 600;
const Vector2 screenCenter = {width / 2,height / 2};

#define MAX_ASTEROIDS 64
#define ASTEROID_RANDOM_ANGLE 30 * DEG2RAD
#define ASTEROID_SPEED_MIN 100
#define ASTEROID_SPEED_MAX 300

static Asteroid _asteroids[MAX_ASTEROIDS] = {0};
static AsteroidSize _sizes[] = {SMALL,MEDIUM,LARGE};

void UpdateDrawFrame(void);
void AsteroidAdd(Vector2 position, AsteroidSize size);
Vector2 GetNextAsteroidPositon(void);

int main()
{
	srand(time(0));

	InitWindow(width,height,"Game");

	while(!WindowShouldClose())
	{
		UpdateDrawFrame();
	}

	CloseWindow();

	return 0;

}

void UpdateDrawFrame(void)
{
	float frametime = GetFrameTime();
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		UpdateAsteroid(_asteroids + i,frametime);
	}

	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		AsteroidSize nextSize = _sizes[GetRandomValue(0,2)];
		TraceLog(LOG_INFO,"Next Size: %d",(int)nextSize);
		AsteroidAdd(GetNextAsteroidPositon(), nextSize);
	}

	BeginDrawing();

		ClearBackground(BLACK);

		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			AsteroidDraw(_asteroids[i]);
		}

	EndDrawing();
}

void AsteroidAdd(Vector2 position, AsteroidSize size)
{
	bool created = false;
	Vector2 velocity = Vector2Subtract(screenCenter,position);
	velocity = Vector2Scale(Vector2Normalize(velocity),GetRandomValue(ASTEROID_SPEED_MIN,ASTEROID_SPEED_MAX));
	velocity = Vector2Rotate(velocity, (float)GetRandomValue(-ASTEROID_RANDOM_ANGLE, ASTEROID_RANDOM_ANGLE));

	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		if(_asteroids[i].active)
		{
			continue;
		}

		_asteroids[i] = CreateAsteroid(position,velocity,size);
		created = true;
		break;
	}

	if(!created)
	{
		TraceLog(LOG_ERROR, "Failed");
	}
}

Vector2 GetNextAsteroidPositon(void)
{
	Vector2 result = {-128,128};

	if(GetRandomValue(0,1))
	{
		if(GetRandomValue(0,1))
		{
			result.y = width + 128;
		}

		result.x = GetRandomValue(-128, 128 + width);
		
	}
	else
	{
		if(GetRandomValue(0,1))
		{
			result.x = width + 128;
		}

		result.y = GetRandomValue(-128, 128 + width);
	}

	return result;
}