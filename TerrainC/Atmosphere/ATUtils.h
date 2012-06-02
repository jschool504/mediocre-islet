//
//  ATUtils.h
//  TerrainC
//
//  Created by Jeremy School on 5/28/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "ATVertex.h"
#include "ATPoint.h"

#include <time.h>

clock_t startTime;

#define AT_TIMING_START startTime = clock();
#define AT_TIMING_END printf("%f\n", at_duration(startTime));

ATVertex at_convert_point(ATPoint point);
ATPoint at_convert_vertex(ATVertex vertex);

void at_draw_string(int x, int y, char *string);

float at_duration(clock_t startTime);