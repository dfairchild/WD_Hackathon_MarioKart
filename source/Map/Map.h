#define MAX_CARS 10
#define MAX_TILE_WIDTH 500
#define MAX_TILE_HEIGHT 500
#define MAX_POTENTIAL_TILES 100
#define TRACK_WIDTH_IN_TILES 10
#define SHIFT_IN_TILES 10

#include <vector>
#include <string>

// Tile types and their character values
const char DIRT   = 'D';
const char ROAD   = '.';
const char BANANA = 'B';
const char WALL   = '|';
const char START1 = '1';
const char START2 = '2';

enum ShiftDir { UP, DOWN, LEFT, RIGHT };

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
	Tile(char defaultType) { this->defaultType = this->type = defaultType; };

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
	double GetDistanceBetweenCars(Point car1, Point car2);

	TileInfo* HitTiles(Point start, Point end, int &numTiles);

	void LoadMap(int mapNumber, Map map);
	void LoadMap(int mapNumber, int scale);
	void SaveMap(int mapNumber);

	Point DrawMap(Point p, float Distance, float DegOffNorth);
	void PrintMap();

	Tile GetTile(int x, int y);
	void SetTile(int x, int y, const Tile tile);

	std::string GetAppSizeMap();

	std::vector< std::vector<Tile> >  tiles;

private:
	bool ShiftMap(ShiftDir direction);
	void DrawPathLine(Point p, float DegOffNorth);
	void ResetBoundaries();
	int scalar;
	int LeftMost;
	int RightMost;
	int BottomMost;
	int TopMost;
	
};

//Helper functions
bool OnSegment(Point p, Point q, Point r);
int Orientation(Point p, Point q, Point r);
bool DoIntersect(Point p1, Point p2, Point q1, Point q2);
Point FindNewPosition(Point p1, float distance, float deg);
double DegreesToRadians(float deg);
float ConvertFromNorth(float deg);
