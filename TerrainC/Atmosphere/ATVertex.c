//
//  ATVertex.c
//  TerrainProject
//
//  Created by Jeremy School on 5/4/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include <GLUT/glut.h>

#include "ATVertex.h"

ATVertex at_create_vertex(float x, float y, float z) {
	ATVertex vertex = {x, y, z};
	return vertex;
}

void at_draw_vertex(ATVertex vertex) {
	
	glVertex3f(vertex.x, vertex.y, vertex.z);
	
}

void at_draw_colored_vertex(ATVertex vertex, ATColor color) {
	
	glColor3f(color.r, color.g, color.b);
	glVertex3f(vertex.x, vertex.y, vertex.z);
	
}

void at_draw_textured_vertex(ATVertex vertex, ATPoint texture_point) {
	
	glTexCoord2f(texture_point.x, texture_point.y);
	glVertex3f(vertex.x, vertex.y, vertex.z);
	
}

void at_draw_colored_textured_vertex(ATVertex vertex, ATColor color, ATPoint texture_point) {
	
	glColor3f(color.r, color.g, color.b);
	glTexCoord2f(texture_point.x, texture_point.y);
	glVertex3f(vertex.x, vertex.y, vertex.z);
	
}

void at_draw_vertex_mode(ATVertex vertex, int drawMode) {
	
	glBegin(drawMode);
	
	glVertex3f(vertex.x, vertex.y, vertex.z);
	
	glEnd();
	
}

void at_draw_colored_vertex_mode(ATVertex vertex, ATColor color, int drawMode) {
	
	glBegin(drawMode);
	
	glColor3f(color.r, color.g, color.b);
	glVertex3f(vertex.x, vertex.y, vertex.z);
	
	glEnd();
	
}

char * at_string_vertex(ATVertex vertex) {
	char *output = malloc(sizeof(char) * 100);
	sprintf(output, "Vertex: (X: %f Y: %f Z: %f)", vertex.x, vertex.y, vertex.z);
	return output;
}

void at_print_vertex(ATVertex vertex) {
	printf("%s\n", at_string_vertex(vertex));
}
