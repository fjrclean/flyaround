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
	
	m_speed = 0.1;

	m_isMovingRight = false;
	m_isMovingLeft = false;
	m_isMovingForward = false;
	m_isMovingBackward = false;
	m_isMovingPosY = false;
	m_isMovingNegY = false;


}

void camera::lookStep(double xMouse, double yMouse){
	double diffX = xMouse - m_xMouse; //Change in x cursor position
	if(xMouse != m_xMouse)
		m_yRotate += diffX;
		
	m_xMouse = xMouse;

	double diffY = yMouse - m_yMouse; //Change in y cursor position
	if(yMouse != m_yMouse)
		m_xRotate += diffY;
	
		
	m_yMouse = yMouse;
	
	if(m_yRotate >= 360){
		m_yRotate = m_yRotate - 360;
	}
	else if(m_yRotate < 0){
		m_yRotate = 360 + m_yRotate;
	}

	if(m_xRotate > 80){
		m_xRotate = 80;
	}
	else if(m_xRotate < -80){
		m_xRotate = -80;
	}

	updateLookDir();
	updateLeftDir();
	updateRightDir();
}

void camera::updateLookDir(void){
	double cx = 0;
	double cz = 0;
	double cy = 0;
	double r = 1;

	struct vector3d forwardVec;

	forwardVec.x = cx + (r * cos(m_yRotate * M_PI / 180.0));
	forwardVec.z = cz + (r * sin(m_yRotate * M_PI / 180.0));
	
	forwardVec.y = cy + (r * tan(m_xRotate * M_PI / 180.0));
	
	m_lookDir = vMath.getUnit(&forwardVec);

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
	updatePosition();
	return m_worldPos;
}

void camera::setMousePos(double xMouse, double yMouse){
	m_xMouse = xMouse;
	m_yMouse = yMouse;
}

void camera::updatePosition(){
	if(m_isMovingLeft){
		//m_worldPos.x += 0.1;
		m_worldPos.x += m_leftDir.x * m_speed;
		m_worldPos.y += m_leftDir.y * m_speed;
		m_worldPos.z += m_leftDir.z * m_speed;

	}
	if(m_isMovingRight){
		//m_worldPos.x -= 0.1;
		m_worldPos.x += m_rightDir.x * m_speed;
		m_worldPos.y += m_rightDir.y * m_speed;
		m_worldPos.z += m_rightDir.z * m_speed;

	}
	if(m_isMovingForward){
		//moveZ += 0.1;
		m_worldPos.x += m_lookDir.x * m_speed;
		m_worldPos.y += m_lookDir.y * m_speed;
		m_worldPos.z += m_lookDir.z * m_speed;
	}
	if(m_isMovingBackward){
		//moveZ -= 0.1;
		m_worldPos.x -= m_lookDir.x * m_speed;
		m_worldPos.y -= m_lookDir.y * m_speed;
		m_worldPos.z -= m_lookDir.z * m_speed;

	}
	if(m_isMovingPosY){
		m_worldPos.y -= m_speed;
	}
	if(m_isMovingNegY){
		m_worldPos.y += m_speed;
	}
	/*else if(key == GLFW_KEY_LEFT){
		rotateY += 5;
	}
	else if(key == GLFW_KEY_RIGHT){
		rotateY -= 5;
	}*/

}

void camera::inputPress(int key){
	if(key == cameraLeft){
		m_isMovingLeft = true;
	}
	else if(key == cameraRight){
		m_isMovingRight = true;
	}
	else if(key == cameraForward){
		m_isMovingForward = true;
	}
	else if(key == cameraBackward){
		m_isMovingBackward = true;
	}
	else if(key == cameraUp){
		m_isMovingPosY = true;
	}
	else if(key == cameraDown){
		m_isMovingNegY = true;
	}
}

void camera::inputRelease(int key){
	if(key == cameraLeft){
		m_isMovingLeft = false;
	}
	else if(key == cameraRight){
		m_isMovingRight = false;
	}
	else if(key == cameraForward){
		m_isMovingForward = false;
	}
	else if(key == cameraBackward){
		m_isMovingBackward = false;
	}
	else if(key == cameraUp){
		m_isMovingPosY = false;
	}
	else if(key == cameraDown){
		m_isMovingNegY = false;
	}
}


/********************************************************/
