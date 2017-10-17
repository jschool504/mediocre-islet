//
//  Zone.h
//  TerrainC
//
//  Created by Jeremy School on 2013年6月27日.
//  Copyright (c) 2013 Home. All rights reserved.
//

#include "Atmosphere.h"

#ifndef TerrainC_Zone_h
#define TerrainC_Zone_h

#define MATERIAL_GRASS 0
#define MATERIAL_DIRT 1
#define MATERIAL_ROCK 2
#define MATERIAL_SNOW 3
#define MATERIAL_WATER 4
#define MATERIAL_ERROR 1000

#define GRASS_INDEX 0
#define DIRT_INDEX 1
#define ROCK_INDEX 2
#define SNOW_INDEX 3
#define WATER_INDEX 4

#define inverse_percentage(blend_percentage) blend_percentage

typedef struct {
	
	int id;
	
	ATRect area;
    
	// G,D,R,S,W,E
	float *slope_attributes;
	ATColor *color_attributes;
	float *height_attributes;
	
	float blend_percent;
	
} Zone;

#endif

Zone create_zone(ATRect area, float *slope_attributes, ATColor *color_attributes, float *height_attributes);

//Helper function
float blend_value(float val, float max_val, float l_bound, float h_bound, bool invert);

void print_zone(Zone zone);
