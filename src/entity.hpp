//	entity.hpp Represents a generic physical world object.
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

#ifndef ENTITY_HPP
#define ENTITY_HPP

/********************************************************/

#include <vector>
//#include <glm/mat3x3.hpp>
//#include <glm/vec3.hpp>
//#include <glm/gtc/matrix_tranform.hpp>

#include "obj_model.hpp"

/// @todo change to proper mathematics library for vectors. GNU Scientific library?
#include "vector_math.hpp"

/*********************************************************/

		/**
		* @brief
		*
		*/
class entity{

	public:
	entity();
	
	int rotate(double x, double y, double z);
	
	int setRotate(double x, double y, double z);
	
	int getForwardVec(vector3d *);
	
	int getworldPos(vector3d *);
	
	int updateModel(); // temporary.
	
	objModel & getModel(); // temporary.
	
	private:
	int updateAxes();
	
	//vector3d m_rotation;
	
	vector3d m_worldPos;
	
	vector3d m_rotation;
	
	vector3d m_localX;
	vector3d m_localY;
	vector3d m_localZ;

	objModel *m_model; // temporary
};

/*********************************************************/

#endif
