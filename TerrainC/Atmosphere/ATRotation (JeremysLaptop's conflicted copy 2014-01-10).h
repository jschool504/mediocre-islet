//
//  ATPolygon.h
//  TerrainProject
//
//  Created by Jeremy School on 9/20/13.
//  Copyright (c) 2013 Home. All rights reserved.
//

#ifndef TerrainProject_ATRotation_h
#define  TerrainProject_ATRotation_h

typedef struct {
	
	float x;
	float y;
	float z;
	
} ATRotation;

#endif

ATRotation at_create_rotation(float x, float y, float z);
char * at_string_rotation(ATRotation rotation);
void at_print_rotation(ATRotation rotation);
