#define MAX_CARS 10
#define MAX_TILE_WIDTH 1000
#define MAX_TILE_HEIGHT 1000
#define MAX_POTENTIAL_TILES 100

struct Point
{
	float x;
	float y;
};

class TileInfo
{
public:
	void* tile;
	type_info* ti; // pointer, not reference so it can be copied
};

/*class Tile
{
public:
	Point p;
};*/

struct CarInfo
{
	Point p;
	float LastRecordedSpeed;
	float LastRecordedAngle;
};

class Tile {

	// Tile is a class to hold tile data info 
	// Map is comprised of a 1000x1000 of tiles 
	// Each tile will equate to 0.25"
	// Max map size is therefore a ~20.8' per side

private:
	char type;
	char defaultType;

public:
	Tile() {};
	Tile(char defaultType) { this->defaultType = defaultType; };
	~Tile() {};

	char GetType(){	return type; };
	void SetType(int newType){ type = newType; };
	void SetDefaultType(int newDefaultType){ defaultType = newDefaultType; };
	void ResetToDefault(){ type = defaultType; };

};


class Map
{
public:
	Map(int MapNumber, int NumCars);
	Map(int MapNumber, int NumCars, int scalar);
	~Map();

	Point UpdateLocation(Point p, float Distance, float DegOffNorth);
	float Map::GetDistanceBetweenCars(Point car1, Point car2);

	Tile* HitTiles(Point start, Point end);

	void LoadMap(int mapNumber, Map map);
	void LoadMap(int mapNumber);
	void SaveMap(int mapNumber);
private:
	int scalar;
	Tile tiles[MAX_TILE_WIDTH][MAX_TILE_HEIGHT];
};

//Helper functions
bool OnSegment(Point p, Point q, Point r);
int Orientation(Point p, Point q, Point r);
bool DoIntersect(Point p1, Point p2, Point q1, Point q2);
Point FindNewPosition(Point p1, float distance, float deg);
float DegreesToRadians(float deg);
