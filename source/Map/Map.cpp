#include "Map.h"
#include <cmath>
#include <utility>
#include <iostream>


Map::Map(int MapNumber, int NumCars)
{
	Map(MapNumber, NumCars, 1);
}

Map::Map(int MapNumber, int NumCars, int scalar)
{
	this->scalar = scalar;

	//Create rows
	for (int i = 0; i < MAX_TILE_WIDTH; i++)
	{
		this->tiles.push_back(std::vector<Tile>());
	}

	//Create columns for each row
	for (int i = 0; i < MAX_TILE_WIDTH; i++)
		for (int j = 0; j < MAX_TILE_HEIGHT; j++)
		{
			this->tiles[i].push_back(Tile());
		}
}



Point Map::UpdateLocation(Point p, float Distance, float DegOffNorth)
{
	// Shift angle to North
	DegOffNorth += 90;

	Point p2 = { 1, 1 };
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
