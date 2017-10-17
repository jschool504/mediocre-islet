//
//  ATFog.h
//  TerrainProject
//
//  Created by Jeremy School on 5/23/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "ATColor.h"

#ifndef TerrainProject_ATFog_h
#define TerrainProject_ATFog_h

typedef struct {
    
    float start_distance;
    float end_distance;
    float density;
    ATColor color;
    int mode;
    int quality;
    
} ATFog;

#endif

ATFog at_create_fog(float start_distance, float end_distance, float density, ATColor color, int mode, int quality);
void at_set_fog(ATFog fog);
void at_unset_fog();
char * at_string_fog(ATFog fog);
void at_print_fog(ATFog fog);

