//
//  AtmosphereProjection.c
//  TerrainProject
//
//  Created by Jeremy School on 5/3/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "AtmosphereProjection.h"
#include "ATRotation.h"
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

void atmosphere_ortho_start(float left, float right, float bottom, float top, float near, float far) {
	
	glPushMatrix(); // Save the current matrix
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
}

void atmosphere_ortho_end() {
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glPopMatrix(); // Restore the old matrix
	
}