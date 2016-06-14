#include <cmath>
#include <iostream>
#include <cstdio>
#include <vector>
#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h> // POSIX only
#include <cstring>

#include "vector_math.hpp"
#include "camera.hpp"
#include "obj_model.hpp"
#include "glshader.hpp"
#include "netinst.hpp"
#include "game_data.hpp"

void error_callback(int error, const char *description);
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void drawTri(struct vector3d vertA, struct vector3d vertB, struct vector3d vertC);
void lookAround(GLFWwindow *window);

camera playerCam;
glShader shaders("shaders/");
netinst net;

int connsock;
fromplayer_t sbuf;

int main(int argc, char *argv[]){
	// networking setup
	/// @todo Allow server ip, port & player name to be set with program arguments
	std::string name;
	std::cout << "Enter player name: ";
	std::cin >> name;
	
	if((connsock = net.joinServer(9845,"127.0.0.1")) >= 0){
		if(net.appendBuffer(connsock,(void *) name.c_str(),name.size()) != 0)
			std::cout << "Response error" << std::endl;
		if(net.sendBuffer(connsock) != 0)
			std::cout << "Response error" << std::endl;
		std::cout << "Sent response" << std::endl;
	}

	objModel obj("square.obj");
	obj.setScale(0.05,0.05,0.05);
	
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
	glewInit();
	shaders.addShader("testfrag","testvert");

	float ratio;
	int width, height;
	while(!glfwWindowShouldClose(window)){
	
		//window management
		glfwGetFramebufferSize(window,&width,&height);
		ratio = width / (float) height;
		
		glViewport(0,0,width,height);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// networking
		
		

		glMatrixMode(GL_PROJECTION);
	        glLoadIdentity();
	        gluPerspective(45.0f, ratio, 0.1, 5000);
	        
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
	        
	        obj.drawObj(&drawTri);
	
		memset((void *) &sbuf,0,sizeof(sbuf));
	
		//window management
	        glfwSwapBuffers(window);
        	glfwPollEvents();
        	
        	playerCam.getRotation(&sbuf.camRotate.x,&sbuf.camRotate.y);
		net.appendBuffer(connsock,(void *) &sbuf,sizeof(sbuf));
		net.sendBuffer(connsock);


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
		sbuf.actionPress = GM_LEAVE;
		glfwSetWindowShouldClose(window, GL_TRUE);
		std::cout << "Leaving game" << std::endl;
	}
	else if(action == GLFW_PRESS){
		playerCam.inputPress(key);
		
		if(key == GLFW_KEY_W){
			sbuf.actionPress = MV_FORWARD;
		}
	}
	else if(action == GLFW_RELEASE){
		playerCam.inputRelease(key);
	
		if(key == GLFW_KEY_W){
			sbuf.actionRelease = MV_FORWARD;
		}

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


