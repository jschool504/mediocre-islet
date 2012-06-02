//
//  ATPoint.h
//  TerrainProject
//
//  Created by Jeremy School on 5/4/12.
//  Copyright (c) 2012 Home. All rights reserved.
//


#define ATOriginPoint at_create_point(0, 0)

#ifndef TerrainProject_ATPoint_h
#define TerrainProject_ATPoint_h

// This is a 2D point. Used in 2D shapes
typedef struct ATPoint {
	
	float x;
	float y;
	
} ATPoint;

#endif

// Remember, when you initialize an array of these, you need to use this:
// ATPoint *points = malloc(sizeof(ATPoint) * numOfPoints);

// Creating
ATPoint at_create_point(float x, float y);

// Drawing
void at_draw_point(ATPoint point, int drawMode);

// Debugging
char * at_string_point(ATPoint point);
void at_print_point(ATPoint point);