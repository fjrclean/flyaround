//camera.cpp

/********************************************************/

#include "camera.hpp"
#include <iostream>

/********************************************************/

camera::camera(){
	m_worldPos.x = 0;
	m_worldPos.y = 0;
	m_worldPos.z = 0;
	
	m_lookDir.x = 0;
	m_lookDir.y = 0;
	m_lookDir.z = 1;
	updateLeftDir();
	updateRightDir();
	
	m_xRotate = 0;
	m_yRotate = 0;
	
	m_speed = 10.1;


}

void camera::lookStep(double xMouse, double yMouse){
	double diffX = xMouse - m_xMouse; //Change in x cursor position
	if(xMouse != m_xMouse)
		m_yRotate += diffX;
		
	m_xMouse = xMouse;

	double diffY = yMouse - m_yMouse; //Change in y cursor position
	if(yMouse != m_yMouse)
		m_xRotate += diffY;
	if(m_xRotate > 135)
		m_xRotate = 135;
	else if(m_xRotate < -135)
		m_xRotate = -135;
		
	m_yMouse = yMouse;
	
	std::cout << "rotateX: " << m_xRotate << std::endl;
	
	double cx = 0;
	double cz = 0;
	double cy = 0;
	double r = 1;

	struct vector3d forwardVec;

	forwardVec.x = cx + (r * cos(m_yRotate * M_PI / 180.0));
	forwardVec.z = cz + (r * sin(m_yRotate * M_PI / 180.0));
	
	forwardVec.y = cy + (r * cos(m_xRotate * M_PI / 180.0));
	//forwardVec.z += cz + (r * sin(rotateX * M_PI / 180.0));
	
	m_lookDir = vMath.getUnit(&forwardVec);
	
	updateLeftDir();
	updateRightDir();
}

void camera::updateLeftDir(void){
	double cx = 0;
	double cz = 0;
	double cy = 0;
	double r = 1;

	double yRotate = m_yRotate - 90;
	struct vector3d leftDir;

	leftDir.x = cx + (r * cos(yRotate * M_PI / 180.0));
	leftDir.z = cz + (r * sin(yRotate * M_PI / 180.0));
	leftDir.y = 0;
	
	m_leftDir = vMath.getUnit(&leftDir);

}

void camera::updateRightDir(void){
	double cx = 0;
	double cz = 0;
	double cy = 0;
	double r = 1;

	double yRotate = m_yRotate + 90;
	struct vector3d rightDir;

	rightDir.x = cx + (r * cos(yRotate * M_PI / 180.0));
	rightDir.z = cz + (r * sin(yRotate * M_PI / 180.0));
	rightDir.y = 0;
	
	m_rightDir = vMath.getUnit(&rightDir);

}

struct vector3d camera::getLookDir(void){
	return m_lookDir;
}

struct vector3d camera::getWorldPos(void){
	return m_worldPos;
}

void camera::setMousePos(double xMouse, double yMouse){
	m_xMouse = xMouse;
	m_yMouse = yMouse;
}

void camera::input(int key){
	if(key == cameraLeft){
		//m_worldPos.x += 0.1;
		m_worldPos.x += m_leftDir.x * m_speed;
		m_worldPos.y += m_leftDir.y * m_speed;
		m_worldPos.z += m_leftDir.z * m_speed;

	}
	else if(key == cameraRight){
		//m_worldPos.x -= 0.1;
		m_worldPos.x += m_rightDir.x * m_speed;
		m_worldPos.y += m_rightDir.y * m_speed;
		m_worldPos.z += m_rightDir.z * m_speed;

	}
	else if(key == cameraForward){
		//moveZ += 0.1;
		m_worldPos.x += m_lookDir.x * m_speed;
		m_worldPos.y += m_lookDir.y * m_speed;
		m_worldPos.z += m_lookDir.z * m_speed;
	}
	else if(key == cameraBackward){
		//moveZ -= 0.1;
		m_worldPos.x -= m_lookDir.x * m_speed;
		m_worldPos.y -= m_lookDir.y * m_speed;
		m_worldPos.z -= m_lookDir.z * m_speed;

	}
	else if(key == cameraUp){
		m_worldPos.y -= m_speed;
	}
	else if(key == cameraDown){
		m_worldPos.y += m_speed;
	}
	/*else if(key == GLFW_KEY_LEFT){
		rotateY += 5;
	}
	else if(key == GLFW_KEY_RIGHT){
		rotateY -= 5;
	}*/

}


/********************************************************/
