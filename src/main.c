#include "raylib.h"

#define windowH 600
#define windowW 600
#define windowName "snake"

#define zoom 20
#define gridIntervalX windowW/zoom
#define gridIntervalY windowH/zoom

////////////////////////////////////////////
const Color backCLR = {6, 214, 160, 255};
const Color lightbackCLR = {102, 255, 215, 255};
////////////////////////////////////////////
const Color bodyCLR = {17, 138, 178, 255};
const Color headCLR = {7, 59, 76, 255};
////////////////////////////////////////////
const Color foodCLR = {239, 71, 111, 255};
const Color powerCLR = {255, 209, 102, 255};
////////////////////////////////////////////

Color colors[] = {backCLR, lightbackCLR, bodyCLR, headCLR, foodCLR, powerCLR};

void drawGrid();

int main()
{
	InitWindow(windowW, windowH, windowName);
	SetTargetFPS(60);

	int frameCounter = 0;
	int moveInterval = 4;

	Vector2 head = {0, 0};
	Vector2 direction = {0, 0};

	while (!WindowShouldClose())
	{
		// Input //
		if      (IsKeyPressed(KEY_W) && direction.y!=1)
		{
			direction.x = 0;
			direction.y = -1;
		}
		else if (IsKeyPressed(KEY_S) && direction.y!=-1)
		{
			direction.x = 0;
			direction.y = 1;
		}
		else if (IsKeyPressed(KEY_A) && direction.x!=1)
		{
			direction.x = -1;
			direction.y = 0;
		}
		else if (IsKeyPressed(KEY_D) && direction.x!=-1)
		{
			direction.x = 1;
			direction.y = 0;
		}
		
		frameCounter++;
		if (frameCounter >= moveInterval)
		{
			head.x += direction.x * gridIntervalX;
			head.y += direction.y * gridIntervalY;
			frameCounter = 0;
		}

		BeginDrawing();
		ClearBackground(backCLR);
		
		drawGrid();

		DrawRectangle(head.x, head.y, gridIntervalX, gridIntervalY, headCLR);

		EndDrawing();
	}
	

	CloseWindow();
	return 0;
}

void drawGrid()
{
	for (int i = 0; i < windowW; i += gridIntervalX)
		DrawLine(i, 0, i, windowH, lightbackCLR);
	for (int i = 0; i < windowH; i += gridIntervalY)
		DrawLine(0, i, windowW, i, lightbackCLR);
}