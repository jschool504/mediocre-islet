//
//  ATVector.c
//  TerrainProject
//
//  Created by Jeremy School on 5/10/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include <GLUT/glut.h>

#include "ATVector.h"

ATVector at_create_vector(float x, float y, float z) {
	ATVector vector = {x, y, z};
	return vector;
}

void at_draw_vector(ATVector vector, int drawMode) {
	
	glBegin(drawMode);
	
	glVertex3f(0, 0, 0);
	glVertex3f(vector.x, vector.y, vector.z);
	
	glEnd();
}

char * at_string_vector(ATVector vector) {
	char *output = malloc(sizeof(char) * 100);
	sprintf(output, "Vector: (X: %f Y: %f Z: %f)\n", vector.x, vector.y, vector.z);
	return output;
}

void at_print_vector(ATVector vector) {
	printf("%s\n", at_string_vector(vector));
}
