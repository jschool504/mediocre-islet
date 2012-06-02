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

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>

int main(int argc, char * argv[]) {
	
	//app_struct.glut = at_create_glut("Terrain", ATSize512, draw, reshape, idle, argc, argv);
	//app_struct.glut.key_down_function = key_pressed;
	
	app_struct.camera = at_create_camera(at_create_vertex(TERRAIN_SIZE / 2, 100, TERRAIN_SIZE / 2), at_create_rotation(0, 0, 0));
	//app_struct.camera = at_create_camera(at_create_vertex(0, 0, 4), at_create_rotation(0, 0, 0));
	
	app_struct.axis[0] = at_create_axis(ATVectorX, 1000, ATRedColor);
	app_struct.axis[1] = at_create_axis(ATVectorY, 1000, ATGreenColor);
	app_struct.axis[2] = at_create_axis(ATVectorZ, 1000, ATBlueColor);
	
	app_struct.gl_inited = false;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Terrain C");
	
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(key_pressed);
	
	glutMainLoop();
	
    return 0;
}

void init_gl() {
	
	glClearColor(0, 0, 0, 0.0);
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
		
		app_struct.view_range = VIEW_RANGE;
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
	draw_terrain(&app_struct.terrain, at_convert_vertex(app_struct.camera.location));
	
	clock_t endTime = clock();
	float dTime = (1.0 / difftime(endTime, startTime)) * (CLOCKS_PER_SEC * 10);
	
	char *output = malloc(sizeof(char) * 100);
	sprintf(output, "FPS: %0.1f View Range: %d\n", dTime, app_struct.view_range);
	at_draw_string(0, 0, output);
	free(output);
	
	at_unset_camera();
	
	glutSwapBuffers();
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
		app_struct.view_range+=16;
	}
	
	if (key == '_') {
		app_struct.view_range-=16;
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
	
}