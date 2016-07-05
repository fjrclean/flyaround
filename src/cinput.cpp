//	cinput.cpp receives actions from server and converts client input to them.
//	Copyright (C) 2016  Finn Ryan

//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.

//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.

//	You should have received a copy of the GNU General Public License
//	along with this program.  If not, see <http://www.gnu.org/licenses/>.

//	The full license can be found in LICENSE.md .

/********************************************************/

#include "cinput.hpp"

#include <cstring>
#include <iostream>

/********************************************************/

cinput::cinput(fromplayer_t *output){
	m_output = output;
	memset((void *) output,0,sizeof(fromplayer_t));

	memset((void *) &m_mouseRotation,0,sizeof(vector3d));

	m_mouseX = 0;
	m_mouseY = 0;
}

int cinput::addAction(uint16_t num, char *name, int GLFW_defkey){
	if(m_inputmap.find(num) != m_inputmap.end()){
		return -1;
	}
	
	if(m_actionnames.find(num) != m_actionnames.end()){
		return -1;
	}
	
	/// @todo Add check for existing mappings in config files
	m_inputmap[num] = GLFW_defkey;
	m_actionnames[num] = std::string(name);
	
	return 0;
}

int cinput::mapAction(uint16_t num, int GLFW_key){
	m_inputmap[num] = GLFW_key;
	
	return 0;
}

int cinput::inputPressed(int GLFW_key){
	/// @todo Better way to find element than for loop?
	/// map::find can only find key, not element??
	for(int i=0; i<m_inputmap.size(); i++){
		if(m_inputmap[i] == GLFW_key){
			m_output->actionPress = i;
			/// @todo Setting actionPress should be bitwise
			/// to allow multiple presses in single fromplayer_t
			return 0;
		}
	}
	std::cerr << "input press: no mapping exists." << std::endl;
	return -1;
}

int cinput::inputReleased(int GLFW_key){
	/// @todo Better way to find element than for loop?
	/// map::find can only find key, not element??
	for(int i=0; i<m_inputmap.size(); i++){
		if(m_inputmap[i] == GLFW_key){
			m_output->actionRelease = i;
			/// @todo Setting actionRelease should be bitwise
			/// to allow multiple releases in single fromplayer_t
			return 0;
		}
	}
	std::cerr << "input release: no mapping exists." << std::endl;
	return -1;
}

int cinput::setMousePos(double mouseX, double mouseY){
	m_mouseX = mouseX;
	m_mouseY = mouseY;
	
	return 0;
}

int cinput::updateMouseRotation(double mouseX, double mouseY){
	double diffX = mouseX - m_mouseX; // Change in x cursor position
	double rotateY = m_mouseRotation.y; //m_output->camRotate.y;
	rotateY += diffX;
	m_mouseX = mouseX; // Update previous coordinate

	double diffY = mouseY - m_mouseY; //Change in y cursor position
	double rotateX = m_mouseRotation.x; //m_output->camRotate.x;
	rotateX += diffY;
	m_mouseY = mouseY; // Update previous coordinate
	
	if(rotateY >= 360){
		rotateY = rotateY - 360;
	}
	else if(rotateY < 0){
		rotateY = 360 + rotateY;
	}

	if(rotateX > 80){
		rotateX = 80;
	}
	else if(rotateX < -80){
		rotateX = -80;
	}

	m_mouseRotation.x = rotateX;
	m_mouseRotation.y = rotateY;
	m_output->camRotate.y = rotateY;
	m_output->camRotate.x = rotateX;

	return 0;
}


/********************************************************/
