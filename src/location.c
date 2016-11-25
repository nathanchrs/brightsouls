#include "location.h"

Location Location_make(Point point, int areaId) {
	Location loc;
	loc.point = point;
	loc.areaId = areaId;
	return loc;
}

bool Location_isEqual(Location a, Location b) {
	return a.point.r == b.point.r && a.point.c == b.point.c && a.areaId == b.areaId;
}

bool Location_isValid(Location loc, const AreaArray *areas) {
	if (loc.areaId >= 0 && loc.areaId < areas->length) {
		return loc.point.r >= 0 && loc.point.r < areas->items[loc.areaId].height && loc.point.c >= 0 && loc.point.c < areas->items[loc.areaId].width;
	} else {
		return false;
	}
}

int Location_findMatchingEdge(Location loc, const LocationEdgeArray *locationEdges) {
	bool found = false;
	int i = 0;
	while (i < locationEdges->length && !found) {
		if (Location_isEqual(locationEdges->items[i].from, loc)) {
			found = true;
		} else {
			i++;
		}
	}
	return found ? i : -1;
}

Location Location_moveUp(Location currentLocation, const AreaArray *areas, const LocationEdgeArray *locationEdges) {
	Location loc = currentLocation;
	loc.point.r--;

	/* Check if the new location is the starting point of an edge, if an edge is found and is valid the go there */
	int edgeId = Location_findMatchingEdge(loc, locationEdges);
	if (edgeId != -1 && Location_isValid(locationEdges->items[edgeId].to, areas)) {
		return locationEdges->items[edgeId].to;
	}

	/* If the current location is not an edge's starting point and is not valid, cancel move */
	if (!Location_isValid(loc, areas)) return currentLocation;
	else return loc;
}

Location Location_moveDown(Location currentLocation, const AreaArray *areas, const LocationEdgeArray *locationEdges) {
	Location loc = currentLocation;
	loc.point.r++;

	/* Check if the new location is the starting point of an edge, if an edge is found and is valid the go there */
	int edgeId = Location_findMatchingEdge(loc, locationEdges);
	if (edgeId != -1 && Location_isValid(locationEdges->items[edgeId].to, areas)) {
		return locationEdges->items[edgeId].to;
	}

	/* If the current location is not an edge's starting point and is not valid, cancel move */
	if (!Location_isValid(loc, areas)) return currentLocation;
	else return loc;
}

Location Location_moveLeft(Location currentLocation, const AreaArray *areas, const LocationEdgeArray *locationEdges) {
	Location loc = currentLocation;
	loc.point.c--;

	/* Check if the new location is the starting point of an edge, if an edge is found and is valid the go there */
	int edgeId = Location_findMatchingEdge(loc, locationEdges);
	if (edgeId != -1 && Location_isValid(locationEdges->items[edgeId].to, areas)) {
		return locationEdges->items[edgeId].to;
	}

	/* If the current location is not an edge's starting point and is not valid, cancel move */
	if (!Location_isValid(loc, areas)) return currentLocation;
	else return loc;
}

Location Location_moveRight(Location currentLocation, const AreaArray *areas, const LocationEdgeArray *locationEdges) {
	Location loc = currentLocation;
	loc.point.c++;

	/* Check if the new location is the starting point of an edge, if an edge is found and is valid the go there */
	int edgeId = Location_findMatchingEdge(loc, locationEdges);
	if (edgeId != -1 && Location_isValid(locationEdges->items[edgeId].to, areas)) {
		return locationEdges->items[edgeId].to;
	}

	/* If the current location is not an edge's starting point and is not valid, cancel move */
	if (!Location_isValid(loc, areas)) return currentLocation;
	else return loc;
}

void LocationEdgeArray_load(LocationEdgeArray *locs, FILE *fin) {
	int n, i;
	fscanf(fin, "%d", &n);
	Array_allocate(locs, n);
	locs->length = n;
	int r1, c1, aid1, r2, c2, aid2;
	for (i = 0; i < n; i++) {
		fscanf(fin, "%d%d%d%d%d%d", &r1, &c1, &aid1, &r2, &c2, &aid2);
		locs->items[i].from.point.r = r1;
		locs->items[i].from.point.c = c1;
		locs->items[i].from.areaId = aid1;
		locs->items[i].to.point.r = r1;
		locs->items[i].to.point.c = c1;
		locs->items[i].to.areaId = aid1;
	}
}

void LocationEdgeArray_deallocate(LocationEdgeArray *locs) {
	Array_deallocate(locs);
}
