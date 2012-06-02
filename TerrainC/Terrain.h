//
//  Terrain.h
//  TerrainC
//
//  Created by Jeremy School on 5/26/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "Atmosphere.h"
#include "Chunk.h"
#include <math.h>
#include <stdbool.h>

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

#ifndef TerrainC_Terrain_h
#define TerrainC_Terrain_h

typedef struct {
	
	ATPoint origin;
	unsigned int map_size; // Meters
	unsigned int chunk_size;
	unsigned int view_range;
	int seed;
	bool draw_wireframe;
	bool show_chunks;
	int lighting_softness;
	
	ATTexture terrain_texture;
	ATRect grass_texture_rect;
	ATRect dirt_texture_rect;
	ATRect rock_texture_rect;
	ATRect snow_texture_rect;
	ATRect error_texture_rect;
	
	// Private
	unsigned int number_of_chunks; // number of chunks
	unsigned int _chunks_per_side; // number of chunks on one side of the map
	bool _chunks_calculated;
	Chunk *_chunks; // Actual array of chunks
	
} Terrain;

#endif

Terrain create_terrain(ATPoint origin, unsigned int map_size, unsigned int chunk_size, unsigned int view_range, ATTexture texture, ATRect texture_rects[5], int seed);
void destroy_terrain(Terrain terrain);
void init_chunks(Terrain *terrain);
Chunk chunk_for_coord(Terrain terrain, int x, int y);
void draw_terrain(Terrain *terrain, ATPoint display_point);