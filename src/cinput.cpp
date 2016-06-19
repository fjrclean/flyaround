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

/********************************************************/

cinput::cinput(fromplayer_t *output, double mouseX, double mouseY){
	m_output = output;
	m_mouseX = mouseX;
	m_mouseY = mouseY;
}

int cinput::addAction(uint16_t num, char *name, int GLFW_defkey){
	if(m_inputmap.find() != m_inputmap.end()){
		return -1;
	}
	
	if(m_actionnames.find() != m_actionnames.end()){
		return -1;
	}
	
	/// @todo Add check for existing mappings in config files
	m_inputmap[num] = GLFW_defkey;
	m_actionnames[num] = std::string(name);
	
	return 0;
}

int cinput::mapAction(uint16_t num, int GLFW_key){
	
}

/********************************************************/
