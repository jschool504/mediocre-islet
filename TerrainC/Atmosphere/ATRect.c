//
//  ATRect.c
//  TerrainC
//
//  Created by Jeremy School on 5/31/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ATRect.h"

ATRect at_create_rect(ATPoint origin, ATSize size) {
	
	ATRect rect;
	rect.origin = origin;
	rect.size = size;
	
	return rect;
	
}

ATRect at_create_rect_numbers(float ox, float oy, float wx, float wy) {
	
	return at_create_rect(at_create_point(ox, oy), at_create_size(wx, wy));
	
}


char * at_string_rect(ATRect rect) {
	
	char * output = malloc(sizeof(char) * 33);
	sprintf(output, "Rect: (X: %f Y: %f) (W: %f H: %f)", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	return output;
	
}

void at_print_rect(ATRect rect) {
	
	printf("%s\n", at_string_rect(rect));
	
}
