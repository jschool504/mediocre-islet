//
//  ATImage.h
//  TerrainC
//
//  Created by Jeremy School on 5/30/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "ATSize.h"

#define AT_IMAGE_TYPE_TGA 0

#define TGA_WIDTH_LOCATION 12
#define TGA_HEIGHT_LOCATION 14
#define TGA_DEPTH_LOCATION 16
#define TGA_DATA_LOCATION 18

#define AT_RGB 3
#define AT_RGBA 4

#ifndef TerrainC_ATImage_h
#define TerrainC_ATImage_h

typedef struct {
	
	ATSize size;
	unsigned char depth;
	unsigned char *data;
	
} ATImage;

#endif

ATImage at_load_image_type(char *path, int type);