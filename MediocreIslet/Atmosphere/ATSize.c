//
//  ATSize.c
//  TerrainC
//
//  Created by Jeremy School on 5/25/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdbool.h>
#include <stdio.h>
#include "ATSize.h"

ATSize at_create_size(float width, float height) {
	ATSize size = {width, height};
	return size;
}

bool is_po2(int num) {
	
	if (num == 0) {
		return false;
	}
	
	while (num % 2 == 0) {
		num = num / 2;
	}
	
	if (num > 1) {
		return false;
	}
	
	return true;
}

/* Converts each dimension into the next power of 2. Example:
 
 width = 14
 height = 25
 
 Width will equal 16, height 32
 
 The reason for this is that the dimensions of OpenGL textures must be a power of 2 (though they do not have to be the same). As such, I wanted a convienent function to convert ATSizes to texture compatible sizes.
 
 */
ATSize at_convert_to_po2(ATSize size) {
	
	int width = (int)size.width;
	int height = (int)size.height;
	
	// Width
	while (!is_po2(width)) {
		width++;
	}
	
	while (!is_po2(height)) {
		height++;
	}
	
	ATSize finalSize = at_create_size(width, height);
	
	return finalSize;
}

void at_print_size(ATSize size) {
	printf("Width: %f Height: %f", size.width, size.height);
}