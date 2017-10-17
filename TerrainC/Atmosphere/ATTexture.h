//
//  ATTexture.h
//  TerrainProject
//
//  Created by Jeremy School on 5/4/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#define AT_CORNER_LOWER_LEFT 0
#define AT_CORNER_UPPER_LEFT 1
#define AT_CORNER_UPPER_RIGHT 2
#define AT_CORNER_LOWER_RIGHT 3

#ifndef TerrainProject_ATTexture_h
#define TerrainProject_ATTexture_h

#include <stdbool.h>

#include "ATPoint.h"
#include "ATSize.h"
#include "ATRect.h"

typedef struct {
	
	unsigned int id;	// OpenGL will store all the texture pixels and stuff.
						// All we need is a number referencing the texture.
	
	ATRect active_rect;
	ATSize size;	// This is totally seperate from the active rectangle system.
					// It's the actual size of the texture image.
	
	bool alpha;
	
} ATTexture;

#endif

/*

Dear Future Me,

Ok, so this active_rect stuff is a tad confusing. I apologize. Essentially, the
active rectangle allows you to specify a rectangle that will be used in the
texture. You can set the active corner of this rectangle using
at_set_active_point(texture, index). The index tells Atmosphere which corner
you want active. You can use the contstants AT_CORNER_LOWER_LEFT,
AT_CORNER_UPPER_LEFT, AT_CORNER_UPPER_RIGHT, and AT_CORNER_LOWER_RIGHT to
specify the corner you want.

	//Texture\\
O---------------O
|				|
|				|
|//Active Rect\\|
*-------*		|
|		|		|
|		|		|
|		|		|
*-------*-------O
 
Regards,
Present Me

*/

ATTexture at_create_texture(unsigned char *texture_data, ATSize size, ATRect active_rect, int format, bool alpha);

// Sets the rectangle to be used for the texture
void at_set_active_rect(ATTexture *texture, ATRect active_rect);
// Sets the active corner of the rectangle
void at_set_active_point(ATTexture *texture, int index);
// Returns the active point that will be set using at_set_active_point if it's called
ATPoint at_get_active_point(ATTexture *texture, int index);

// Makes the texture the active texture.
void at_bind_texture(ATTexture texture);

// Disables blending, enables depth testing, disables textures
// Note: you don't actually need to use this function unless you have a texture
// with alpha on it
void at_unbind_texture();

void at_destroy_texture(ATTexture texture);
void at_print_texture(ATTexture texture);
