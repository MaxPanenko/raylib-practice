#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "asteriods.h"
#include "asteriods.c"

const int width = 600;
const int height = 600;
const Vector2 screensize = {width,height};

#define MAX_ASTEROIDS 64
static Asteroid _asteroids[MAX_ASTEROIDS] = {0};

void UpdateDrawFrame(void);
void AsteroidAdd(Vector2 position, Vector2 velocity, AsteroidSize size);

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
		AsteroidAdd(GetMousePosition(),(Vector2){200,0},SMALL);
	}

	BeginDrawing();

		ClearBackground(BLACK);

		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			AsteroidDraw(_asteroids[i]);
		}

	EndDrawing();
}

void AsteroidAdd(Vector2 position, Vector2 velocity, AsteroidSize size)
{
	bool created = false;

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