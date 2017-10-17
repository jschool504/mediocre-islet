# Task List for TerrainC

Issues
----

### 1 -- FPS drops significantly as total terrain size increases. This likely has to do with nested for loops.

### 2 -- Only chunks that can be seen by the user are rendered, however this often results in chunks directly under the user blinking out of existence in strange ways.

### 3 -- View distance is limited to about 150 units. Anything beyond that will begin to seriously impact framerate. Probably happening because chunk heightmap generation is performed on the main thread (and lazily).

