//
//  ATTexturedPolygon.h
//  TerrainProject
//
//  Created by Jeremy School on 5/4/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

#include "ATPoint.h"
#include "ATTexture.h"

#ifndef TerrainProject_ATTexturedPolygon_h
#define TerrainProject_ATTexturedPolygon_h

typedef struct ATTexturedPolygon {
	
	ATPoint origin;
	int num_vertices; // Number of verts in the array
	
	ATPoint *points; // Array of vertices. Be careful of the order in which you put them in, because that's the order they'll be drawn in
	
	ATTexture texture;
	ATPoint *texture_points;
	
} ATTexturedPolygon;

#endif

ATTexturedPolygon at_create_textured_polygon(ATPoint origin, int numberOfVerts, ATPoint *points, ATTexture texture, ATPoint *texture_points);
void at_draw_textured_polygon_mode(ATTexturedPolygon polygon, int drawMode);
void at_print_textured_polygon(ATTexturedPolygon polygon, bool printPoints);
