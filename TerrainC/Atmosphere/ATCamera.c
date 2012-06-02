//
//  AtmosphereCamera.c
//  TerrainProject
//
//  Created by Jeremy School on 5/10/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

#include "ATCamera.h"

#define PI_OVER_180 0.01745329251994

ATCamera at_create_camera(ATVertex location, ATRotation rotation) {
	
	ATCamera camera = {location, rotation};
	return camera;
	
}

void at_set_camera(ATCamera camera) {
	
	glPushMatrix();
	
	glRotatef(-camera.rotation.x, 1, 0, 0);
	glRotatef(-camera.rotation.y, 0, 1, 0);
	glRotatef(-camera.rotation.z, 0, 0, 1);
	
	glTranslatef(-camera.location.x, 0, 0);
	glTranslatef(0, -camera.location.y, 0);
	glTranslatef(0, 0, -camera.location.z);
	
}

void at_unset_camera() {
	glPopMatrix(); // Undo the changes made by the camera
}

char * at_string_camera(ATCamera camera) {
	char *loc = malloc(sizeof(char) * 50);
	char *rot = malloc(sizeof(char) * 50);
	
	char *cameraOutput = malloc(sizeof(char) * 150);
	
	sprintf(loc, "Location: (X: %f Y: %f Z: %f)", camera.location.x, camera.location.y, camera.location.z);
	sprintf(rot, "Rotation: (X: %f Y: %f Z: %f)", camera.rotation.x, camera.rotation.y, camera.rotation.z);
	
	sprintf(cameraOutput, "%s\n%s", loc, rot);
	
	free(loc);
	free(rot);
	
	return cameraOutput;
}

void at_print_camera(ATCamera camera) {
	
	printf("%s\n\n", at_string_camera(camera));
	
}