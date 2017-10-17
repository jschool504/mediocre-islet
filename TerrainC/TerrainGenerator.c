//
//  TerrainGenerator.c
//  TerrainC
//
//  Created by Jeremy School on 5/26/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Atmosphere.h"
#include "TerrainGenerator.h"

#define ZONE_SIZE 100
#define ZONE_BLEND_PERCENT 0.1

#define NUM_OF_TERRAINS_PER_SIDE generator.map_size / ZONE_SIZE

//#define MAP_DIVISOR 81.6

#define BlendValue(val) (val + 1) / ((float)generator.map_size / (float)ZONE_SIZE)

#define BlendValueInverse(val) 1 - ((val + 1) / ((float)generator.map_size / (float)ZONE_SIZE))

void initMPD(TerrainGenerator *generator);

float getHeightAtPoint(ATPoint point, float frequency, float amplitude, float height, float seed);
float smoothedNoise(float x, float y, float height, int seed);
float randomFloat(int x, int y, float height, int seed);
float cosine(float x1, float x2, float a);

#define NUM_MOUNTAINS 10
#define MAX_MOUNTAIN_RADIUS 120
#define MIN_MOUNTAIN_RADIUS 45
ATVector *mountains;

TerrainGenerator create_t_generator(int seed, int map_size) {
	
	TerrainGenerator generator = {seed, map_size};
	
	generator.num_of_zones = (generator.map_size / ZONE_SIZE) * (generator.map_size / ZONE_SIZE);
	
	generator.zones = malloc(sizeof(Zone) * generator.num_of_zones);
    
    mountains = malloc(sizeof(ATVector) * NUM_MOUNTAINS);
    srand(seed);
    for (int mi = 0; mi < NUM_MOUNTAINS; mi++) {
        mountains[mi] = at_create_vector(rand() % generator.map_size,
                                         rand() % generator.map_size,
                                         interpolate(MIN_MOUNTAIN_RADIUS, MAX_MOUNTAIN_RADIUS, randomFloat(rand(), rand(), map_size, seed)));
    }
	
	//x = W-E
	//y = N-S
	
	for (int x = 0; x < generator.map_size / ZONE_SIZE; x++) {
		for (int y = 0; y < generator.map_size / ZONE_SIZE; y++) {
			
			float *slope_criteria = malloc(sizeof(float) * 6);
			slope_criteria[GRASS_INDEX] = 0.45;
			slope_criteria[DIRT_INDEX] = 0.6;
			slope_criteria[ROCK_INDEX] = INFINITY;
			slope_criteria[SNOW_INDEX] = 0.6;
			slope_criteria[WATER_INDEX] = 0;
			
            // TODO: refactor this to a better name, as it is relating to material height cutoffs, not vertex heights
			float *height_criteria = malloc(sizeof(float) * 6);
			height_criteria[GRASS_INDEX] = interpolate(0, 130, y / (float)(generator.map_size/2 / ZONE_SIZE));
			height_criteria[DIRT_INDEX] = interpolate(0, 130, y / (float)(generator.map_size/2 / ZONE_SIZE));
			height_criteria[ROCK_INDEX] = INFINITY;
			height_criteria[SNOW_INDEX] = INFINITY;
			height_criteria[WATER_INDEX] = 40;
			
			ATColor *colors = malloc(sizeof(ATColor) * 6);
			colors[GRASS_INDEX] = at_create_color(interpolate(0, 0.4, y/(float)(generator.map_size / ZONE_SIZE)),
                                                  interpolate(0.2, 0.85, y/(float)(generator.map_size / ZONE_SIZE)),
                                                  interpolate(0, 0.3, y/(float)(generator.map_size / ZONE_SIZE)), 1.0);
			colors[DIRT_INDEX] = at_create_color(0.3, 0.2, 0.1, 1.0);
			colors[ROCK_INDEX] = at_create_color(0.5, 0.5, 0.5, 1.0);
			colors[SNOW_INDEX] = at_create_color(1, 1, 1, 1.0);
			colors[WATER_INDEX] = at_create_color(0, 0, 0.9, 1.0);

            ATRect zone_rect = at_create_rect(at_create_point(x * ZONE_SIZE, y * ZONE_SIZE), at_create_size(ZONE_SIZE, ZONE_SIZE));
            
			Zone zone = create_zone(zone_rect, slope_criteria, colors, height_criteria);
            
            // normal zone blend area is 10%, increase that to 20% for more northern zones
			zone.blend_percent = ZONE_BLEND_PERCENT;
            if (zone.height_attributes[GRASS_INDEX] < 80) {
                zone.blend_percent = 0.2;
            }

			generator.zones[x + (y * generator.map_size / ZONE_SIZE)] = zone;
		}
	}
	
	return generator;
}

// INTERPOLATION!!!
float interpolate(float min, float max, float progress) {
    return min + ((max - min) * progress);
}

float average(float a, float b, float c) {
    return a + b / 2;
}

// Side-effect note: this method does not return a strictly true zone for a
// given point. Instead, if a point is within 10% of the edge of a zone, it will
// randomly select a point from an adjacent zone to create a sort of blended
// transition area between bordering zones
Zone zone_for_point(TerrainGenerator generator, ATPoint point) {

	for (int zone_count = 0; zone_count < generator.num_of_zones; zone_count++) {
        Zone zone = generator.zones[zone_count];
        
		if (at_rect_contains_point(generator.zones[zone_count].area, point)) {
			int start_x = zone.area.origin.x / ZONE_SIZE;
			int start_y = zone.area.origin.y / ZONE_SIZE;
            
            int zone_x = start_x;
            int zone_y = start_y;
			
			float x_percentage_of_zone = (point.x - zone.area.origin.x) / ZONE_SIZE;
			float y_percentage_of_zone = (point.y - zone.area.origin.y) / ZONE_SIZE;
            
            float blend_zone_percent = x_percentage_of_zone;
            float in_x_blend_zone_percent = -((x_percentage_of_zone - zone.blend_percent) / zone.blend_percent);
            float out_x_blend_zone_percent = (x_percentage_of_zone - (1 - zone.blend_percent)) / zone.blend_percent;
            float in_y_blend_zone_percent = -(y_percentage_of_zone - zone.blend_percent) / zone.blend_percent;
            float out_y_blend_zone_percent = (y_percentage_of_zone - (1 - zone.blend_percent)) / zone.blend_percent;
            
            srand(point.x * point.y);
            int do_corner_chance = rand() % 100;
            
            /** Following is code to blend zones together at their borders... **/
            
            // bottom side
            if (y_percentage_of_zone > 1 - zone.blend_percent) {
                
                // left corner
                if (x_percentage_of_zone < zone.blend_percent) {
                    
                    // grab left
                    if (do_corner_chance < 33) {
                        blend_zone_percent = in_x_blend_zone_percent;
                        zone_x -= 1;

                    // grab left-bottom
                    } else if (do_corner_chance < 66) {
                        blend_zone_percent = in_x_blend_zone_percent;
                        zone_x -= 1;
                        zone_y += 1;

                    // grab bottom
                    } else if (do_corner_chance < 100) {
                        blend_zone_percent = out_y_blend_zone_percent;
                        zone_y += 1;
                    }
                    
                    // increase likelyhood of choosing an adjacent zone by 20%
                    // because we are in a corner
                    blend_zone_percent += 0.2;
                
                // right corner
                } else if (x_percentage_of_zone > 1 - zone.blend_percent) {
                    
                    // grab right
                    if (do_corner_chance < 33) {
                        blend_zone_percent = out_x_blend_zone_percent;
                        zone_x += 1;

                    // grab right-bottom
                    } else if (do_corner_chance < 66) {
                        blend_zone_percent = out_x_blend_zone_percent;
                        zone_x += 1;
                        zone_y += 1;
    
                    // grab bottom
                    } else {
                        blend_zone_percent = out_y_blend_zone_percent;
                        zone_y += 1;
                    }
                    
                    // increase likelyhood of choosing an adjacent zone by 20%
                    // because we are in a corner
                    blend_zone_percent += 0.2;
                
                // bottom side
                } else {
                    blend_zone_percent = out_y_blend_zone_percent;
                    zone_y += 1;
                }
            
            // top side
            } else if (y_percentage_of_zone < zone.blend_percent) {

                // left corner
                if (x_percentage_of_zone < zone.blend_percent) {
                    
                    // grab left
                    if (do_corner_chance < 33) {
                        blend_zone_percent = in_x_blend_zone_percent;
                        zone_x -= 1;
                    
                    // grab left-top
                    } else if (do_corner_chance < 66) {
                        blend_zone_percent = in_x_blend_zone_percent;
                        zone_x -= 1;
                        zone_y -= 1;
                    
                    // grab top
                    } else {
                        blend_zone_percent = in_x_blend_zone_percent;
                        zone_y -= 1;
                    }
                    
                // right corner
                } else if (x_percentage_of_zone > 1 - zone.blend_percent) {
                    
                    // grab right
                    if (do_corner_chance < 33) {
                        blend_zone_percent = out_x_blend_zone_percent;
                        zone_x += 1;

                    // grab right-top
                    } else if (do_corner_chance < 66) {
                        blend_zone_percent = out_x_blend_zone_percent;
                        zone_x += 1;
                        zone_y -= 1;

                    // grab top
                    } else {
                        blend_zone_percent = in_y_blend_zone_percent;
                        zone_y -= 1;
                    }
                    
                    // increase likelyhood of choosing an adjacent zone by 20%
                    // because we are in a corner
                    blend_zone_percent += 0.2;
                
                // top side
                } else {
                    blend_zone_percent = in_y_blend_zone_percent;
                    zone_y -= 1;
                }

            // left
            } else if (x_percentage_of_zone < zone.blend_percent) {
                zone_x -= 1;
                blend_zone_percent = in_x_blend_zone_percent;
                
            // right
            } else if (x_percentage_of_zone > 1 - zone.blend_percent) {
                zone_x += 1;
                blend_zone_percent = out_x_blend_zone_percent;
            }
            
            int rand_num = (int)(randomFloat(point.x, point.y, generator.map_size, 0) * 100);
            
            if (rand_num < interpolate(0, 50, blend_zone_percent)) {
                Zone adjacent_zone = generator.zones[zone_x + (zone_y * NUM_OF_TERRAINS_PER_SIDE)];
                
                // validate the zone (make sure we didn't grab one from beyond the edge of the terrain)
                // zone id is pulled from a variable that is incremented by 1 every time a new zone is created
                if (adjacent_zone.id > 0 && adjacent_zone.id < generator.num_of_zones) {
                    return create_zone(zone.area,
                                       zone.slope_attributes,
                                       adjacent_zone.color_attributes,
                                       adjacent_zone.height_attributes);
                }
            }
			
            return zone;
		}
	}
	
    // no zone found for the given point
	float attrs[6] = {0,0,0,0,0,0};
	ATColor colors[6] = {
		ATWhiteColor,
		ATWhiteColor,
		ATWhiteColor,
		ATWhiteColor,
		ATWhiteColor,
		ATWhiteColor
	};

	return create_zone(ATZeroRect, attrs, colors, attrs);
}

// super star method :) gets the height for a given x, y coordinate
float height_at_point(TerrainGenerator generator, ATPoint point) {
    
    Zone zone = zone_for_point(generator, point);
    
    float dist = DistanceToPoint(point, at_create_point(generator.map_size / 2, generator.map_size / 2));
    float center_x = generator.map_size / 2;
    float max_dist = sqrt(2) * center_x;
    
    // initial height bias
    float total = interpolate(100, 0, dist/max_dist);
    total += getHeightAtPoint(point, 0.05, 15, generator.map_size, 1);
    
    if (dist > (generator.map_size * 0.5)) {
        total = zone.height_attributes[WATER_INDEX];
    }
    
    if (total <= zone.height_attributes[WATER_INDEX]) {
        total = zone.height_attributes[WATER_INDEX];
    }
    
    for (int i = 0; i < NUM_MOUNTAINS; i++) {
        ATVector mountain = mountains[i];
        float distance_to_mountain = DistanceToPoint(point, mountain);
        if (distance_to_mountain < mountain.z) {
            total += cosine(60, 0, distance_to_mountain/mountain.z);
        }
    }
    
    return total;
}

float getHeightAtPoint(ATPoint point, float frequency, float amplitude, float height, float seed) {
    float height_total = (smoothedNoise(point.x * frequency, point.y * frequency, height, seed)) * amplitude;
    //height_total = (((smoothedNoise(point.x * frequency * 0.3, point.y * frequency * 0.3, height, seed)) * amplitude * 2) + height_total) / 2;
    return height_total;
    //return randomFloat(point.x, point.y, height, seed);
}

float randomFloat(int x, int y, float height, int seed) {
	long r;
    float s;
	
	srandom(y * height + x + seed);
	
	r = random();
	
    s = (float)(r & 32767) / 32767.0; // ?
	
    return (s);
}

float cosine(float x1, float x2, float a) {
	float temp;
	temp = (1.0f - cosf(a * 3.1415927f)) / 2.0f;
	
	return (x1 * (1.0f - temp) + x2 * temp);
}

float smoothedNoise(float x, float y, float height, int seed) {
	int intX = (int)x;
	int intY = (int)y;
	
	float remX = x - (float)intX;
	float remY = y - (float)intY;
	
	float v1, v2, v3, v4, t1, t2;
	
	//cosine interpolation
	v1 = randomFloat(intX, intY, height, seed);
	v2 = randomFloat(intX + 1, intY, height, seed);
	v3 = randomFloat(intX, intY + 1, height, seed);
	v4 = randomFloat(intX + 1, intY + 1, height, seed);
	
	t1 = cosine(v1, v2, remX);
	t2 = cosine(v3, v4, remX);
	
	return cosine(t1, t2, remY);
	 
}
