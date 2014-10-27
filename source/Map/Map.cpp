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

float Map::GetDistanceBetweenCars(Point car1, Point car2)
{
	return std::sqrt(std::pow(car2.x - car1.x, 2) + std::pow(car2.y - car1.y, 2));;
}

Tile* Map::HitTiles(Point start, Point end)
{
	Tile HitTiles[MAX_POTENTIAL_TILES];

	int XDirection = (start.x < end.x ? 1 : -1);
	int YDirection = (start.y < end.y ? 1 : -1);

	int leftX = (XDirection > 0 ? start.x : end.x);
	int bottomY = (YDirection > 0 ? start.y : end.y);

	int rightX = (XDirection > 0 ? end.x : start.x);
	int topY = (YDirection > 0 ? end.y : start.y);

	int tiles = 0;

	for (int x = leftX; x <= rightX; x++)
	{
		for (int y = bottomY; y <= topY; y++)
		{
			Point p = { x, y };
			bool collinear = OnSegment(start, end, p);

			if (collinear)
			{
				HitTiles[tiles++] = this->tiles[x][y];
			}
		}
	}

	return HitTiles;
}

int main(void)
{
	return 0;
}