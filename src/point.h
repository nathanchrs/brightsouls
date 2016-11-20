#ifndef POINT_H
#define POINT_H

typedef struct {
	int r;
	int c;
} Point;

Point Point_make(int r, int c);

Point Point_translate(Point point, int dr, int dc);

#endif