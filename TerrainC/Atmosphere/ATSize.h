//
//  ATSize.h
//  TerrainProject
//
//  Created by Jeremy School on 5/4/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#define ATZeroSize	at_create_size(0, 0)

// I figure that these will be useful when working with textures
#define ATSize8		at_create_size(8, 8)
#define ATSize16	at_create_size(16, 16)
#define ATSize32	at_create_size(32, 32)
#define ATSize64	at_create_size(64, 64)
#define ATSize128	at_create_size(128, 128)
#define ATSize256	at_create_size(256, 256)
#define ATSize512	at_create_size(512, 512)
#define ATSize1024	at_create_size(1024, 1024)
#define ATSize2048	at_create_size(2048, 2048)

#ifndef TerrainProject_ATSize_h
#define TerrainProject_ATSize_h

// This is a size struct. I'm still a bit torn (5/2/12) over whether to have a 2D and 3D version or just a 3D version. We'll see what I decide.
typedef struct ATSize {
	
	float width;
	float height;
	
} ATSize;

#endif

// Creating
ATSize at_create_size(float width, float height);

// This will take an ATSize and round it's width and height components up to their closest powers of 2
ATSize at_convert_to_po2(ATSize size);

// Debugging
void at_print_size(ATSize size);