//
//  ATVector.h
//  TerrainProject
//
//  Created by Jeremy School on 5/10/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

// A few helpful default vectors

#define ATOriginVector at_create_vector(0, 0, 0)

#define ATVectorX at_create_vector(1, 0, 0)
#define ATVectorY at_create_vector(0, 1, 0)
#define ATVectorZ at_create_vector(0, 0, 1)

#ifndef TerrainProject_ATVector_h
#define TerrainProject_ATVector_h

typedef struct {
	
	float x;
	float y;
	float z;
	
} ATVector;

#endif

ATVector at_create_vector(float x, float y, float z);
void at_draw_vector(ATVector vector, int drawMode);

// Debugging
char * at_string_vector(ATVector vector);
void at_print_vector(ATVector vector);