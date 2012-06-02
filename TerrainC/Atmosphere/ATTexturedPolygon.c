//
//  ATTexturedPolygon.c
//  TerrainProject
//
//  Created by Jeremy School on 5/5/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include "ATTexturedPolygon.h"

ATTexturedPolygon at_create_textured_polygon(ATPoint origin, int numberOfVerts, ATPoint *points, ATTexture texture, ATPoint *texture_points) {
	ATTexturedPolygon polygon = {origin, numberOfVerts, points, texture, texture_points};
	return polygon;
}

void at_draw_textured_polygon_mode(ATTexturedPolygon polygon, int drawMode) {
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, polygon.texture.id);
	
	if (polygon.texture.alpha == true) {
		
		glDisable(GL_DEPTH_TEST);
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	
	glBegin(GL_POINT);
	
	glColor3f(1, 1, 1);
	
	glEnd();
	
	glBegin(drawMode);
	
	for (int i = 0; i < polygon.num_vertices; i++) {
		
		glTexCoord2f(polygon.texture_points[i].x, polygon.texture_points[i].y);
		glVertex2f(polygon.points[i].x, polygon.points[i].y);
		
	}
	
	glEnd();
	
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
	glDisable(GL_TEXTURE_2D);
	
}

void at_print_textured_polygon(ATTexturedPolygon polygon, bool printPoints) {
	printf("Origin: (X: %f Y: %f)", polygon.origin.x, polygon.origin.y);
	
	if (printPoints == true) {
		printf(" Vertices: (\n\n");
		
		for (int i = 0; i < polygon.num_vertices; i++) {
			printf("X: %f Y: %f\n", polygon.points[i].x, polygon.points[i].y);
		}
		
		printf("\n)\n");
	} else {
		printf("\n");
	}
	
}