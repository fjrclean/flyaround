#include <cmath>
#include <iostream>
#include <cstdio>
#include <vector>
#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vector_math.hpp"
#include "camera.hpp"
#include "obj_model.hpp"
#include "glshader.hpp"
//#include "logic.h"
//#include "physics.h"
//#include "drawing.h"

void error_callback(int error, const char *description);
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void drawTri(struct vector3d vertA, struct vector3d vertB, struct vector3d vertC);
void lookAround(GLFWwindow *window);

camera playerCam;
glShader shaders("shaders/");

int main(int argc, char *argv[]){
	
	objModel obj("square.obj");
	
	//initialization
	if(!glfwInit()){
		std::cerr << "err: glfw could not initialize.\n";
		return -1;
	}
	
	glfwSetErrorCallback(error_callback);
	
	GLFWwindow *window = glfwCreateWindow(640,480,"Flyaround",NULL,NULL);
	if(!window){
		glfwTerminate();
		std::cerr << "err: glfw window could not be created.\n";
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	double xMouse, yMouse;
	glfwGetCursorPos (window, &xMouse, &yMouse);
	playerCam.setMousePos(xMouse,yMouse);
	
	//glShader test
	shaders.addShader("testfrag","testvert");

	float ratio;
	int width, height;
	while(!glfwWindowShouldClose(window)){
	
		//window management
		glfwGetFramebufferSize(window,&width,&height);
		ratio = width / (float) height;
		
		glViewport(0,0,width,height);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//do logic
	
		//do physics
	
		//do drawing

		glMatrixMode(GL_PROJECTION);
	        glLoadIdentity();
	        //glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		//glFrustum (-ratio, ratio, 0, height, 1.5f, 20.0);
	        gluPerspective(45.0f, ratio, 0.1,1000);
	        
		double xMouse, yMouse;
		glfwGetCursorPos (window, &xMouse, &yMouse);	
		playerCam.lookStep(xMouse,yMouse);
		struct vector3d lookDir = playerCam.getLookDir();
		gluLookAt(
			lookDir.x,lookDir.y,lookDir.z,
			0,0,0,
			0,1,0);

	        
	        glMatrixMode(GL_MODELVIEW);
	        glLoadIdentity();
	        
	        struct vector3d worldPos = playerCam.getWorldPos();
        	glTranslatef(worldPos.x,worldPos.y,worldPos.z);
        	//glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        	/*glBegin(GL_TRIANGLES);
        	glColor3f(1.f, 0.f, 0.f);
        	glVertex3f(-0.6f, -0.4f, -5.f);
        	glColor3f(0.f, 1.f, 0.f);
        	glVertex3f(0.6f, -0.4f, -5.f);
        	glColor3f(0.f, 0.f, 1.f);
        	glVertex3f(0.f, 0.6f, -5.f);
	        glEnd();*/
	        
	        obj.drawObj(&drawTri);

	
		//std::cout << "moveZ:" << moveZ << std::endl;
	
		//window management
	        glfwSwapBuffers(window);
        	glfwPollEvents();

	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void error_callback(int error, const char *description){
	std::fputs(description, stderr);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if(action == GLFW_PRESS){
		playerCam.inputPress(key);
	}
	else if(action == GLFW_RELEASE){
		playerCam.inputRelease(key);
	}
}

void drawTri(struct vector3d vertA, struct vector3d vertB, struct vector3d vertC){
       	glBegin(GL_TRIANGLES);
       	glColor3f(1.f, 0.f, 0.f);
       	glVertex3f(vertA.x, vertA.y, vertA.z);
       	glColor3f(0.f, 1.f, 0.f);
       	glVertex3f(vertB.x, vertB.y, vertB.z);
       	glColor3f(0.f, 0.f, 1.f);
       	glVertex3f(vertC.x, vertC.y, vertC.z);
        glEnd();

}


