//
//  main.h
//  TerrainC
//
//  Created by Jeremy School on 5/25/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "Atmosphere/Atmosphere.h"
#include "Terrain.h"
#include <stdbool.h>

#define MOV_SPEED 2
#define ROT_SPEED 4

#define TERRAIN_SIZE 5000
#define CHUNK_SIZE 10
#define VIEW_RANGE 150
#define POV_HEIGHT 5

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
	
    bool lock_camera_to_ground;
	bool gl_inited;
	
} AppStruct;

#endif

AppStruct app_struct;

void init_glut();
void init_gl();
void reshape(int width, int height);
void set_view_range(int view_range);
void draw();
void idle();
void key_pressed(unsigned char key, int x, int y);
