// This is the Atmosphere drawing library. It's purpose is to assist you in all your OpenGL drawing quests. Use it wisely.

// Of everything in the Terrain Project, this is probably the easiest to understand. Basically, with Atmosphere, I'm trying to create a wrapper to automatically manage some of OpenGL's more mundane tasks (and some abstract ones). The code here all basically does exactly what function name says; I tried to stick with an extremely rigid function naming structure here, to make everything as straightforward as possible.

#include "ATPoint.h"
#include "ATPolygon.h"
#include "ATVertex.h"
#include "ATVector.h"
#include "ATRotation.h"
#include "ATSize.h"
#include "ATTexture.h"
#include "ATColor.h"
#include "ATTexturedPolygon.h"
#include "AtmosphereProjection.h"
#include "ATCamera.h"
#include "ATFog.h"
#include "ATImage.h"
#include "ATAxis.h"
#include "ATMath.h"
#include "ATUtils.h"
#include "ATRect.h"