//
//  ATVertex.h
//  TerrainProject
//
//  Created by Jeremy School on 5/4/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "ATColor.h"
#include "ATPoint.h"

#define ATOriginVertex at_create_vertex(0, 0, 0)

#ifndef TerrainProject_ATVertex_h
#define TerrainProject_ATVertex_h

// This is the 3D equivalent of an ATPoint. Note the name difference.
typedef struct ATVertex {
	
	float x;
	float y;
	float z;
	
	float nx;
	float ny;
	float nz;
	
	float s;
	float t;
	
} ATVertex;

#endif

ATVertex at_create_vertex(float x, float y, float z);
ATVertex at_create_vertex_normals(float x, float y, float z, float nx, float ny);
ATVertex at_create_vertex_texpoints(float x, float y, float z, float s, float t);

void at_draw_vertex(ATVertex vertex);
void at_draw_colored_vertex(ATVertex vertex, ATColor color);
void at_draw_textured_vertex(ATVertex vertex, ATPoint texture_point);
void at_draw_colored_textured_vertex(ATVertex vertex, ATColor color, ATPoint texture_point);

void at_draw_vertex_mode(ATVertex vertex, int drawMode);
void at_draw_colored_vertex_mode(ATVertex vertex, ATColor color, int drawMode);

char * at_string_vertex(ATVertex vertex);
void at_print_vertex(ATVertex vertex);