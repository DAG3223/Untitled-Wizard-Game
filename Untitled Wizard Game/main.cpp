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
* make blocks breakable..........................DONE
* make blocks interactable.......................TODO
*/

//Man revolted, and so God revoked their godly status (ITEMS) [WIP]
/*
* force blocks to come from items
* make items
* make items do different things
*/

struct BlockAttributes {
	Color clr{};
	int tileWidth{};
	int tileHeight{};
	bool solid{false};
};

class Block {
	BlockAttributes attr;
	
	int tileX;
	int tileY;

public:
	Block() {

	}

	void set_tileX(int x) {
		tileX = x;
	}

	void set_tileY(int y) {
		tileY = y;
	}

	int get_tileX() {
		return tileX;
	}

	int get_tileY() {
		return tileY;
	}

	const BlockAttributes& get_attr() {
		return attr;
	}


	/*Color clr{ BLACK };
	int tileWidth{1};
	int tileHeight{1};
	bool solid{ false };*/
};

struct Tile {
	Rectangle hitbox{ 0.0f, 0.0f, 0.0f, 0.0f };
	Block* occupant{ nullptr };

	//bool occupied{ false }; //if occupant is nullptr, occupied is false
	//bool solid{ false }; //return solidity of occupant



	/*bool isRoot{ false }; //doesn't matter
	int sourceX{ -1 }; //occupant remembers its tile X and y
	int sourceY{ -1 };

	Block* blockData{ nullptr };*/
	/*int blockWidth{ -1 }; //occupant knows its tile width and height
	int blockHeight{ -1 };*/
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

	size_t get_dims() {
		return grid.size();
	}



	//SETTERS
	void set_gridDims(int gridDims) {
		//std::cout << "tile dims: " << tileDims << "\n";
		
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
	}

	int get_tileDims() {
		return tileDims;
	}

	bool isOccupied(int x, int y) {
		return at(x, y).occupant != nullptr;
	}

	//void set_occupy(int x, int y, bool state) {
	//	//at(x, y).occupied = state;
	//}

	/*void set_solid(int x, int y, bool state) {
		at(x, y).solid = state;
	}*/


	//Grid and Index Alignment
	//modifies value to snapped value tile grid
	//void gridSnapValue(float& n) {
	//	n = floor(n / tileDims) * tileDims;
	//}

	////modifies value to snapped index in tile grid
	//void indexSnapValue(float& n) {
	//	n = floor(n / tileDims);
	//}

	////grid aligns an input rectangle
	//void gridSnapRec(Rectangle& rec) {
	//	gridSnapValue(rec.x);
	//	gridSnapValue(rec.y);
	//}


	//float get_gridSnapValue(float n) {
	//	return floor(n / tileDims) * tileDims;
	//}

	//float get_indexSnapValue(float n) {
	//	return floor(n / tileDims);
	//}

	//Rectangle get_gridSnapRec(Rectangle r) {
	//	return { get_gridSnapValue(r.x), get_gridSnapValue(r.y), r.width, r.height };
	//}


	//bool checkCollisionTileRec(Rectangle& r) {

	//}

	/*void snapRecToGrid(Rectangle& r) {
		r.x = floor(r.x / (float)tileDims) * (float)tileDims;
		r.y = floor(r.y / (float)tileDims) * (float)tileDims;
	}

	Rectangle getSnapRec(Rectangle r) {
		Rectangle copy;
		copy.x = r.x;
		copy.y = r.y;
		copy.width = r.width;
		copy.height = r.height;
		copy.x = floor(copy.x / (float)tileDims) * (float)tileDims;
		copy.y = floor(copy.y / (float)tileDims) * (float)tileDims;
		return copy;
	}*/

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

	/*void place(int x, int y, int width, int height, bool solid) {
		if (isRegionOccupied(x, y, width, height)) return;

		tiles.at(x, y).isRoot = true;
		tiles.at(x, y).blockData->tileWidth = width;
		tiles.at(x, y).blockData->tileHeight = height;

		for (int Y = y; Y < y + height; Y++) {
			for (int X = x; X < x + width; X++) {
				tiles.set_occupy(X, Y, true);
				tiles.set_solid(X, Y, solid);
				tiles.at(X, Y).sourceX = x;
				tiles.at(X, Y).sourceY = y;
			}
		}
	}*/

	void place(int x, int y, Block& block) {
		BlockAttributes attr = block.get_attr();
		if (isRegionOccupied(x, y, attr.tileWidth, attr.tileHeight)) return;
		
		for (int Y = y; Y < y + attr.tileHeight; Y++) {
			for (int X = x; X < x + attr.tileWidth; X++) {
				tiles.at(X, Y).occupant = &block;
				tiles.at(X, Y).occupant->set_tileX(x);
				tiles.at(X, Y).occupant->set_tileY(y);

				//tiles.set_occupy(X, Y, true);
				//tiles.set_solid(X, Y, block.solid);

				//tiles.at(X, Y).occupant->Tx = x;
				//tiles.at(X, Y).sourceY = y;
			}
		}
	}

	void destroy(int x, int y) {
		if (!tiles.isOccupied(x, y)) return;

		Block& block = *(tiles.at(x, y).occupant);

		for (int Y = block.tileY; Y < block.tileY + block.attr.tileHeight; Y++) {
			for (int X = block.tileX; X < block.tileX + block.attr.tileWidth; X++) {
				tiles.at(X, Y).occupant = nullptr;
			}
		}

		//Tile& clicked = tiles.at(x, y);
		
		
		/*Tile& root = tiles.at(clicked.sourceX, clicked.sourceY);
		
		int startX = root.sourceX;
		int startY = root.sourceY;
		int endY = startY + root.blockData->tileHeight;
		int endX = startX + root.blockData->tileWidth;

		for (int Y = startY; Y < endY; Y++) {
			for (int X = startX; X < endX; X++) {
				tiles.set_occupy(X, Y, false);
				tiles.set_solid(X, Y, false);
				tiles.at(X, Y).sourceX = -1;
				tiles.at(X, Y).sourceY = -1;
			}
		}*/
	}

private:
	bool isRegionOccupied(int x, int y, int width = 1, int height = 1) {
		for (int Y = y; Y < y + height; Y++) {
			for (int X = x; X < x + width; X++) {
				if (tiles.isOccupied(X, Y)) return true;
				//if (tiles.at(X, Y).occupied == true) return true;
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
		/*char u = '0', l = '0', d = '0', r = '0';
		std::cin >> u >> l >> d >> r;*/

		//double iT = GetTime();
		/*int x = (IsKeyDown(KeyboardKey::KEY_D)) - (IsKeyDown(KeyboardKey::KEY_A));
		int y = (IsKeyDown(KeyboardKey::KEY_S)) - (IsKeyDown(KeyboardKey::KEY_W));*/

		/*if (x != 0) {
			if (!colliding_HORZ(x)) {
				hitbox.x += 5 * x;
			}
		}*/

		/*std::cout << "colliding with:  x: " << colliding_HORZ(x) << ", y: " << colliding_VERT(y) << "\n";

		if (!colliding_HORZ(x)) {
			hitbox.x += 5 * x;
		}

		if (!colliding_VERT(y)) {
			hitbox.y += 5 * y;
		}*/

		/*if (y != 0) {
			if (!colliding_VERT(y)) {
				hitbox.y += 5 * y;
			}
		}*/

		
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
		//double dT = GetTime() - iT;
		//std::cout << "Player collision time (ms): " << dT * 1000 << "\n";
	}

	void checkCollision(float& var, float oSpeed) {
		//double iT = GetTime();
		//int el = 0;
		//int elCh = 0;
		for (auto& row : map->data()) {
			for (auto& r : row) {
				//el++;
				if (!r.occupant->attr.solid) continue;
				//elCh++;
				if (CheckCollisionRecs(hitbox, r.hitbox)) {
					var -= oSpeed;
					return;
				}
			}
		}
		//double dT = GetTime() - iT;
		//std::cout << "Collision check time (ms): " << dT * 1000 << "\n";
		//std::cout << elCh << " / " << el << " elements checked.\n";
	}

	void draw() {
		DrawRectangleRec(hitbox, RED);
	}

private:
	


	/*std::vector<int> CHECKED = { 0, 1 };
	std::vector<int> DIR_POS = { 1 };
	std::vector<int> DIR_NEG = { -1 };*/

	//TODO: THIS IS A GOOD STRUCTURE. KEEP THIS
	/*bool colliding(const std::initializer_list<int>& xSet, const std::initializer_list<int>& ySet) {
		double iT = GetTime();
		int el = 0;
		
		Rectangle snappedHitbox = map->getSnapRec(hitbox);

		for (int y : ySet) {
			for (int x : xSet) {
				if (x + snappedHitbox.x < 0 || y + snappedHitbox.y < 0) continue;
				el++;
				if (CheckCollisionRecs(snappedHitbox, map->at(x + snappedHitbox.x / map->get_tileDims(), y + snappedHitbox.y / map->get_tileDims()).hitbox)) return true;
			}
		}

		double dT = GetTime() - iT;
		std::cout << "Collision check time (ms): " << dT * 1000 << "\n";
		std::cout << el << " elements checked.\n";
	}

	bool colliding_VERT(int DIR) {
		return colliding({0, 1}, { DIR });
	}

	bool colliding_HORZ(int DIR) {
		return colliding({ DIR }, { 0, 1 });
	}*/
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
	
	std::vector<Block> blockTypes;
	blockTypes.push_back({ RAYWHITE, 0, 0, false }); //0: Air
	blockTypes.push_back({ BLACK, 1, 1, true });     //1: Wall   
	blockTypes.push_back({ WHITE, 1, 1, false });    //2: Floor

	while (!WindowShouldClose()) {
		//game logic
		player.move();

		if (IsKeyPressed(KeyboardKey::KEY_P)){
			/*int x, y, width, height, solid;
			std::cin >> x >> y >> width >> height >> solid;

			blocks.place(x, y, width, height, (bool)solid);*/

			int x, y, n;
			std::cin >> x >> y >> n;
			blocks.place(x, y, blockTypes.at(n));
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
				if (r.occupant == nullptr) continue;
				//if (r.occupied == false) continue;
				
				//if (r.solid == true) {
				if (r.occupant->attr.solid){
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