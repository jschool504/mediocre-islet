//
//  ATRotation.c
//  TerrainProject
//
//  Created by Jeremy School on 5/10/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "ATRotation.h"

ATRotation at_create_rotation(float x, float y, float z) {
	ATRotation rotation = {x, y, z};
	return rotation;
}

char * at_string_rotation(ATRotation rotation) {
	char *output = malloc(sizeof(char) * 100);
	sprintf(output, "Rotation: (X: %f Y: %f Z: %f)", rotation.x, rotation.y, rotation.z);
	return output;
}

void at_print_rotation(ATRotation rotation) {
	printf("%s\n", at_string_rotation(rotation));
}