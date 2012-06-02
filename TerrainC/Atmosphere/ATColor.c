//
//  ATColor.c
//  TerrainProject
//
//  Created by Jeremy School on 5/4/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ATColor.h"

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

ATColor at_create_color(float red, float green, float blue, float alpha) {
	ATColor color = {red, green, blue, alpha};
	return color;
}

void at_set_color(ATColor color) {
	glColor4f(color.r, color.g, color.b, color.a);
}

ATColor at_create_color_from_float(float intensity, float alpha) {
	
	return at_create_color(intensity, intensity, intensity, alpha);
	
}

ATColor at_multiply_color(ATColor color, ATColor color2) {
	
	ATColor product_color;
	
	product_color.r = color.r * color2.r;
	product_color.g = color.g * color2.g;
	product_color.b = color.b * color2.b;
	product_color.a = color.a * color2.a;
	
	return product_color;
}

char * at_string_color(ATColor color) {
	char *output = malloc(sizeof(char) * 100);
	sprintf(output, "Color: (R: %f G: %f B: %f A: %f)", color.r, color.g, color.b, color.a);
	return output;
}

void at_print_color(ATColor color) {
	printf("%s\n", at_string_color(color));
}