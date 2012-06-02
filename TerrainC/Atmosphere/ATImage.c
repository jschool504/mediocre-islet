//
//  ATImage.c
//  TerrainC
//
//  Created by Jeremy School on 5/30/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ATImage.h"

ATImage load_tga_data(char *path);

ATImage at_load_image_type(char *path, int type) {
	
	ATImage image;
	
	if (type == AT_IMAGE_TYPE_TGA) {
		image = load_tga_data(path);
	}
	
	return image;
}

ATImage load_tga_data(char *path) {
	
	ATImage *image = NULL;
	FILE *filePtr = NULL;
	int mode, totalBytes;
	
	image = malloc(sizeof(ATImage));
	
	filePtr = fopen(path, "rb");
	
	if (filePtr == NULL) {
		perror("Crap, The file wasn't loaded");
	} else {
		
		// Load image info
		
		short w, h;
		
		fseek(filePtr, TGA_WIDTH_LOCATION, SEEK_SET);
		fread(&w, sizeof(short), 1, filePtr);
		
		fseek(filePtr, TGA_HEIGHT_LOCATION, SEEK_SET);
		fread(&h, sizeof(short), 1, filePtr);
		
		fseek(filePtr, TGA_DEPTH_LOCATION, SEEK_SET);
		fread(&image->depth, sizeof(short), 1, filePtr);
		
		image->size.width = (float)w;
		image->size.height = (float)h;
		
		// Load image data
		
		mode = image->depth / 8;
		
		totalBytes = (image->size.height * image->size.width) * mode;
		
		printf("W: %f, H: %f, D: %d, M: %d, B: %d\n", image->size.width, image->size.height, image->depth, mode, totalBytes);
		
		image->data = malloc(sizeof(unsigned char) * totalBytes);
		
		fseek(filePtr, TGA_DATA_LOCATION, SEEK_SET);
		fread(image->data, sizeof(unsigned char), totalBytes, filePtr);
		
		fclose(filePtr);
	}
	
	return *image;
}