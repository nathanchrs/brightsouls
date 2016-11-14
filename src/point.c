#include "point.h"

Point Point_make(int r, int c) {
	Point p;
	p.r = r;
	p.c = c;
	return p;
}

Point Point_translate(Point point, int dr, int dc) {
	point.r += dr;
	point.c += dc;
	return point;
}