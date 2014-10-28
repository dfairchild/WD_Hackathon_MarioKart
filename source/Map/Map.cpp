#include "Map.h"
#include <cmath>

Map::Map(int MapNumber, int NumCars)
{
	Map(MapNumber, NumCars, 1);
}

Map::Map(int MapNumber, int NumCars, int scalar)
{
	this->scalar = scalar;
}

Map::~Map()
{

}

Point UpdateLocation(Point p, float Distance, float DegOffNorth)
{
	return FindNewPosition(p, Distance, DegOffNorth);
}

double Map::GetDistanceBetweenCars(Point car1, Point car2)
{
	return std::sqrt(std::pow(car2.x - car1.x, 2) + std::pow(car2.y - car1.y, 2));;
}

// Get the tiles hit using the Bresenham line algorithm
Tile* Map::HitTiles(Point start, Point end)
{
	Tile* HitTiles = new Tile[MAX_POTENTIAL_TILES];

	int tile = 0;
	int deltax = end.x - start.x;
	int deltay = end.y - start.y;

	double error = 0.0;
	double deltaerr = abs(deltay / deltax); // Doesn't work on vertical lines.  Need to add handling for that

	int y = start.y;

	for (int x = start.x; x <= end.x; x++)
	{
		if (this->tiles[x][y] != HitTiles[tile])
			HitTiles[tile++] = this->tiles[x][y];

		error += deltaerr;
		if (error >= 0.5)
		{
			y++;
			error -= 1.0;
		}
	}

	return HitTiles;
}
