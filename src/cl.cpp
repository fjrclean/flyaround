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
#include "cinput.hpp"
#include "entity.hpp"

void error_callback(int error, const char *description);
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void drawTri(struct vector3d vertA, struct vector3d vertB, struct vector3d vertC);
void lookAround(GLFWwindow *window);

camera playerCam;
glShader shaders("shaders/");
netinst net(30);
char netbuf[NET_SBUFSZ];

fromplayer_t output;
cinput input(&output);

int connsock;
fromplayer_t sbuf;

std::vector<entity> entities;
std::vector<entity> *players;

int main(int argc, char *argv[]){
	// networking setup
	/// @todo Allow server ip, port & player name to be set with program arguments
	std::string name;
	std::cout << "Enter player name: ";
	std::cin >> name;
	
	if((connsock = net.joinServer(9845,"127.0.0.1")) >= 0){
		if(net.appendBuffer(connsock,(void *) name.c_str(),name.size()) != 0)
			return -1;
		if(net.sendBuffer(connsock) != 0)
			return -1;
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
	//playerCam.setMousePos(xMouse,yMouse);
	input.setMousePos(xMouse,yMouse);
	
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

		if(net.checkStep() == 0){
		
		}
		/******* NETWORKING *******/
			// Get game state
		if(net.tryRead(connsock,(void *)&netbuf,sizeof(netbuf),NULL,0) > 0){
			std::cout << "state received" << std::endl;
			unsigned int index = 0;
			fromserver_t *from = (fromserver_t *) &netbuf;
			index += sizeof(fromserver_t);
			for(int i=0; i<from->entstateN; i++){
				index += sizeof(entstate_t);
			}
			actiondef_t *action;
			for(int i=0; i<from->actiondefN; i++){
				action = (actiondef_t *) &netbuf[index];
				input.addAction(action->id,"test action",action->GLFW_defkey);
				std::cout << "action added" << std::endl;
				index += sizeof(actiondef_t);
			}
		}
		else{
			//std::cerr << "No state received from server" << std::endl;
		}
		/**************************/

		
		

		glMatrixMode(GL_PROJECTION);
	        glLoadIdentity();
	        gluPerspective(45.0f, ratio, 0.1, 5000);
	        
		double xMouse, yMouse;
		glfwGetCursorPos (window, &xMouse, &yMouse);	
		memset((void *) &output,0,sizeof(fromplayer_t));
		input.updateMouseRotation(xMouse,yMouse);
		//playerCam.lookStep(xMouse,yMouse);
		playerCam.setRotation(output.camRotate.x,output.camRotate.y,0);
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


