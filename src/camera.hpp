//camera.hpp
//Part of project game_engine/flyaround
//Class to represent the camera object within the wordl

#ifndef CAMERA_HPP
#define CAMERA_HPP

/********************************************************/

#include <GLFW/glfw3.h>
#include "vector_math.hpp"

/*********************************************************/

		/**
		*@brief
		*
		*/
class camera{

	public:
	camera();
	void input(int action);
		/**
		*@brief returns the eye coordinates of where the camera should be looking
		*/
	void lookStep(double xMouse, double yMouse);
	struct vector3d getLookDir(void);
	struct vector3d getWorldPos(void);
	void setMousePos(double xMouse, double yMouse);
	private:
	
		///update m_leftDir based on m_yRotate
	void updateLeftDir(void);
	void updateRightDir(void);
	
		///positions of the camera within the world
		///used to determine how to move the world around the render viewport.
	struct vector3d m_worldPos;
		///where the camera is looking, this is not world coordinates, 
		///but opengl where camera is always position 0,0,0
		///In unit vector format
	struct vector3d m_lookDir;
	struct vector3d m_leftDir;
	struct vector3d m_rightDir;
		///the previous* position of mouse cursor
	double m_xMouse;
	double m_yMouse;
		///The camera's current rotation on the global Y axis
	double m_yRotate;
		///The camera's current rotation on the global X axis;
	double m_xRotate;
		///Camera movement speed
	double m_speed;
	
	vecMath vMath;
	
	int cameraForward = GLFW_KEY_W;
	int cameraBackward = GLFW_KEY_S;
	int cameraLeft = GLFW_KEY_A;
	int cameraRight = GLFW_KEY_D;
	int cameraDown = GLFW_KEY_LEFT_CONTROL;
	int cameraUp = GLFW_KEY_SPACE;

};

/*********************************************************/

#endif
