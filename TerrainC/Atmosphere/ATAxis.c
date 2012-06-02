#include "ATAxis.h"

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

ATAxis at_create_axis(ATVector direction, float length, ATColor color) {
	ATAxis axis = {direction, length, color};
	
	axis._start_vertex = at_create_vertex(-(axis.direction.x * (length * 0.5)),
										  -(axis.direction.y * (length * 0.5)),
										  -(axis.direction.z * (length * 0.5)));
	
	axis._end_vertex = at_create_vertex((axis.direction.x * (length * 0.5)),
										(axis.direction.y * (length * 0.5)),
										(axis.direction.z * (length * 0.5)));
	
	return axis;
}

void at_draw_axis(ATAxis axis) {
	
	glBegin(GL_LINES);
	
	at_set_color(axis.color);
	
	at_draw_vertex(axis._start_vertex);
	at_draw_vertex(axis._end_vertex);
	
	glEnd();
	
}