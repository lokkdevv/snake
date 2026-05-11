#include "raylib.h"
#include <stdio.h>

#define windowH 600
#define windowW 600
#define windowName "snake"

#define zoom 20
#define gridIntervalX (windowW/zoom)
#define gridIntervalY (windowH/zoom)
#define gridArea (gridIntervalX*gridIntervalY)

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
////////////////////////////////////////////

void drawGrid();
void drawKO();
void spawnFood(Vector2* food, Vector2 head);

int main()
{
	InitWindow(windowW, windowH, windowName);
	SetTargetFPS(60);

	char gameOver = 0;
	char changedDirection = 0;

	int Delta = 0;

	int frameCounter = 0;
	int moveInterval = 8;

	Vector2 head = {0, 0};
	Vector2 direction = {0, 0};
	Vector2 food = {0};

	Vector2 body[gridArea] = {0};
	int bodyIndex = 0;

	spawnFood(&food, head);
	while (!WindowShouldClose())
	{
		Delta = GetFrameTime();

		// Input //
		if      (IsKeyPressed(KEY_W) && direction.y!=1 && !changedDirection)
		{
			direction.x = 0;
			direction.y = -1;
			changedDirection = 1;
		}
		else if (IsKeyPressed(KEY_S) && direction.y!=-1 && !changedDirection)
		{
			direction.x = 0;
			direction.y = 1;
			changedDirection = 1;
		}
		else if (IsKeyPressed(KEY_A) && direction.x!=1 && !changedDirection)
		{
			direction.x = -1;
			direction.y = 0;
			changedDirection = 1;
		}
		else if (IsKeyPressed(KEY_D) && direction.x!=-1 && !changedDirection)
		{
			direction.x = 1;
			direction.y = 0;
			changedDirection = 1;
		}
		if (IsKeyPressed(KEY_R))
		{
			Vector2 zeroState = {0, 0};
			head = zeroState;
			direction = zeroState;
			gameOver = 0;
			spawnFood(&food, head);
			changedDirection = 0;
		}
		///////////

		// Collision //
		if (head.x > windowW || head.x < 0)
		{
			gameOver = 1;
		}
		if (head.y > windowH || head.y < 0)
		{
			gameOver = 1;
		}
		
		if (food.x == head.x && food.y == head.y)
		{
			spawnFood(&food, head);
			body[bodyIndex].x = head.x - direction.x;
			body[bodyIndex].y = head.y - direction.y;
			bodyIndex++;
		}
		///////////////

		// Movement //
		frameCounter++;
		if (frameCounter >= moveInterval && !gameOver)
		{
			head.x += direction.x * gridIntervalX;
			head.y += direction.y * gridIntervalY;
			for (int i = 0; i < bodyIndex; i++)
			{
				if (i==0)
				{
					body[i].x = head.x - direction.x;
					body[i].y = head.y + direction.y;
					continue;
				}
				body[i].x = body[i-1].x;
				body[i].y = body[i-1].y;
			}
			frameCounter = 0;
			changedDirection = 0;
		}
		//////////////

		// Drawing //
		BeginDrawing();
		ClearBackground(backCLR);
		drawGrid();

		DrawRectangle(food.x, food.y, gridIntervalX, gridIntervalY, foodCLR);
		DrawRectangle(head.x, head.y, gridIntervalX, gridIntervalY, headCLR);
		for (int i = 0; i < bodyIndex; i++)
		{
			DrawRectangle(body[i].x, body[i].y, gridIntervalX, gridIntervalY, bodyCLR);
		}

		if (gameOver)
		{
			drawKO();
		}

		EndDrawing();
		/////////////
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

void drawKO()
{
	const char* text = "Game Over";
	int textSize = 70;
	int textWidth = MeasureText(text, textSize);
	Color deathBlack = {0, 0, 0, 200};
	DrawRectangle(0, 0, windowW, windowH, deathBlack);
	DrawText(text, windowW/2-textWidth/2, windowH/2-textSize/2, textSize, RED);
}

void spawnFood(Vector2* food, Vector2 head)
{
	Vector2 randomPos = {GetRandomValue(0, windowW/(gridIntervalX)-1), GetRandomValue(0, windowH/(gridIntervalY)-1)};
	randomPos.x = gridIntervalX * (int)randomPos.x;
	randomPos.y = gridIntervalY * (int)randomPos.y;

	while(randomPos.x == head.x && randomPos.y == head.y)
	{
		randomPos.x = GetRandomValue(0, windowW/(gridIntervalX)-1);
		randomPos.y = GetRandomValue(0, windowH/(gridIntervalY)-1);
		randomPos.x = gridIntervalX * (int)randomPos.x;
		randomPos.y = gridIntervalY * (int)randomPos.y;
	}
	
	food->x = randomPos.x;
	food->y = randomPos.y;
}