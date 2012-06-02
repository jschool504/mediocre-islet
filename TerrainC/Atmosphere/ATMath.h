//
//  ATMath.h
//  TerrainC
//
//  Created by Jeremy School on 5/26/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <math.h>

// Some math macros to make things neater
#define Square(num) ((num) * (num))
#define DistanceToPoint(startPoint, endPoint) (sqrtf(Square(startPoint.x - endPoint.x) + Square(startPoint.y - endPoint.y)))

#define PI_OVER_180 0.01745329251994

#ifndef TerrainC_ATMath_h
#define TerrainC_ATMath_h



#endif
