#include "pch.h"

int main() {
	int screenWidth = 800;
	int screenHeight = 450;
	int i = 0;
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Template is working.", 190, 200, 20, RED);

		EndDrawing();
	}

	CloseWindow();        // Close window and OpenGL context

	return 0;
}