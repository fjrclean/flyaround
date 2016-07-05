//	entity.cpp Represents a generic physical world object.
//	Part of the flyaround game engine project.
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

#include "entity.hpp"

#include <cstring>

/********************************************************/

entity::entity(){
	m_localX.x = 1;
	m_localX.y = 0;
	m_localX.z = 0;
	
	m_localY.x = 0;
	m_localY.y = 1;
	m_localY.z = 0;
	
	m_localZ.x = 0;
	m_localZ.y = 0;
	m_localZ.z = 1;
	
	memset((void *) &m_worldPos,0,sizeof(vector3d));
	memset((void *) &m_rotation,0,sizeof(vector3d));
	
}

int entity::rotate(double x, double y, double z){
	m_rotation.x += x;
	m_rotation.y += y;
	m_rotation.z += z;

	/// @todo change to proper matrix rotation using glm.
	/// Using cos, sin, tan method from obsolete camera class for now,
	/// with no z axis rotation. Can this be added?
	
	/*m_localZ.x = cx + (r * cos(m_yRotate * M_PI / 180.0));
	m_localZ.z = cz + (r * sin(m_yRotate * M_PI / 180.0));
	
	forwardVec.y = cy + (r * tan(m_xRotate * M_PI / 180.0));
	
	m_lookDir = vMath.getUnit(&forwardVec);*/

	return 0;
}

int entity::setRotate(double x, double y, double z){
	m_rotation.x = 0;
	m_rotation.y = 0;
	m_rotation.z = 0;

	rotate(x,y,z);

	return 0;
}

int entity::updateAxes(){
	double cx = 0;
	double cz = 0;
	double cy = 0;
	double r = 1;
	
	//m_localX = 
}
/********************************************************/
