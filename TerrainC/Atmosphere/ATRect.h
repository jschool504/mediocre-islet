//
//  ATRect.h
//  TerrainC
//
//  Created by Jeremy School on 5/31/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "ATPoint.h"
#include "ATSize.h"

#define ATZeroRect at_create_rect(ATOriginPoint, ATZeroSize)

#ifndef TerrainC_ATRect_h
#define TerrainC_ATRect_h

typedef struct {
	
	ATPoint origin;
	ATSize size;
	
} ATRect;

#endif

ATRect at_create_rect(ATPoint origin, ATSize size);
ATRect at_create_rect_numbers(float ox, float oy, float wx, float wy);

char * at_string_rect(ATRect rect);
void at_print_rect(ATRect rect);