#include <iostream>
#include <raylib.h>
#include <raymath.h>

//in the beginning god created the heavens and the earth (START)
/*
* make a basic plane to walk on
* add a player
* add collision objects
* grid align the objects
* these objects will be "blocks", and the grid will be made of "tiles"
*/

//And so man learned to create (BLOCKS)
/*
* make blocks be able to be colored
* make blocks able to take up multiple tiles
* make blocks placeable
* make blocks breakable
* make blocks swappable (?)
* make blocks interactable
*/

//Man revolted, and so God revoked their godly status (ITEMS) [WIP]
/*
* force blocks to come from items
* make items
* make items do different things
*/

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