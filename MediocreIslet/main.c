//
//  main.c
//  TerrainC
//
//  Created by Jeremy School on 5/25/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

#include <GLUT/glut.h>

int main(int argc, char * argv[]) {
	app_struct.camera = at_create_camera(at_create_vertex(TERRAIN_SIZE / 2, 150, TERRAIN_SIZE / 2), at_create_rotation(-45, 0, 0));
    app_struct.lock_camera_to_ground = false;
	
	app_struct.axis[0] = at_create_axis(ATVectorX, 1000, ATRedColor);
	app_struct.axis[1] = at_create_axis(ATVectorY, 1000, ATGreenColor);
	app_struct.axis[2] = at_create_axis(ATVectorZ, 1000, ATBlueColor);
	
	app_struct.gl_inited = false;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Terrain C");
	
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(key_pressed);
	
	glutMainLoop();
	
    return 0;
}

void init_gl() {
	
    ATColor sky_color = ATGrayColor;
	glClearColor(sky_color.r, sky_color.g, sky_color.b, sky_color.a);
	glClearDepth(1.0);
	
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	
	glShadeModel(GL_FLAT);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
	
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	
	glRasterPos2i(0, 0);
}

// GLUT callbacks
void reshape(int width, int height) {
	
	//printf("%f\n", (float)width / (float)height);
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)width / (float)height, 0.1, 1024);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Do drawing here
void draw() {
	
	if (app_struct.gl_inited == false) {
		init_gl();
		
		app_struct.grassImg = at_load_image_type("terrain_textures.tga", AT_IMAGE_TYPE_TGA);
		
		ATTexture texture = at_create_texture(app_struct.grassImg.data, at_create_size(80, 16), ATZeroRect, GL_RGB, false);
		
		texture.active_rect = at_create_rect(ATOriginPoint, at_create_size(16, 16));
		
		ATRect rects[5] = {
			
			at_create_rect(ATOriginPoint, ATSize16),
			at_create_rect(at_create_point(16, 0), ATSize16),
			at_create_rect(at_create_point(32, 0), ATSize16),
			at_create_rect(at_create_point(48, 0), ATSize16),
			at_create_rect(at_create_point(64, 0), ATSize16)
			
		};
		
		app_struct.terrain = create_terrain(ATOriginPoint, TERRAIN_SIZE, CHUNK_SIZE, VIEW_RANGE, texture, rects, 1);
		app_struct.terrain.draw_wireframe = false;
        
        set_view_range(VIEW_RANGE);
		app_struct.gl_inited = true;
	}
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	at_set_camera(app_struct.camera);
	
	at_draw_axis(app_struct.axis[0]);
	at_draw_axis(app_struct.axis[1]);
	at_draw_axis(app_struct.axis[2]);
	
	clock_t startTime = clock();
	
	app_struct.terrain.view_range = app_struct.view_range;
	draw_terrain(&app_struct.terrain, app_struct.camera);
	
	clock_t endTime = clock();
	float dTime = (1.0 / difftime(endTime, startTime)) * (CLOCKS_PER_SEC * 10);
	
	char output[1000];
    Zone current_zone = zone_for_point(app_struct.terrain.generator, at_create_point(app_struct.camera.location.x, app_struct.camera.location.z));

    int rotation = (int)app_struct.camera.rotation.y % 360;
    if (rotation < 0) {
        rotation += 360;
    }

    sprintf(output,
            "FPS: %0.1f View Range: %d\nLocation: (X: %f Y: %f Z: %f)\nRotation: %d\nZone %s\nMax Grass Height: %f | Max Dirt Height: %f",
            dTime,
            app_struct.view_range, app_struct.camera.location.x, app_struct.camera.location.y, app_struct.camera.location.z,
            rotation,
            at_string_point(current_zone.area.origin),
            current_zone.height_attributes[GRASS_INDEX], current_zone.height_attributes[DIRT_INDEX]);
	at_draw_string(0, 1 - LINE_HEIGHT * 1, output);
	
	at_unset_camera();
	
	glutSwapBuffers();
}

void set_view_range(int view_range) {
    app_struct.view_range = view_range;
    ATFog fog = at_create_fog(view_range - 40, view_range - 15, 0.8, ATGrayColor, GL_LINEAR, GL_DONT_CARE);
    at_set_fog(fog);
}

// Make sure the next frame is drawn as soon as GLUT is idle
void idle() {
	glutPostRedisplay();
}

void key_pressed(unsigned char key, int x, int y) {
	//printf("%hhu\n", key);
	
	//          d c = camera
	//        / | d = destination
	// dist /   | dist = distance to travel
	//    / ang | ang = angle of c
	//  / - |   |
	// c--------a
	
	// i, j, k, l move according to world axes
	
	if (key == 'I') {
		app_struct.camera.location.y += MOV_SPEED;
	}
	
	if (key == 'K') {
		app_struct.camera.location.y -= MOV_SPEED;
	}
	
	if (key == 'i') {
		app_struct.camera.location.z -= MOV_SPEED;
	}
	
	if (key == 'k') {
		app_struct.camera.location.z += MOV_SPEED;
	}
	
	if (key == 'j') {
		app_struct.camera.location.x -= MOV_SPEED;
	}
	
	if (key == 'l') {
		app_struct.camera.location.x += MOV_SPEED;
	}
	
	if (key == 'w') {
		app_struct.camera.location.x -= sinf(app_struct.camera.rotation.y * PI_OVER_180) * MOV_SPEED;
		app_struct.camera.location.y += sinf(app_struct.camera.rotation.x * PI_OVER_180) * MOV_SPEED;
		app_struct.camera.location.z -= cosf(app_struct.camera.rotation.y * PI_OVER_180) * MOV_SPEED;
	}
	
	if (key == 's') {
		app_struct.camera.location.x += sinf(app_struct.camera.rotation.y * PI_OVER_180) * MOV_SPEED;
		app_struct.camera.location.y -= sinf(app_struct.camera.rotation.x * PI_OVER_180) * MOV_SPEED;
		app_struct.camera.location.z += cosf(app_struct.camera.rotation.y * PI_OVER_180) * MOV_SPEED;
	}
	
	if (key == 'a') {
		app_struct.camera.rotation.y += ROT_SPEED;
	}
	
	if (key == 'd') {
		app_struct.camera.rotation.y -= ROT_SPEED;
	}
	
	if (key == '=') {
		app_struct.camera.rotation.x += ROT_SPEED;
	}
	
	if (key == '-') {
		app_struct.camera.rotation.x -= ROT_SPEED;
	}
	
	if (key == 'W') {
		app_struct.terrain.draw_wireframe = !app_struct.terrain.draw_wireframe;
	}
	
	if (key == 'R') {
		app_struct.camera = at_create_camera(ATOriginVertex, ATZeroRotation);
	}
	
	if (key == '+') {
        set_view_range(app_struct.view_range + 10);
	}
	
	if (key == '_') {
		set_view_range(app_struct.view_range - 10);
	}
	
	if (key == 'C') {
		if (glIsEnabled(GL_CULL_FACE)) {
			glDisable(GL_CULL_FACE);
		} else {
			glEnable(GL_CULL_FACE);
		}
	}
	
	if (key == 'S') {
		
		GLint answer;
		glGetIntegerv(GL_SHADE_MODEL, &answer);
		
		if (answer == GL_FLAT) {
			glShadeModel(GL_SMOOTH);
		} else {
			glShadeModel(GL_FLAT);
		}
	}
	
	if (key == 'Q') {
		exit(0);
	}
    
    if (key == 'V') {
        app_struct.lock_camera_to_ground = !app_struct.lock_camera_to_ground;
    }
    
    if (app_struct.lock_camera_to_ground) {
        float height_at_location = height_for_coord(app_struct.terrain, at_create_point(app_struct.camera.location.x, app_struct.camera.location.z));
        app_struct.camera.location.y = POV_HEIGHT + height_at_location;
    }
}
