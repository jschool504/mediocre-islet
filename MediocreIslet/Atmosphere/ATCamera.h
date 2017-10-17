//
//  AtmosphereCamera.h
//  TerrainProject
//
//  Created by Jeremy School on 5/10/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "ATVertex.h"
#include "ATRotation.h"

#ifndef TerrainProject_ATCamera_h
#define TerrainProject_ATCamera_h

typedef struct {
	
	ATVertex location; // Remember, this will set the location of the camera in world coords.
	ATRotation rotation;
	
} ATCamera;

#endif

ATCamera at_create_camera(ATVertex location, ATRotation rotation);

void at_set_camera(ATCamera camera);
void at_unset_camera();

char * at_string_camera(ATCamera camera);

void at_print_camera(ATCamera camera);