//
//  ATRotation.h
//  TerrainProject
//
//  Created by Jeremy School on 5/10/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#define ATZeroRotation at_create_rotation(0, 0, 0)

#ifndef TerrainProject_ATRotation_h
#define TerrainProject_ATRotation_h

typedef struct {
	
	float x;
	float y;
	float z;
	
} ATRotation;

#endif

ATRotation at_create_rotation(float x, float y, float z);
char * at_string_rotation(ATRotation rotation);
void at_print_rotation(ATRotation rotation);