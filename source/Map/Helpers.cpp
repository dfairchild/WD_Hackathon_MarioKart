#include <algorithm>
#include "Map.h"

#define PI 3.14159265

// Given 3 points p, q, r, check if all 3 are collinear
bool OnSegment(Point p, Point q, Point r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;

	return false;
}

// To find orientation of the points (p, q, r).
// Returns 3 possible values
// 0 = points are collinear
// 1 = Clockwise orientation
// 2 = Counterclockwise orientation
int Orientation(Point p, Point q, Point r)
{
	// Slides with derivation
	// http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf

	double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0.0) return 0;

	return (val > 0) ? 1 : 2; // clockwise or counter-clockwise
}

// Determine if line segments p1q1 and p2q2 intersect
bool DoIntersect(Point p1, Point p2, Point q1, Point q2)
{
	//Find the 4 orientations needed

	int o1 = Orientation(p1, q1, p2);
	int o2 = Orientation(p1, q1, q2);
	int o3 = Orientation(p2, q2, p1);
	int o4 = Orientation(p2, q2, q1);

	if (o1 != o2 && o3 != o4)
		return true;

	//Special cases
	// p1, q1, and p2 are collinear and p2 lies on p1q1
	if (o1 == 0 && OnSegment(p1, p2, q1)) return true;

	// p1, q1, and p2 are collinear and q2 lies on p1q1
	if (o2 == 0 && OnSegment(p1, q2, q1)) return true;

	// p2, q2, and p1 are collinear and p1 lies on p2q2
	if (o3 == 0 && OnSegment(p2, p1, q2)) return true;

	// p2, q2, and q1 are collinear and q1 lies on p2q2
	if (o4 == 0 && OnSegment(p2, q1, q2)) return true;

	return false;
}

Point FindNewPosition(Point p, float distance, float deg)
{
	Point p2;

	deg = int(deg + 360) % 360;

	//if ((deg >= 90) && (deg < 270))
	//	p2.x = p.x - (distance * cos(DegreesToRadians(deg)));
	//else
		p2.x = p.x + (distance * cos(DegreesToRadians(deg)));

	//if ((deg >= 0) && (deg < 180))
		p2.y = p.y - (distance * sin(DegreesToRadians(deg)));
	//else
	//	p2.y = p.y + (distance * sin(DegreesToRadians(deg)));

	return p2;
}

double DegreesToRadians(float deg)
{
	return (deg * PI / 180);
}

float ConvertFromNorth(float deg)
{
	deg = int(deg + 360) % 360;

	if (deg < 90 && deg >= 0)
		return 90 - deg;
	if (deg < 180 && deg >= 90)
		return 270 + (180 - deg);
	if (deg < 270 && deg >= 180)
		return 180 + (270 - deg);
	if (deg < 360 && deg >= 270)
		return 90 + (360 - deg);
	else
		return -1;
}