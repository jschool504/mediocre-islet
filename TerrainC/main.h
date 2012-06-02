//
//  main.h
//  TerrainC
//
//  Created by Jeremy School on 5/25/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "Atmosphere.h"
#include "Terrain.h"
#include <stdbool.h>

#define MOV_SPEED 1
#define ROT_SPEED 3

#define TERRAIN_SIZE 10240
#define CHUNK_SIZE 32
#define VIEW_RANGE 128

#define LIGHTING_SOFTNESS 25

#ifndef TerrainC_main_h
#define TerrainC_main_h

// This holds all your "instance" vars
typedef struct {
	
	ATCamera camera;
	ATAxis axis[3];
	Terrain terrain;
	ATTexture grass;
	ATImage grassImg;
	ATImage dirtImg;
	
	int view_range;
	
	bool gl_inited;
	
} AppStruct;

#endif

AppStruct app_struct;

void init_glut();
void init_gl();
void reshape(int width, int height);
void draw();
void idle();
void key_pressed(unsigned char key, int x, int y);