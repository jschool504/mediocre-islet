//
//  Zone.c
//  TerrainC
//
//  Created by Jeremy School on 2013年6月27日.
//  Copyright (c) 2013 Home. All rights reserved.
//

#include "Zone.h"
#include <stdio.h>
#include <stdlib.h>

int id = 0;

Zone create_zone(ATRect area, float *slope_attributes, ATColor *color_attributes, float *height_attributes) {
	Zone zone;
	zone.id = id;
    id++;
	zone.area = area;
	zone.slope_attributes = slope_attributes;
	zone.color_attributes = color_attributes;
	zone.height_attributes = height_attributes;
	zone.blend_percent = 0.1;
	
	return zone;
}

//put in a value and maximum possible value, get out a percentage of
float blend_value(float val, float max_val, float l_bound, float h_bound, bool invert) {
	float final_val = val/max_val;
	
	//printf("%f / %f = %f\n", val, max_val, final_val);
	
	if (final_val < l_bound) {
		final_val = l_bound;
	}
	
	if (final_val > h_bound) {
		final_val = h_bound;
	}
	
	if (invert) {
		final_val = 1.0 - final_val;
	}
	
	return final_val;
}

void print_zone(Zone zone) {
	printf("Zone ID: %d\n", zone.id);
	printf("Zone area: %s\n", at_string_rect(zone.area));
	printf("Grass max slope: %f\n", (float)zone.slope_attributes[0]);
	printf("Dirt max slope: %f\n", (float)zone.slope_attributes[1]);
	printf("Rock max slope: %f\n", (float)zone.slope_attributes[2]);
	printf("Snow max slope: %f\n", (float)zone.slope_attributes[3]);
	printf("Water max slope: %f\n", (float)zone.slope_attributes[4]);
	printf("Error max slope: %f\n", (float)zone.slope_attributes[5]);
	
	printf("Grass color: %s\n", at_string_color(zone.color_attributes[GRASS_INDEX]));
	printf("Dirt color: %s\n", at_string_color(zone.color_attributes[DIRT_INDEX]));
	printf("Rock color: %s\n", at_string_color(zone.color_attributes[ROCK_INDEX]));
	printf("Snow color: %s\n", at_string_color(zone.color_attributes[SNOW_INDEX]));
	printf("Rock color: %s\n", at_string_color(zone.color_attributes[WATER_INDEX]));
	printf("Error color: %s\n", at_string_color(zone.color_attributes[5]));
	
	printf("Grass max height: %f\n", (float)zone.slope_attributes[GRASS_INDEX]);
	printf("Dirt max height: %f\n", (float)zone.slope_attributes[DIRT_INDEX]);
	printf("Rock max height: %f\n", (float)zone.slope_attributes[ROCK_INDEX]);
	printf("Snow max height: %f\n", (float)zone.slope_attributes[SNOW_INDEX]);
	printf("Water max height: %f\n", (float)zone.slope_attributes[WATER_INDEX]);
	printf("Error max height: %f\n", (float)zone.slope_attributes[5]);
}
