//	cinput.hpp receives actions from server and converts client input to them.
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

#ifndef CLASS_HPP
#define CLASS_HPP

/********************************************************/

#include <map>

#include <game_data.hpp>

/*********************************************************/

		/**
		* @brief
		*
		*/
class cinput{

	public:
		/**
		* @brief default constructor.
		*
		* @param output sets where action & mouse data is stored once
		* converted, eg from input to action.
		* @param mouseX is the starting GLFW mouse x coordinate.
		* @param mouseY is the starting GLFW mouse y coordinate.
		*/
	cinput(fromplayer_t output, double mouseX, double mouseY);

		/**
		* @brief Adds a player action for this game.
		*
		* @param name is used for human readable mapping
		* of input to the action (eg in options menu).
		* @param num is to identify the action programmatically,
		* or send over network.
		* @param GLFW_defkey is the default input this action
		* is mapped to unless a mapping already exists in a
		* config file.
		*
		* @return 0 on success; -1 on failure, check log;
		*/
	int addAction(uint16_t num, char *name, int GLFW_defkey);
	
		/**
		* @brief Maps GLFW input key to an action.
		*
		* @param num is to identify the action programmatically,
		* or send over network.
		* @param GLFW_key is the input to map this action
		* to.
		*
		* @return 0 on success; -1 on failure (eg action is already
		* mapped to input), check log;
		*
		* @todo Allow multiple inputs to be mapped to single action.
		*/
	int mapAction(uint16_t num, int GLFW_key);
	
		/**
		* @brief Adds key's association action press to the output.
		*
		* @param GLFW_key is used to look for associated action.
		*
		* @return 0 on success; -1 on failure (eg no mapping exists),
		* check log;
		*/
	int inputPressed(int GLFW_key);

		/**
		* @brief Adds key's association action release to the output.
		*
		* @param GLFW_key is used to look for associated action.
		*
		* @return 0 on success; -1 on failure (eg no mapping exists),
		* check log;
		*/
	int inputReleased(int GLFW_key);
	
		/**
		* @brief Uses current & previous mouse coordinates to determine
		* rotation around imaginary mouse axes.
		*
		* Can be used for the rotation of objects such as the camera, or
		* player character, etc.
		*
		* @param mouseX is the current GLFW mouse x coordinate.
		* @param mouseY is the current GLFW mouse y coordinate.
		*
		* @return 0 for success; -1 on failure, check log;
		*/
	int updateMouseRotation(double mouseX, double mouseY);
	
	private:
	double m_mouseX;
	double m_mouseY;
	fromplayer_t *m_output;
	
	std::map<uint16_t,int> m_inputmap;
	std::map<uint16_t,std::string> m_actionnames;
};

/// @todo add insertion operator for ini-like file defining action-input mappings.

/*********************************************************/

#endif
