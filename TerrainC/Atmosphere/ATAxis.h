#include "ATVector.h"
#include "ATVertex.h"
#include "ATColor.h"

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

#ifndef TerrainC_ATAxis_h
#define TerrainC_ATAxis_h

typedef struct {
	
	ATVector direction;
	float length;
	ATColor color;
	
	//Private
	ATVertex _start_vertex;
	ATVertex _end_vertex;
	
} ATAxis;

#endif

ATAxis at_create_axis(ATVector direction, float length, ATColor color);

void at_draw_axis(ATAxis axis);