//
//  TerrainGenerator.h
//  TerrainC
//
//  Created by Jeremy School on 5/26/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#ifndef TerrainC_TerrainGenerator_h
#define TerrainC_TerrainGenerator_h

typedef struct {
	
	int seed;
	int map_size;
	float *mpd_heights;
	
} TerrainGenerator;

#endif

TerrainGenerator create_t_generator(int seed, int map_size);
float height_at_point(TerrainGenerator generator, ATPoint point);