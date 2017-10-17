//
//  TerrainGenerator.h
//  TerrainC
//
//  Created by Jeremy School on 5/26/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "Zone.h"

#ifndef TerrainC_TerrainGenerator_h
#define TerrainC_TerrainGenerator_h

typedef struct {
	
	//int id;
	int seed;
	int map_size;
	float *mpd_heights;
	
	Zone *zones;
	
	//Readonly
	int num_of_zones;
	
} TerrainGenerator;

#endif

TerrainGenerator create_t_generator(int seed, int map_size);
float interpolate(float min, float max, float progress);
float height_at_point(TerrainGenerator generator, ATPoint point);
Zone zone_for_point(TerrainGenerator generator, ATPoint point);
