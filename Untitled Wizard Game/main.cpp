#include <iostream>
#include <raylib.h>
#include <raymath.h>

int main() {
	InitWindow(800, 800, "Untitled Wizard Game");
	SetTargetFPS(60);
	
	while (!WindowShouldClose()) {
		//game logic


		//draw
		BeginDrawing();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}