//
//  Chunk.c
//  TerrainC
//
//  Created by Jeremy School on 5/26/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Chunk.h"

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

int compare_elements(const void *a, const void *b);
int private_size(Chunk chunk);
void init_data(Chunk *chunk);

Chunk create_chunk(ATPoint location, int map_size, int chunk_size, int seed) {
	Chunk chunk;
	chunk.location = location;
	chunk.map_size = map_size;
	chunk.chunk_size = chunk_size;
	chunk.seed = seed;
	chunk.lighting_softness = 1;
	chunk._vertex_count = chunk_size * chunk_size;
	
	chunk._data_calculated = 0;
	//at_print_point(chunk.location);
	//chunk._generator = create_t_generator(chunk.seed, chunk.map_size);
	
	// Some default cutoffs
	chunk.max_slope_grass = 0.8;
	chunk.max_height_grass = 50;
	chunk.max_slope_dirt = 0.9;
	chunk.max_slope_water = 0.1;
	chunk.max_slope_rock = MAXFLOAT;
	
	return chunk;
}

float get_height_at_point(Chunk chunk, int x, int y) {
    return chunk._vertices[x + (y * chunk.chunk_size)].y;
}

int private_size(Chunk chunk) {
	return chunk.chunk_size + 1;
}

void init_data(Chunk *chunk) {
	
	chunk->_vertices = malloc(sizeof(ATVertex) * Square(private_size(*chunk)));
	chunk->_materials = malloc(sizeof(ATColor) * Square(private_size(*chunk)));
	chunk->_lighting = malloc(sizeof(float) * Square(private_size(*chunk)));
	chunk->_texture_points = malloc(sizeof(float) * Square(private_size(*chunk)));
	
	for (int x = 0; x < private_size(*chunk); x++) {
		for (int y = 0; y < private_size(*chunk); y++) {
			
			ATPoint point = at_create_point(chunk->location.x + x, chunk->location.y + y); //Pass into zonecontroller
			
			//printf("%d, %d\n", x, y);
			//at_print_point(chunk->location);
			
			ATVertex vertex = at_create_vertex(point.x, height_at_point(*chunk->_generator, point), point.y);
			chunk->_vertices[x + (y * private_size(*chunk))] = vertex;
			
			float localHeights[5] = {
				vertex.y,
				height_at_point(*chunk->_generator, at_create_point(vertex.x - 1, vertex.z)),
				height_at_point(*chunk->_generator, at_create_point(vertex.x, vertex.z - 1)),
				height_at_point(*chunk->_generator, at_create_point(vertex.x + 1, vertex.z)),
				height_at_point(*chunk->_generator, at_create_point(vertex.x, vertex.z + 1))
			};
			
			float lightSlope = 1 - (localHeights[1] - localHeights[0]);
			
			if (lightSlope < MIN_LIGHT) {
				lightSlope = MIN_LIGHT;
			}
			
			qsort(localHeights, 5, sizeof(float), compare_elements);
			
			chunk->_lighting[x + (y * private_size(*chunk))] = lightSlope; //Get light slope
			
			float slope = localHeights[4] - localHeights[0];
			
			Zone zone = zone_for_point(*chunk->_generator, point);
			
			if (slope == zone.slope_attributes[WATER_INDEX] && vertex.y <= zone.height_attributes[WATER_INDEX]) {
				
				chunk->_materials[x + (y * private_size(*chunk))] = MATERIAL_WATER; //Get material
			
			} else if (slope < zone.slope_attributes[GRASS_INDEX] && vertex.y <= zone.height_attributes[GRASS_INDEX]) {
				
				if ((zone.slope_attributes[GRASS_INDEX] + slope) / 2) {
					chunk->_materials[x + (y * private_size(*chunk))] = MATERIAL_GRASS;
				} else {
					chunk->_materials[x + (y * private_size(*chunk))] = MATERIAL_DIRT;
				}
				
			} else if (slope < zone.slope_attributes[DIRT_INDEX] && vertex.y <= zone.height_attributes[DIRT_INDEX]) {
				
				if ((zone.slope_attributes[DIRT_INDEX] + slope) / 2) {
					chunk->_materials[x + (y * private_size(*chunk))] = MATERIAL_DIRT;
				} else {
					chunk->_materials[x + (y * private_size(*chunk))] = MATERIAL_ROCK;
				}
				
            } else if (slope < zone.slope_attributes[SNOW_INDEX] && vertex.y < zone.height_attributes[SNOW_INDEX]) {
                
                chunk->_materials[x + (y * private_size(*chunk))] = MATERIAL_SNOW;
                
            } else if (slope < zone.slope_attributes[ROCK_INDEX] && vertex.y <= zone.height_attributes[ROCK_INDEX]) {
				
				chunk->_materials[x + (y * private_size(*chunk))] = MATERIAL_ROCK;
				
			} else {
				
				chunk->_materials[x + (y * private_size(*chunk))] = MATERIAL_ERROR;
				
			}
			
		}
	}
	
	chunk->_data_calculated = true;
}

int compare_elements(const void *a, const void *b) {
	
	const float *ia = (const float *)a;
	const float *ib = (const float *)b;
	
	return *ia - *ib;
	
}

void print_chunk(Chunk chunk) {
	printf("%s, %d, %d\n", at_string_point(chunk.location), chunk.chunk_size, chunk._data_calculated);
}

void draw_chunk(Chunk *chunk) {
	
	// Lazy instantiation
	
	if (chunk->_data_calculated == false) {
		init_data(chunk);
	}
	
	at_bind_texture(chunk->texture);
	
	for (int x = 0; x < private_size(*chunk) - 1; x++) {
		
		glBegin(GL_TRIANGLE_STRIP);
		for (int y = 0; y < private_size(*chunk) - 1; y++) {
			
			ATVertex vertex[4] = {
				chunk->_vertices[x + (y * private_size(*chunk))],
				chunk->_vertices[(x + 1) + (y * private_size(*chunk))],
				chunk->_vertices[x + ((y + 1) * private_size(*chunk))],
				chunk->_vertices[(x + 1) + ((y + 1) * private_size(*chunk))]
			};
			
			ATColor lighting[4] = {
				at_create_color_from_float(chunk->_lighting[x + (y * private_size(*chunk))], 1.0),
				at_create_color_from_float(chunk->_lighting[(x + 1) + (y * private_size(*chunk))], 1.0),
				at_create_color_from_float(chunk->_lighting[x + ((y + 1) * private_size(*chunk))], 1.0),
				at_create_color_from_float(chunk->_lighting[(x + 1) + ((y + 1) * private_size(*chunk))], 1.0)
			};
			
			Zone zone = zone_for_point(*chunk->_generator, at_create_point(chunk->location.x + x, chunk->location.y + y));
			
			at_set_active_rect(&chunk->texture, chunk->rock_texture_rect);
			
			if (chunk->_materials[x + (y * private_size(*chunk))] == MATERIAL_GRASS) {
				at_set_color(at_multiply_color(zone.color_attributes[GRASS_INDEX], lighting[0]));
				at_set_active_rect(&chunk->texture, chunk->grass_texture_rect);
				
			} else if (chunk->_materials[x + (y * private_size(*chunk))] == MATERIAL_DIRT) {
				at_set_color(at_multiply_color(zone.color_attributes[DIRT_INDEX], lighting[0]));
				at_set_active_rect(&chunk->texture, chunk->dirt_texture_rect);
				
			} else if (chunk->_materials[x + (y * private_size(*chunk))] == MATERIAL_ROCK) {
				at_set_color(at_multiply_color(zone.color_attributes[ROCK_INDEX], lighting[0]));
				at_set_active_rect(&chunk->texture, chunk->rock_texture_rect);
				
			} else if (chunk->_materials[x + (y * private_size(*chunk))] == MATERIAL_SNOW) {
				at_set_color(at_multiply_color(zone.color_attributes[SNOW_INDEX], lighting[0]));
				at_set_active_rect(&chunk->texture, chunk->snow_texture_rect);
				
			} else if (chunk->_materials[x + (y* private_size(*chunk))] == MATERIAL_WATER) {
				at_set_color(at_multiply_color(zone.color_attributes[WATER_INDEX], lighting[0]));
				at_set_active_rect(&chunk->texture, chunk->rock_texture_rect);
				
			} else {
				at_set_color(at_multiply_color(ERROR_COLOR, lighting[0]));
				at_set_active_rect(&chunk->texture, chunk->error_texture_rect);
				
			}
			
			at_set_active_point(&chunk->texture, AT_CORNER_LOWER_LEFT);
			at_draw_vertex(vertex[0]);
			
			at_set_active_point(&chunk->texture, AT_CORNER_UPPER_LEFT);
			at_draw_vertex(vertex[1]);
			
			at_set_active_point(&chunk->texture, AT_CORNER_LOWER_RIGHT);
			at_draw_vertex(vertex[2]);
			
			at_set_active_point(&chunk->texture, AT_CORNER_UPPER_RIGHT);
			at_draw_vertex(vertex[3]);
		}
		glEnd();
		
	}
	
	at_unbind_texture();
	
}

ATPoint center_chunk(Chunk chunk) {
	return at_create_point(chunk.location.x + (chunk.chunk_size / 2), chunk.location.y + (chunk.chunk_size / 2));
}
