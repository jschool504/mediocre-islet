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

void initMPD(TerrainGenerator *generator);

float getHeightAtPoint(ATPoint point, float frequency, float amplitude, float height, float seed);
float smoothedNoise(float x, float y, float height, int seed);
float randomFloat(int x, int y, float height, int seed);
float cosine(float x1, float x2, float a);

TerrainGenerator create_t_generator(int seed, int map_size) {
	TerrainGenerator generator = {seed, map_size};
	
	initMPD(&generator);
	
	return generator;
}

void initMPD(TerrainGenerator *generator) {
	
	generator->mpd_heights = malloc(sizeof(float) + ((Square(generator->map_size) + 1)));
	
	srandom(generator->seed);
	
	// Set the corners
	generator->mpd_heights[0 + (0 * generator->map_size)] = random() % ROUGHNESS;
	generator->mpd_heights[generator->map_size + (0 * generator->map_size)] = random() % ROUGHNESS;
	generator->mpd_heights[0 + (generator->map_size * generator->map_size)] = random() % ROUGHNESS;
	generator->mpd_heights[generator->map_size + (generator->map_size * generator->map_size)] = random() % ROUGHNESS;
	
	int offset = generator->map_size;
	int range = ROUGHNESS;
	int rangeModifier = 0.7;
	float temp;
	bool oddx, oddy;
	
	while (offset > 0) {
		
		oddy = false;
		
		for (int x = 0; x < generator->map_size; x++) {
			
			oddx = false;
			
			for (int y = 0; y < generator->map_size; y++) {
				
				// if this is a center
				if (oddx && oddy) {
					
					float lowerLeft = generator->mpd_heights[(x - offset) + ((y - offset) * generator->map_size)];
					float upperLeft = generator->mpd_heights[(x - offset) + ((y + offset) * generator->map_size)];
					float upperRight = generator->mpd_heights[(x + offset) + ((y + offset) * generator->map_size)];
					float lowerRight = generator->mpd_heights[(x + offset) + ((y - offset) * generator->map_size)];
					
					temp = ((lowerLeft + upperLeft + upperRight + lowerRight) / 4) + (random() % range);
					
				} else { // if this is a side
					
					// horizontal side
					if (oddx) {
						
						float right = generator->mpd_heights[(x + offset) + (y * generator->map_size)];
						float left = generator->mpd_heights[(x - offset) + (y * generator->map_size)];
						
						temp = ((right + left) / 2) + (random() % range);
						
					} else { // vertical side
						
						float above = generator->mpd_heights[x + ((y + offset) * generator->map_size)];
						float below = generator->mpd_heights[x + ((y - offset) * generator->map_size)];
						
						temp = ((above + below) / 2) + (random() % range);
						
					}
					
				}
				
				generator->mpd_heights[x + (y * generator->map_size)] = temp;
				
			}
		}
		
		range *= rangeModifier;
		offset /= 2;
		
	}
	
}

float height_at_point(TerrainGenerator generator, ATPoint point) {
	
	/*
	float frequency = 1;
	float persistence = 0.65;
	float amplitude = persistence;
	int octaves = 9;
	
	float total = 0.0;
	
	for (int i = 0; i < octaves; i++) {
		
		total += getHeightAtPoint(point, frequency, amplitude, generator.map_size, generator.seed);
		
		frequency *= 2;
		amplitude *= persistence;
		
	}
	*/
	/*
	float total;
	
	float total0 = getHeightAtPoint(point, 0.0009, 50, generator.map_size, generator.seed);
	float total1 = getHeightAtPoint(point, 0.0045, total0, generator.map_size, generator.seed);
	float total2 = getHeightAtPoint(point, 0.0225, total1, generator.map_size, generator.seed);
	float total3 = getHeightAtPoint(point, 0.1125, total2, generator.map_size, generator.seed);
	
	total = total0 + total1 + total2 + total3;
	*/
	
	
	
	return generator.mpd_heights[(int)point.x + ((int)point.y * generator.map_size)];
}

// My understanding of the code is somewhat sketchy after this point

float randomFloat(int x, int y, float height, int seed) {
	int r;
    float s;
	
	srandom(y * height + x + seed);
	
	r = random();
	
    s = (float)(r & 0x7fff)/(float)0x7fff;
	
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

float getHeightAtPoint(ATPoint point, float frequency, float amplitude, float height, float seed) {
	return (smoothedNoise(point.x * frequency, point.y * frequency, height, seed)) * amplitude;
}