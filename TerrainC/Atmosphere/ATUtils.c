//
//  ATUtils.c
//  TerrainC
//
//  Created by Jeremy School on 5/28/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ATUtils.h"
#include "AtmosphereProjection.h"

#include <GLUT/glut.h>

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

ATVertex at_convert_point(ATPoint point) {
	
	return at_create_vertex(point.x, 0, point.y);
	
}

ATPoint at_convert_vertex(ATVertex vertex) {
	
	return at_create_point(vertex.x, vertex.z);
	
}

void at_draw_string(int x, int y, char *string) {
	
	atmosphere_ortho_start(0, 1, 0, 1, 0, 10);
	
	glColor3f(1, 1, 1);
	glRasterPos2f(x, y);
	
	for (char *c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	
	atmosphere_ortho_end();
	
}

float at_duration(clock_t startTime) {
	
	clock_t endTime = clock();
	float dTime = difftime(endTime, startTime);
	
	return dTime / CLOCKS_PER_SEC;
	
}