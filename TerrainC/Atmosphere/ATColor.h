//
//  ATColor.h
//  TerrainProject
//
//  Created by Jeremy School on 5/4/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#define ATBlackColor	at_create_color(0, 0, 0, 1)
#define ATGrayColor		at_create_color(0.5, 0.5, 0.5, 1)
#define ATWhiteColor	at_create_color(1, 1, 1, 1)
#define ATRedColor		at_create_color(1, 0, 0, 1)
#define ATGreenColor	at_create_color(0, 1, 0, 1)
#define ATBlueColor		at_create_color(0, 0, 1, 1)

#ifndef TerrainProject_ATColor_h
#define TerrainProject_ATColor_h

// This is an ATColor, which stores rgba colors like this: {0.67, 0.5, 0.1, 0.5}. It's easy to plugin into the glColor*f() command that way. There is no 3D version :-)
typedef struct {
	
	float r;
	float g;
	float b;
	
	float a;
	
} ATColor;

#endif

ATColor at_create_color(float red, float green, float blue, float alpha);

// Goes inside a glBegin() glEnd() statement
void at_set_color(ATColor color);

ATColor at_create_color_from_float(float intensity, float alpha);
ATColor at_multiply_color(ATColor color, ATColor color2);

char * at_string_color(ATColor color);

void at_print_color(ATColor color);