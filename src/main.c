#include "raylib.h"
#include <stdio.h>

#define windowH 600
#define windowW 600
#define windowName "snake+"

#define zoom 20
#define gridIntervalX (windowW/zoom)
#define gridIntervalY (windowH/zoom)
#define gridArea (gridIntervalX*gridIntervalY)

////////////////////////////////////////////
const Color backCLR = {6, 214, 160, 255};
const Color lightbackCLR = {102, 255, 215, 255};
const Color bodyCLR = {17, 138, 178, 255};
const Color headCLR = {7, 59, 76, 255};
const Color foodCLR = {239, 71, 111, 255};
const Color powerCLR = {255, 209, 102, 255};
////////////////////////////////////////////

void drawGrid();
void drawKO();
void spawnFood(Vector2* food, Vector2 head, Vector2* body, int bodyIndex);

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

	spawnFood(&food, head, body, bodyIndex);
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
			bodyIndex = 0;
			spawnFood(&food, head, body, bodyIndex);
		}
		///////////

		frameCounter++;
		if (frameCounter >= moveInterval && !gameOver && (direction.x != 0 || direction.y != 0))
		{
			Vector2 prevHead = head;

			// Move head
			head.x += direction.x * gridIntervalX;
			head.y += direction.y * gridIntervalY;

			// Boundary collision
			if (head.x >= windowW || head.x < 0 || head.y >= windowH || head.y < 0) {
				gameOver = true;
			}

			// Body collision and follow Logic
			for (int i = bodyIndex - 1; i >= 0; i--) {
				if (head.x == body[i].x && head.y == body[i].y) gameOver = true;
				
				if (i == 0) body[i] = prevHead;
				else body[i] = body[i-1];
			}

			// Food collision
			if (head.x == food.x && head.y == food.y) {
				bodyIndex++;
				if(bodyIndex > 1) body[bodyIndex-1] = body[bodyIndex-2];
				else body[0] = prevHead;
				
				spawnFood(&food, head, body, bodyIndex);
			}

			frameCounter = 0;
			changedDirection = false;
		}

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

void spawnFood(Vector2* food, Vector2 head, Vector2* body, int bodyIndex) {
	bool validPos = false;
	while (!validPos) {
		food->x = GetRandomValue(0, zoom - 1) * gridIntervalX;
		food->y = GetRandomValue(0, zoom - 1) * gridIntervalY;
		
		validPos = true;
		if (food->x == head.x && food->y == head.y) validPos = false;
		for (int i = 0; i < bodyIndex; i++) {
			if (food->x == body[i].x && food->y == body[i].y) {
				validPos = false;
				break;
			}
		}
	}
}