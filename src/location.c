#include "location.h"
#include "utilities.h"

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
		if (loc.point.r >= 0 && loc.point.r < areas->items[loc.areaId].height && loc.point.c >= 0 && loc.point.c < areas->items[loc.areaId].width) {
			return Area_getCell(&(areas->items[loc.areaId]), loc.point) == AREA_EMPTY_CELL;
		}
	}
	return false;
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
	n = IO_readInteger(fin);
	Array_allocate(locs, n);
	locs->length = n;
	for (i = 0; i < n; i++) {
		locs->items[i].from.point.r = IO_readInteger(fin);
		locs->items[i].from.point.c = IO_readInteger(fin);
		locs->items[i].from.areaId = IO_readInteger(fin);
		locs->items[i].to.point.r = IO_readInteger(fin);
		locs->items[i].to.point.c = IO_readInteger(fin);
		locs->items[i].to.areaId = IO_readInteger(fin);
	}
}

void LocationEdgeArray_permute(LocationEdgeArray *locs) {
	Location swap;
	int i;
	int swapi;
	for (i = 0; i < locs->length; i++) {
		swapi = getRandomInt(0, locs->length - 1);
		if (locs->items[i].to.areaId != locs->items[swapi].to.areaId) {
			swap = locs->items[swapi].to;
			locs->items[swapi].to = locs->items[i].to;
			locs->items[i].to = swap;
		}
	}
}

void LocationEdgeArray_save(const LocationEdgeArray *locs, FILE *fout) {
	IO_writeInteger(fout, locs->length);
	IO_writeNewline(fout);
	int i;
	for (i = 0; i < locs->length; i++) {
		IO_writeInteger(fout, locs->items[i].from.point.r);
		IO_writeInteger(fout, locs->items[i].from.point.c);
		IO_writeInteger(fout, locs->items[i].from.areaId);
		IO_writeInteger(fout, locs->items[i].to.point.r);
		IO_writeInteger(fout, locs->items[i].to.point.c);
		IO_writeInteger(fout, locs->items[i].to.areaId);
		IO_writeNewline(fout);
	}
}

void LocationEdgeArray_deallocate(LocationEdgeArray *locs) {
	Array_deallocate(locs);
}
