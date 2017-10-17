//
//  ATUtils.c
//  TerrainC
//
//  Created by Jeremy School on 5/28/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ATUtils.h"
#include "AtmosphereProjection.h"

#include <GLUT/glut.h>

ATVertex at_convert_point(ATPoint point) {
	
	return at_create_vertex(point.x, 0, point.y);
	
}

ATPoint at_convert_vertex(ATVertex vertex) {
	
	return at_create_point(vertex.x, vertex.z);
	
}

void at_start_screen_output(int num_of_chars) {
	screen_output = malloc(sizeof(num_of_chars));
}

void at_end_screen_output() {
	free(screen_output);
}

void at_print_screen(char *string) {
	strncat(screen_output, string, sizeof(char));
}

void at_draw_string(float x, float y, char *string) {
	
	atmosphere_ortho_start(0, 1, 0, 1, 0, 10);
	
	glColor3f(1, 1, 1);
	glRasterPos2f(x, y);
	
	int newlines = 1;
	for (char *c = string; *c != '\0'; c++) {
		if (*c == '\n') {
			glRasterPos2f(x, y -= LINE_HEIGHT);
			newlines++;
		}
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	
	atmosphere_ortho_end();
}

float at_duration(clock_t startTime) {
	
	clock_t endTime = clock();
	float dTime = difftime(endTime, startTime);
	
	return dTime / CLOCKS_PER_SEC;
	
}
