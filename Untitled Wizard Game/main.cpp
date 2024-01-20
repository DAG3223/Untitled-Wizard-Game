#include <iostream>
#include <vector>
#include <raylib.h>
#include <raymath.h>

//in the beginning god created the heavens and the earth (START)
/*
* make a basic plane to walk on ...........................................................DONE
* add a player ............................................................................DONE
* add collision objects ...................................................................DONE
* grid align the objects ..................................................................DONE
* these objects will be "blocks", and the grid will be made of "tiles" ....................WOOHOO!
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

class Player {
	Rectangle hitbox{ 0, 0, 25, 25 };
	std::vector<std::vector<Rectangle>>* collisionObjects;

public:
	Player(std::vector<std::vector<Rectangle>>* objects) {
		collisionObjects = objects;
	}

	void move() {
		if (IsKeyDown(KeyboardKey::KEY_W)) {
			hitbox.y -= 5;

			for (auto& row : *collisionObjects) {
				for (auto& r : row) {
					if (CheckCollisionRecs(hitbox, r)) {
						hitbox.y += 5;
						break;
					}
				}
			}
		}
		if (IsKeyDown(KeyboardKey::KEY_A)) {
			hitbox.x -= 5;

			for (auto& row : *collisionObjects) {
				for (auto& r : row) {
					if (CheckCollisionRecs(hitbox, r)) {
						hitbox.x += 5;
						break;
					}
				}
			}
		}
		if (IsKeyDown(KeyboardKey::KEY_S)) {
			hitbox.y += 5;

			for (auto& row : *collisionObjects) {
				for (auto& r : row) {
					if (CheckCollisionRecs(hitbox, r)) {
						hitbox.y -= 5;
						break;
					}
				}
			}
		}
		if (IsKeyDown(KeyboardKey::KEY_D)) {
			hitbox.x += 5;

			for (auto& row : *collisionObjects) {
				for (auto& r : row) {
					if (CheckCollisionRecs(hitbox, r)) {
						hitbox.x -= 5;
						break;
					}
				}
			}
		}
	}

	void draw() {
		DrawRectangleRec(hitbox, RED);
	}
};

int main() {
	InitWindow(800, 800, "Untitled Wizard Game");
	SetTargetFPS(60);

	std::vector<std::vector<Rectangle>> boxGrid;

	boxGrid.resize(25);
	for (auto& row : boxGrid) {
		row.resize(25);
	}

	Player player(&boxGrid);
	
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 25; x++) {
			if (GetRandomValue(0, 3) == 0) {
				boxGrid.at(y).at(x) = { (float)x * 25.0f, (float)y * 25.0f, 25.0f, 25.0f };
			}
		}
	}

	while (!WindowShouldClose()) {
		//game logic
		player.move();

		//draw
		BeginDrawing();
		ClearBackground(DARKGREEN);

		player.draw();

		for (auto& row : boxGrid) {
			for (auto& r : row) {
				DrawRectangleRec(r, DARKBLUE);
			}
		}

		/*for (auto& r : boxes) {
			DrawRectangleRec(r, DARKBLUE);
		}*/

		EndDrawing();
	}

	CloseWindow();
	return 0;
}