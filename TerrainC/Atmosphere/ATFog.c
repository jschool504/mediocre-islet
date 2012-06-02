//
//  ATFog.c
//  TerrainProject
//
//  Created by Jeremy School on 5/23/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include "ATFog.h"

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

ATFog at_create_fog(float start_distance, float end_distance, float density, ATColor color, int mode, int quality) {
	
	ATFog fog = {start_distance, end_distance, density, color, mode, quality};
	return fog;
	
}

void at_set_fog(ATFog fog) {
	
	glEnable(GL_FOG);
	glFogf(GL_FOG_START, fog.start_distance);
	glFogf(GL_FOG_END, fog.end_distance);
	glFogi(GL_FOG_MODE, fog.mode);
	GLfloat fogColor[4] = {fog.color.r, fog.color.g, fog.color.b, 1.0};
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, fog.density);
	glHint(GL_FOG_HINT, fog.quality);
	
}

void at_unset_fog() {
	
	glDisable(GL_FOG);
	
}

char * at_string_fog(ATFog fog) {
	
}

void at_print_fog(ATFog fog) {
	
}
