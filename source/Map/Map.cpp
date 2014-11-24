#include "Map.h"
#include <cmath>
#include <iostream>
#include <utility>

Map::Map(int MapNumber, int NumCars)
{
	this->scalar = 1;
	Map(MapNumber, NumCars, 1);
}

Map::Map(int MapNumber, int NumCars, int scalar)
{
	this->scalar = scalar;
	this->LeftMost = MAX_TILE_WIDTH;
	this->RightMost = 0;
	this->TopMost = MAX_TILE_HEIGHT;
	this->BottomMost = 0;

	//Create rows
	for (int i = 0; i < MAX_TILE_WIDTH; i++)
	{
		this->tiles.push_back(std::vector<Tile>());
	}

	//Create columns for each row
	for (int i = 0; i < MAX_TILE_WIDTH; i++)
		for (int j = 0; j < MAX_TILE_HEIGHT; j++)
		{
			this->tiles[i].push_back(Tile('D'));
		}
}



Point Map::UpdateLocation(Point p, float Distance, float DegOffNorth)
{
	// Shift angle to North
	//DegOffNorth = 90 - DegOffNorth;
	return FindNewPosition(p, Distance, DegOffNorth);
}

double Map::GetDistanceBetweenCars(Point car1, Point car2)
{
	return std::sqrt(std::pow(car2.x - car1.x, 2) + std::pow(car2.y - car1.y, 2));;
}

// Get the tiles hit using the Bresenham line algorithm
TileInfo* Map::HitTiles(Point start, Point end, int &numTiles)
{
	TileInfo* HitTiles = new TileInfo[MAX_POTENTIAL_TILES];
	numTiles = 0;

	bool steep = (fabs(end.y - start.y) > fabs(end.x - start.x));

	if (steep)
	{
		std::swap(start.x, start.y);
		std::swap(end.x, end.y);
	}

	if (start.x > end.x)
	{
		std::swap(start.x, end.x);
		std::swap(start.y, end.y);
	}

	double deltax = end.x - start.x;
	double deltay = fabs(end.y - start.y);

	double error = deltax / 2.0;
	int ystep = (start.y < end.y) ? 1 : -1;

	int y = start.y;

	for (int x = start.x; x <= end.x; x++)
	{
		if (steep)
		{
			if (this->tiles[y][x] != HitTiles[numTiles].tile)
			{
				TileInfo t = { this->tiles[y][x], { y, x } };
				HitTiles[numTiles++] = t;
			}
		}
		else
		{
			if (this->tiles[x][y] != HitTiles[numTiles].tile)
			{
				TileInfo t = { this->tiles[x][y], { x, y } };
				HitTiles[numTiles++] = t;
			}
		}

		error -= deltay;
		if (error < 0)
		{
			y += ystep;
			error += deltax;
		}
	}

	return HitTiles;
}

Point Map::DrawMap(Point p, float Distance, float DegOffNorth)
{
	//DegOffNorth = 90 - DegOffNorth;
	Point p2 = UpdateLocation(p, Distance, DegOffNorth);

	int numTiles = 0;
	TileInfo *TileLine = HitTiles(p, p2, numTiles);

	for (int i = 0; i < numTiles; i++)
	{
		int x = TileLine[i].p.x;
		int y = TileLine[i].p.y;
		tiles[x][y] = Tile('\'');
		Point* TempPoint = new Point{ TileLine[i].p.x, TileLine[i].p.y };
		DrawPathLine(*TempPoint, DegOffNorth);
		delete TempPoint;
	}

	tiles[p.x][p.y] = Tile('!');
	tiles[p2.x][p2.y] = Tile('!');

	if (LeftMost < SHIFT_IN_TILES)
	{
		if (ShiftMap(RIGHT))
			p2.x += SHIFT_IN_TILES;
	}
	if (RightMost > (MAX_TILE_WIDTH - SHIFT_IN_TILES))
	{
		if (ShiftMap(LEFT))
			p2.x -= SHIFT_IN_TILES;
	}
	if (TopMost < SHIFT_IN_TILES)
	{
		if (ShiftMap(DOWN))
			p2.y += SHIFT_IN_TILES;
	}
	if (BottomMost > (MAX_TILE_HEIGHT - SHIFT_IN_TILES))
	{
		if (ShiftMap(UP))
			p2.y -= SHIFT_IN_TILES;
	}

	ResetBoundaries();
	return p2;
}

void Map::DrawPathLine(Point p, float DegOffNorth)
{
	Point endpoint1 = UpdateLocation(p, TRACK_WIDTH_IN_TILES, DegOffNorth + 90);
	Point endpoint2 = UpdateLocation(p, TRACK_WIDTH_IN_TILES, DegOffNorth - 90);

	int numTiles1 = 0;
	TileInfo *line1 = HitTiles(p, endpoint1, numTiles1);

	int numTiles2 = 0;
	TileInfo *line2 = HitTiles(p, endpoint2, numTiles2);

	for (int i = 0; i < numTiles1; i++)
	{
		int x = line1[i].p.x;
		int y = line1[i].p.y;
		tiles[x][y] = Tile('.');
		tiles[x+1][y] = Tile('.');
		tiles[x-1][y] = Tile('.');
		tiles[x][y+1] = Tile('.');
		tiles[x][y-1] = Tile('.');

		if ((y + 1) > BottomMost)
			BottomMost = y + 1;

		if ((y - 1) < TopMost)
			TopMost = y - 1;

		if ((x + 1) > RightMost)
			RightMost = x + 1;

		if ((x - 1) < LeftMost)
			LeftMost = x - 1;
	}

	for (int i = 0; i < numTiles2; i++)
	{
		int x = line2[i].p.x;
		int y = line2[i].p.y;
		tiles[x][y] = Tile('.');
		tiles[x + 1][y] = Tile('.');
		tiles[x - 1][y] = Tile('.');
		tiles[x][y + 1] = Tile('.');
		tiles[x][y - 1] = Tile('.');

		if ((y + 1) > BottomMost)
			BottomMost = y + 1;

		if ((y - 1) < TopMost)
			TopMost = y - 1;

		if ((x + 1) > RightMost)
			RightMost = x + 1;

		if ((x - 1) < LeftMost)
			LeftMost = x - 1;
	}
}

bool Map::ShiftMap(ShiftDir direction)
{
	bool ShiftMade;
	int SpacesToMove;

	if (direction == RIGHT)
	{
		// Check that there's space
		for (int y = 0; y < MAX_TILE_HEIGHT; y++)
		{
			for (int x = MAX_TILE_WIDTH- 1; x >= (MAX_TILE_WIDTH - (2 * SHIFT_IN_TILES)); --x)
			{
				if (tiles[x][y].type == DIRT)
					continue;

				return false;
			}
		}

		for (int y = 0; y < MAX_TILE_HEIGHT; y++)
		{
			for (int x = (MAX_TILE_WIDTH - SHIFT_IN_TILES - 1); x >= 0; --x)
			{
				tiles[x + SHIFT_IN_TILES][y] = tiles[x][y];
			}

			// Fill the left gap
			for (int i = 0; i < SHIFT_IN_TILES; i++)
			{
				tiles[i][y] = Tile(DIRT);
			}
		}
	}
	else if (direction == LEFT)
	{
		// Check that there's space
		for (int y = 0; y < MAX_TILE_HEIGHT; y++)
		{
			for (int x = 0; x < 2 * SHIFT_IN_TILES; x++)
			{
				if (tiles[x][y].type == DIRT)
					continue;

				return false;
			}
		}

		for (int y = 0; y < MAX_TILE_HEIGHT; y++)
		{
			for (int x = SHIFT_IN_TILES; x < MAX_TILE_WIDTH; x++)
			{
				tiles[x - SHIFT_IN_TILES][y] = tiles[x][y];
			}

			// Fill the right gap
			for (int i = MAX_TILE_WIDTH - 1; i >= (MAX_TILE_WIDTH - SHIFT_IN_TILES); --i)
			{
				tiles[i][y] = Tile(DIRT);
			}
		}
	}
	else if (direction == DOWN)
	{
		// Check that there's space
		for (int x = 0; x < MAX_TILE_WIDTH; x++)
		{
			for (int y = MAX_TILE_WIDTH - 1; y >= (MAX_TILE_HEIGHT - (2 * SHIFT_IN_TILES)); --y)
			{
				if (tiles[x][y].type == DIRT)
					continue;

				return false;
			}
		}

		for (int x = 0; x < MAX_TILE_WIDTH; x++)
		{
			for (int y = (MAX_TILE_HEIGHT - SHIFT_IN_TILES - 1); y >= 0; --y)
			{
				tiles[x][y + SHIFT_IN_TILES] = tiles[x][y];
			}

			// Fill the left gap
			for (int i = 0; i < SHIFT_IN_TILES; i++)
			{
				tiles[x][i] = Tile(DIRT);
			}
		}
	}
	else if (direction == UP)
	{
		// Check that there's space
		for (int x = 0; x < MAX_TILE_WIDTH; x++)
		{
			for (int y = 0; y < 2 * SHIFT_IN_TILES; y++)
			{
				if (tiles[x][y].type == DIRT)
					continue;

				return false;
			}
		}

		for (int x = 0; x < MAX_TILE_WIDTH; x++)
		{
			for (int y = SHIFT_IN_TILES; y < MAX_TILE_HEIGHT; y++)
			{
				tiles[x][y - SHIFT_IN_TILES] = tiles[x][y];
			}

			// Fill the right gap
			for (int i = MAX_TILE_HEIGHT - 1; i >= (MAX_TILE_HEIGHT - SHIFT_IN_TILES); --i)
			{
				tiles[x][i] = Tile(DIRT);
			}
		}
	}

	return true;
}

void Map::ResetBoundaries()
{
	this->LeftMost = MAX_TILE_WIDTH;
	this->RightMost = 0;
	this->TopMost = MAX_TILE_HEIGHT;
	this->BottomMost = 0;
}

void Map::PrintMap()
{
	std::cout << "Printing map" << std::endl;
	for (int y = 0; y < MAX_TILE_HEIGHT; y++)
	{
		for (int x = 0; x < MAX_TILE_WIDTH; x++)
		{
			std::cout << tiles[x][y].type;
		}
		std::cout << std::endl;
	}
}
