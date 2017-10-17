//
//  Terrain.c
//  TerrainC
//
//  Created by Jeremy School on 5/26/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Terrain.h"

Terrain create_terrain(ATPoint origin, unsigned int map_size, unsigned int chunk_size, unsigned int view_range,  ATTexture terrain_texture, ATRect texture_rects[5], int seed) {
	Terrain terrain;
	terrain.origin = origin;
	terrain.map_size = map_size;
	terrain.chunk_size = chunk_size;
	terrain.view_range = view_range;
	terrain.seed = seed;
	terrain.draw_wireframe = false;
	terrain.lighting_softness = 1;
	terrain._chunks_per_side = terrain.map_size / terrain.chunk_size;
	terrain.number_of_chunks = Square(terrain._chunks_per_side);
	terrain._chunks_calculated = false;
	
	terrain.terrain_texture = terrain_texture;
	terrain.grass_texture_rect = texture_rects[0];
	terrain.dirt_texture_rect = texture_rects[1];
	terrain.rock_texture_rect = texture_rects[2];
	terrain.snow_texture_rect = texture_rects[3];
	
	terrain.generator = create_t_generator(terrain.seed, terrain.map_size);
	
	return terrain;
}

void destroy_terrain(Terrain terrain) {
	
	free(terrain._chunks);
	
}

float height_for_coord(Terrain terrain, ATPoint coord) {
    float x_percent = coord.x / terrain.map_size;
    float y_percent = coord.y / terrain.map_size;
    int x_chunk = x_percent * terrain._chunks_per_side;
    int y_chunk = y_percent * terrain._chunks_per_side;
    Chunk chunk = chunk_for_coord(terrain, x_chunk, y_chunk);
    return get_height_at_point(chunk, (int)coord.x - (int)chunk.location.x, (int)coord.y - (int)chunk.location.y);
}

Chunk chunk_for_coord(Terrain terrain, int x, int y) {
	return terrain._chunks[x + (y * terrain._chunks_per_side)];
}

void init_chunks(Terrain *terrain) {
	
	terrain->_chunks = malloc(sizeof(Chunk) * Square(terrain->number_of_chunks));
	
	for (int x = 0; x < terrain->_chunks_per_side; x++) {
		for (int y = 0; y < terrain->_chunks_per_side; y++) {
			
			Chunk chunk = create_chunk(at_create_point(x * terrain->chunk_size, y * terrain->chunk_size), terrain->map_size, terrain->chunk_size, terrain->seed);
			chunk._generator = &terrain->generator;
			chunk.lighting_softness = terrain->lighting_softness;
			
			chunk.texture = terrain->terrain_texture;
			chunk.grass_texture_rect = terrain->grass_texture_rect;
			chunk.dirt_texture_rect = terrain->dirt_texture_rect;
			chunk.rock_texture_rect = terrain->rock_texture_rect;
			chunk.snow_texture_rect = terrain->snow_texture_rect;
			chunk.error_texture_rect = terrain->error_texture_rect;
			
			terrain->_chunks[x + (y * terrain->_chunks_per_side)] = chunk;
			
		}
	}
	
	terrain->_chunks_calculated = true;
}

void draw_terrain(Terrain *terrain, ATCamera camera) {
	
	if (terrain->_chunks_calculated == false) {
		init_chunks(terrain);
	}
	
	if (terrain->draw_wireframe == true) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	
	for (int i = 0; i < terrain->number_of_chunks; i++) {
        
        /** This works don't touch it >:( **/
        
		Chunk *chunk = &terrain->_chunks[i];
        ATPoint loc = at_create_point(camera.location.x, camera.location.z);
        int rotation = (int)camera.rotation.y % 360;
        if (rotation < 0) {
            rotation += 360;
        }

        ATPoint chunk_point = center_chunk(*chunk);
        int dist = abs((int)DistanceToPoint(loc, chunk_point));
        
        float diff_x = loc.x - chunk_point.x;
        float diff_y = loc.y - chunk_point.y;
        
        float chunk_angle = atan2f(diff_x, diff_y);
        chunk_angle *= 180 / M_PI;
        if (chunk_angle < 0) {
            chunk_angle += 360;
        }
        
        if (rotation < FOV && chunk_angle>(360-FOV)) {
            chunk_angle -= 360;
        }
        
        if (rotation > (360-FOV) && chunk_angle < FOV) {
            chunk_angle += 360;
        }
        
        int diff = rotation - (int)chunk_angle;
        
        if (diff < FOV && diff > -FOV && dist < terrain->view_range) {
            draw_chunk(chunk);
        }
        
        /** end **/
	}
	
	if (terrain->draw_wireframe == true) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	//print_chunk(terrain._chunks[5 + (5 * terrain.map_size)]);
	
}
