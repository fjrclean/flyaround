// luaHandle.hpp
// Part of project game_engine/flyaround

#ifndef LUA_HANDLE_HPP
#define LUA_HANDLE_HPP

/********************************************************/

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

/*********************************************************/

		/**
		* @brief Encapsulates the Lua API for easy use with
		* objects and automatic error checking.
		*
		*/
class luaHandle{

	public:
	
		/**
		* @brief Constructor creates a Lua state
		*/
	luaHandle(
	
		/**
		* @brief Makes a CPP function callable from
		* Lua state.
		*
		* 
	int addCPPFunction(
	private:

};

/*********************************************************/

#endif
