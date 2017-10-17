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

// I used this weird capitalization to avoid any potential naming conflicts
#define AT_TIMING_START float StArTtImE = clock();
#define AT_TIMING_END printf("%f\n", at_duration(StArTtImE));

#define PRINT_TO_SCREEN(new_string) sprintf(screen_output, "%s\n%s", screen_output, new_string)
#define LINE_HEIGHT 0.034

ATVertex at_convert_point(ATPoint point);
ATPoint at_convert_vertex(ATVertex vertex);

char *screen_output;

void at_start_screen_output(int num_of_chars);
void at_end_screen_output();
void at_print_screen(char *string);
void at_draw_string(float x, float y, char *string);

float at_duration(clock_t startTime);