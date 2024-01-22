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
* Create distinction between tiles and blocks
*	TILE: invisible, can be occupied, solid, stores root of block
*	BLOCK: visible, interactable
* make blocks be able to be colored..............DONE
* make blocks able to take up multiple tiles.....DONE
* make blocks placeable..........................DONE
* make blocks breakable..........................TODO
* make blocks swappable (?)......................TODO
* make blocks interactable.......................TODO
*/

//Man revolted, and so God revoked their godly status (ITEMS) [WIP]
/*
* force blocks to come from items
* make items
* make items do different things
*/

class Block {
	Color clr{ BLACK };
	int tileWidth{1};
	int tileHeight{1};
};

struct Tile {
	Rectangle hitbox{ 0.0f, 0.0f, 0.0f, 0.0f };
	bool occupied{ false };
	bool solid{ false };

	bool isRoot{ false };
	int sourceX{ -1 };
	int sourceY{ -1 };
	int blockWidth{ -1 };
	int blockHeight{ -1 };
};

class Tilemap {
	std::vector<std::vector<Tile>> grid;
	int tileDims = 25;

public:
	Tilemap() {

	}

	Tilemap(int gridDims, int tileDims) {
		set_tileDims(tileDims);
		set_gridDims(gridDims);	
	}

	//GETTERS
	const std::vector<std::vector<Tile>>& data() {
		return grid;
	}

	Tile& at(int x, int y) {
		return grid.at(y).at(x);
	}

	int get_dims() {
		return grid.size();
	}



	//SETTERS
	void set_gridDims(int gridDims) {
		std::cout << "tile dims: " << tileDims << "\n";
		
		grid.resize(gridDims);
		for (auto& row : grid) {
			row.resize(gridDims);
		}

		for (int y = 0; y < gridDims; y++) {
			for (int x = 0; x < gridDims; x++) {
				at(x, y).hitbox.x = (float)(x * tileDims); //{ (float)(x * tileDims), (float)(y * tileDims), (float)tileDims, (float)tileDims };
				at(x, y).hitbox.y = (float)(y * tileDims);
				at(x, y).hitbox.width = (float)(tileDims);
				at(x, y).hitbox.height = (float)(tileDims);
			}
		}
	}

	void set_tileDims(int tileDims) {
		this->tileDims = tileDims;
		std::cout << "tile dims: " << this->tileDims << "\n";
	}

	void set_occupy(int x, int y, bool state) {
		at(x, y).occupied = state;
	}

	void set_solid(int x, int y, bool state) {
		at(x, y).solid = state;
	}

	/*void randomize(double p) {
		for (int y = 0; y < 25; y++) {
			for (int x = 0; x < 25; x++) {
				if (GetRandomValue(0, 3) == 0) {
					boxGrid.at(y).at(x) = { (float)x * 25.0f, (float)y * 25.0f, 25.0f, 25.0f };
				}
			}
		}
	}*/

	/*void drawAll() {
		for (auto& row : grid) {
			for (auto& r : row) {
				DrawRectangleRec(r, DARKBLUE);
			}
		}
	}*/
};

class Blockmap {
	Tilemap tiles;
	
public:
	Blockmap() {

	}

	Blockmap(int gridDims, int tileDims) {
		tiles.set_gridDims(gridDims);
		tiles.set_tileDims(tileDims);
	}

	Tilemap& get_map() {
		return tiles;
	}

	void place(int x, int y, int width, int height, bool solid) {
		if (isRegionOccupied(x, y, width, height)) return;

		tiles.at(x, y).isRoot = true;
		tiles.at(x, y).blockWidth = width;
		tiles.at(x, y).blockHeight = height;

		for (int Y = y; Y < y + height; Y++) {
			for (int X = x; X < x + width; X++) {
				tiles.set_occupy(X, Y, true);
				tiles.set_solid(X, Y, solid);
				tiles.at(X, Y).sourceX = x;
				tiles.at(X, Y).sourceY = y;

				std::cout << "x, y: " << x << ", " << y << ": source: " << tiles.at(X, Y).sourceX << ", " << tiles.at(X, Y).sourceY << "\n";
			}
		}
	}

	void destroy(int x, int y) {
		Tile& clicked = tiles.at(x, y);
		if (clicked.occupied == false) return;
		
		Tile& root = tiles.at(clicked.sourceX, clicked.sourceY);
		std::cout << "root pos: " << root.sourceX << ", " << root.sourceY << "\n";
		
		int sX = root.sourceX;
		int sY = root.sourceY;
		int bH = root.blockHeight;
		int bW = root.blockWidth;

		for (int Y = sY; Y < sY + bH; Y++) {
			for (int X = sX; X < sX + bW; X++) {
				std::cout << "removing pos: " << X << ", " << Y << "\n";

				tiles.set_occupy(X, Y, false);
				tiles.set_solid(X, Y, false);
				tiles.at(X, Y).sourceX = -1;
				tiles.at(X, Y).sourceY = -1;
			}
		}
	}

private:
	bool isRegionOccupied(int x, int y, int width = 1, int height = 1) {
		for (int Y = y; Y < y + height; Y++) {
			for (int X = x; X < x + width; X++) {
				if (tiles.at(X, Y).occupied == true) return true;
			}
		}
		return false;
	}
};

class Player {
	Rectangle hitbox{ 0, 0, 25, 25 };
	Tilemap* map;
	//std::vector<std::vector<Rectangle>>* collisionObjects;

public:
	Player(Tilemap* tiles) {
		map = tiles;
	}

	void move() {
		if (IsKeyDown(KeyboardKey::KEY_W)) {
			hitbox.y -= 5;
			checkCollision(hitbox.y, -5);
		}
		if (IsKeyDown(KeyboardKey::KEY_A)) {
			hitbox.x -= 5;
			checkCollision(hitbox.x, -5);
		}
		if (IsKeyDown(KeyboardKey::KEY_S)) {
			hitbox.y += 5;
			checkCollision(hitbox.y, 5);
		}
		if (IsKeyDown(KeyboardKey::KEY_D)) {
			hitbox.x += 5;
			checkCollision(hitbox.x, 5);
		}
	}

	void checkCollision(float& var, float oSpeed) {
		for (auto& row : map->data()) {
			for (auto& r : row) {
				if (!r.solid) continue;
				if (CheckCollisionRecs(hitbox, r.hitbox)) {
					var += oSpeed *= -1;
					break;
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

	//Tilemap tiles(25, 25);
	Blockmap blocks(25, 25);
	/*for (int y = 0; y < tiles.get_dims(); y++) {
		for (int x = 0; x < tiles.get_dims(); x++) {
			if (GetRandomValue(0, 3) == 0) {
				tiles.set_occupy(x, y, true);
				tiles.set_solid(x, y, (bool)GetRandomValue(0, 1));
			}
		}
	}*/
	Player player(&(blocks.get_map()));
	
	while (!WindowShouldClose()) {
		//game logic
		player.move();

		if (IsKeyPressed(KeyboardKey::KEY_P)){
			int x, y, width, height, solid;
			std::cin >> x >> y >> width >> height >> solid;

			blocks.place(x, y, width, height, (bool)solid);
		}

		if (IsKeyPressed(KeyboardKey::KEY_L)) {
			int x, y;
			std::cin >> x >> y;

			blocks.destroy(x, y);
		}

		//draw
		BeginDrawing();
		ClearBackground(DARKGREEN);

		//draw solid and unsolid tiles as different colors
		for (auto& row : blocks.get_map().data()) {
			for (auto& r : row) {
				if (r.occupied == false) continue;
				
				if (r.solid == true) {
					DrawRectangleRec(r.hitbox, DARKBLUE);
				}
				else {
					DrawRectangleRec(r.hitbox, BLUE);
				}
			}
		}

		player.draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}