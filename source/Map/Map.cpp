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

void Map::UpdateLocation(int CarNum, float Distance, float DegOffNorth, TileInfo *ti)
{

}

Point* Map::GetLocation(int CarNum)
{
	Point *p = new Point();

	*p = cars[CarNum].p;

	return p;
}

float Map::GetDistanceBetweenCars(int CarNum1, int CarNum2)
{
	CarInfo car1 = cars[CarNum1];
	CarInfo car2 = cars[CarNum2];
	return std::sqrt(std::pow(car2.p.x - car1.p.x, 2) + std::pow(car2.p.y - car1.p.y, 2));;
}

bool Map::IsCarFacingAnother(int CarNum, float DegOffNorth)
{

	return false;
}

int main(void)
{
	return 0;
}