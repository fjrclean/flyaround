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
	void inputPress(int action);
	void inputRelease(int action);
		/**
		*@brief returns the eye coordinates of where the camera should be looking
		*/
	void lookStep(double xMouse, double yMouse);
	struct vector3d getLookDir(void);
	struct vector3d getWorldPos(void);
	void setMousePos(double xMouse, double yMouse);

	void setRotation(double x, double y, double z);
	void getRotation(double *x, double *y);


	private:

	void updateLookDir(void);
		///update m_leftDir based on m_yRotate
	void updateLeftDir(void);
	void updateRightDir(void);
	void updatePosition();
	
	
	vector3d getPosition();

		///positions of the camera within the world
		///used to determine how to move the world around the render viewport.
	struct vector3d m_worldPos;
		///where the camera is looking, this is not world coordinates, 
		///but opengl where camera is always position 0,0,0
		///In unit vector format

		///The camera's current rotation on the global Y axis
	double m_yRotate;
		///The camera's current rotation on the global X axis;
	double m_xRotate;

	struct vector3d m_lookDir;
	struct vector3d m_leftDir;
	struct vector3d m_rightDir;
		///the previous* position of mouse cursor
	double m_xMouse;
	double m_yMouse;
		///Camera movement speed
	double m_speed;
	
	vecMath vMath;
	
	//current movement states
	bool m_isMovingRight;
	bool m_isMovingLeft;
	bool m_isMovingForward;
	bool m_isMovingBackward;
	bool m_isMovingPosY;
	bool m_isMovingNegY;

	int cameraForward = GLFW_KEY_W;
	int cameraBackward = GLFW_KEY_S;
	int cameraLeft = GLFW_KEY_A;
	int cameraRight = GLFW_KEY_D;
	int cameraDown = GLFW_KEY_LEFT_CONTROL;
	int cameraUp = GLFW_KEY_SPACE;

};

/*********************************************************/

#endif
