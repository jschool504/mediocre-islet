//
//  Chunk.h
//  TerrainC
//
//  Created by Jeremy School on 5/26/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "Atmosphere.h"
#include "TerrainGenerator.h"
#include <stdbool.h>

#define MIN_LIGHT 0.8
#define MAX_LIGHT 0.2

#define GRASS_COLOR at_create_color(0, 0.75, 0, 1.0)
#define DIRT_COLOR at_create_color(0.3, 0.2, 0.1, 1.0)
#define ROCK_COLOR at_create_color(0.5, 0.5, 0.5, 1.0)
#define SNOW_COLOR at_create_color(1, 1, 1, 1.0)
#define WATER_COLOR at_create_color(0, 0, 0.8, 1.0)
#define ERROR_COLOR at_create_color(1.0, 0.0, 1.0, 1.0)

#ifndef TerrainC_Chunk_h
#define TerrainC_Chunk_h

typedef struct {
	
	ATPoint location;
	int chunk_size;
	int map_size;
	int seed;
	int lighting_softness;
	
	float max_slope_grass;
	float max_height_grass;
	
	float max_slope_dirt;
	float max_slope_rock;
	
	float max_slope_water;
	
	ATTexture texture;
	ATRect grass_texture_rect;
	ATRect dirt_texture_rect;
	ATRect rock_texture_rect;
	ATRect snow_texture_rect;
	ATRect error_texture_rect;
	
	// Private
	int _vertex_count;
	ATVertex *_vertices;
	int *_materials;
	float *_lighting;
	float *_texture_points;
	bool _data_calculated;
	TerrainGenerator *_generator;
	
} Chunk;

#endif

Chunk create_chunk(ATPoint location, int map_size, int chunk_size, int seed);

void draw_chunk(Chunk *chunk);
float get_height_at_point(Chunk chunk, int x, int y);

void print_chunk(Chunk chunk);
ATPoint center_chunk(Chunk chunk); // find the center of the chunk
