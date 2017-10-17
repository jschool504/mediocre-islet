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
#include "ATUtils.h"


ATRect at_create_rect(ATPoint origin, ATSize size) {
	
	ATRect rect;
	rect.origin = origin;
	rect.size = size;
	
	return rect;
	
}

ATRect at_create_rect_numbers(float ox, float oy, float wx, float wy) {
	
	return at_create_rect(at_create_point(ox, oy), at_create_size(wx, wy));
	
}

ATPolygon at_convert_rect_polygon(ATRect rect) {
	ATPoint points[4] = {
		rect.origin,
		at_create_point(rect.origin.x, rect.origin.y + rect.size.height),
		at_create_point(rect.origin.x + rect.size.width, rect.origin.y),
		at_create_point(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height)
	};
	ATColor colors[4] = {
		ATWhiteColor,
		ATWhiteColor,
		ATWhiteColor,
		ATWhiteColor
	};
	return at_create_polygon(rect.origin, 4, points, colors);
}

bool at_rect_contains_point(ATRect rect, ATPoint point) {
	
	if (point.x >= rect.origin.x && point.x <= rect.origin.x + rect.size.width) {
		if (point.y >= rect.origin.y && point.y <= rect.origin.y + rect.size.height) {
			return true;
		}
	}
	
	return false;
}

char * at_string_rect(ATRect rect) {
	
	char * output = malloc(sizeof('a') * 33);
	sprintf(output, "Rect: (X: %f Y: %f) (W: %f H: %f)", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	return output;
	
}

void at_print_rect(ATRect rect) {
	
	printf("%s\n", at_string_rect(rect));
	
}
