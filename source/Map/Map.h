#define MAX_CARS 10
#define MAX_TILE_WIDTH 1000
#define MAX_TILE_HEIGHT 1000

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

class Tile
{
public:
	Point p;
};

struct CarInfo
{
	Point p;
	float LastRecordedSpeed;
	float LastRecordedAngle;
};


class Map
{
public:
	Map(int MapNumber, int NumCars);
	Map(int MapNumber, int NumCars, int scalar);
	~Map();

	void UpdateLocation(int CarNum, float Distance, float DegOffNorth, TileInfo *ti);
	Point* GetLocation(int CarNum);
	float GetDistanceBetweenCars(int car1, int car2);

	bool IsCarFacingAnother(int CarNum, float DegOffNorth);
private:
	int scalar;
	int numcars;
	CarInfo cars[MAX_CARS];
	TileInfo tiles[MAX_TILE_WIDTH][MAX_TILE_HEIGHT];
};

//Helper functions
bool OnSegment(Point p, Point q, Point r);
int Orientation(Point p, Point q, Point r);
bool DoIntersect(Point p1, Point p2, Point q1, Point q2);
Point FindNewPosition(Point p1, float distance, float deg);
float DegreesToRadians(float deg);