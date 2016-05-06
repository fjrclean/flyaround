//glshader.hpp
//Part of project game_engine/flyaround
//Handles the loading of glsl shaders from text file,
//and keeping track of the shaders created from them.

#ifndef GLSHADER_HPP
#define GLSHADER_HPP

/********************************************************/

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <map>

/*********************************************************/

		/**
		*@brief
		*
		*/
class glShader{

	public:
		///takes the file shader source is stored in, relative to pwd
	glShader(char *pathPrefix);
	addShader(char *fragSrcFile, char *vertSrcFile);
	private:
		///Loads the ASCII text of fileName and returns it as a char *
	char * loadSource(fileName);
		/**
		*@brief compiles a fragment shader, after checking it has not
		*already been compiled with m_fragSrc.
		*Returns object identifier of shader
		*/
	GLUint compileFrag(char *source);
		
	GLUint compileVert(
	attach(
	
		///map compiled frag shader source file name to it's
		///GLUint object identifier.
		///Used to check if source has already been compiled
		///I presume compiled objects remain after they have been linked with 
	std::map<char *, GLUint> m_fragSrc;
		///map compuled vertex shader source file name to it's
		///GLUint object identifier.
	std::map<char *, GLUint> m_vertSrc;
	
		///Vector of all shader programs
	std::vector<GLUint> m_shaderPrograms;
};

/*********************************************************/

#endif
