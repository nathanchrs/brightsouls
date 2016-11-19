#ifndef LOCATION_H
#define LOCATION_H

#include "area.h"
#include "point.h"
#include "array.h"
#include "boolean.h"

typedef struct {
	Point point;
	int areaId;
} Location;

typedef struct {
	Location from;
	Location to;
} LocationEdge;

typedef ARRAY(Area) AreaArray;
typedef ARRAY(LocationEdge) LocationEdgeArray;

Location Location_make(Point point, int areaId);

bool Location_isEqual(Location a, Location b);

bool Location_isValid(Location loc, const AreaArray *areas);

Location Location_moveUp(Location currentLocation, const AreaArray *areas, const LocationEdgeArray *locationEdges);

Location Location_moveDown(Location currentLocation, const AreaArray *areas, const LocationEdgeArray *locationEdges);

Location Location_moveLeft(Location currentLocation, const AreaArray *areas, const LocationEdgeArray *locationEdges);

Location Location_moveRight(Location currentLocation, const AreaArray *areas, const LocationEdgeArray *locationEdges);

#endif
