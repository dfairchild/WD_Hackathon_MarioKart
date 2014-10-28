#define MAX_CARS 10
#define MAX_TILE_WIDTH 1000
#define MAX_TILE_HEIGHT 1000
#define MAX_POTENTIAL_TILES 100
#define TRACK_WIDTH_IN_TILES 10

#include<vector>

struct Point
{
	double x;
	double y;

	bool operator==(const Point p) const
	{
		return (x == p.x && y == p.y);
	}
};

class Tile {

	// Tile is a class to hold tile data info 
	// Map is comprised of a 1000x1000 of tiles 
	// Each tile will equate to 0.25"
	// Max map size is therefore a ~20.8' per side

public:
	char type;
	char defaultType;

	Tile() {};
	Tile(char defaultType) { this->defaultType = '#'; };

	void ResetToDefault(){ type = defaultType; };

	bool operator==(const Tile &other) { return (type == other.type); };
	bool operator!=(const Tile &other) { return !(*this == other); };

};

struct TileInfo
{
	Tile tile;
	Point p;

	bool operator==(const TileInfo t) const
	{
		return (p.x == t.p.x && p.y == t.p.y);
	}
};

class Map
{
public:
	Map(int MapNumber, int NumCars);
	Map(int MapNumber, int NumCars, int scalar);

	Point UpdateLocation(Point p, float Distance, float DegOffNorth);
	double Map::GetDistanceBetweenCars(Point car1, Point car2);

	TileInfo* HitTiles(Point start, Point end, int &numTiles);

	void LoadMap(int mapNumber, Map map);
	void LoadMap(int mapNumber);
	void SaveMap(int mapNumber);
private:
	int scalar;
	std::vector< std::vector<Tile> >  tiles;
};

//Helper functions
bool OnSegment(Point p, Point q, Point r);
int Orientation(Point p, Point q, Point r);
bool DoIntersect(Point p1, Point p2, Point q1, Point q2);
Point FindNewPosition(Point p1, float distance, float deg);
double DegreesToRadians(float deg);
