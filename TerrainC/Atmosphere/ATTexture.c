//
//  ATTexture.c
//  TerrainProject
//
//  Created by Jeremy School on 5/4/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <GLUT/glut.h>
#include "ATTexture.h"

// Here we get in raw texture data, do all the OpenGL stuff needed to create a texture and stuff the size and position and id into an ATTexture for safekeeping.
ATTexture at_create_texture(unsigned char *texture_data, ATSize size, ATRect active_rect, int format, bool alpha) {
	
	if (texture_data == 0) {
		printf("Why no texture data? :-(");
		ATTexture texture = {0, ATOriginPoint, ATZeroSize, false};
		return texture;
	}
	
	GLuint textureID; // Create a place to store the texture ID
	
	glGenTextures(1, &textureID); // Generate the ID
	glBindTexture(GL_TEXTURE_2D, textureID); // This is now the active texture ID
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	// Actually creates the OpenGL texture
	glTexImage2D(GL_TEXTURE_2D, 0, format, size.width, size.height, 0, format, GL_UNSIGNED_BYTE, texture_data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	
	ATTexture texture;
	texture.id = textureID;
	texture.size = size;
	texture.active_rect = active_rect;
	texture.alpha = alpha;
	
	return texture;
}

void at_set_active_rect(ATTexture *texture, ATRect active_rect) {
	
	texture->active_rect = active_rect;
	
}

// Goes inside glBegin(); glEnd(); calls

void at_set_active_point(ATTexture *texture, int index) {
	
	ATPoint point = at_get_active_point(texture, index);
	glTexCoord2f(point.x, point.y);
	
}

ATPoint at_get_active_point(ATTexture *texture, int index) {
	
	ATPoint active_point;
	
	if (index == AT_CORNER_LOWER_LEFT) {
		
		active_point = at_create_point(texture->active_rect.origin.x / texture->size.width,
				   texture->active_rect.origin.y / texture->size.height);
		
	} else if (index == AT_CORNER_UPPER_LEFT) {
		
		active_point = at_create_point(texture->active_rect.origin.x / texture->size.width,
				   (texture->active_rect.origin.y + texture->active_rect.size.height) / texture->size.height);
		
	} else if (index == AT_CORNER_UPPER_RIGHT) {
		
		active_point = at_create_point((texture->active_rect.origin.x + texture->active_rect.size.width) / texture->size.width,
				   (texture->active_rect.origin.y + texture->active_rect.size.height) / texture->size.height);
		
	} else if (index == AT_CORNER_LOWER_RIGHT) {
		
		active_point = at_create_point((texture->active_rect.origin.x + texture->active_rect.size.width) / texture->size.width,
									   texture->active_rect.origin.y / texture->size.height);
		
	} else {
		printf("Invalid texture corner.");
	}
	
	return active_point;
	
}

void at_bind_texture(ATTexture texture) {
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	
	if (texture.alpha == true) {
		
		glDisable(GL_DEPTH_TEST);
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	
}

void at_unbind_texture() {
	
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	
}

void at_destroy_texture(ATTexture texture) {
	glDeleteTextures(1, &texture.id);
}

void at_print_texture(ATTexture texture) {
	printf("ID: %d Origin: (%f, %f) Size: (W: %f H: %f)\n", texture.id, texture.size.width, texture.size.height);
}
