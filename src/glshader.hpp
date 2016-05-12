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
#include <string>
#include <fstream>

/*********************************************************/

		/**
		*@brief
		*
		*/
class glShader{

	public:
	glShader();
		///takes the file shader source is stored in, relative to pwd
	glShader(std::string pathPrefix);
	void addShader(char *fragSrcFile, char *vertSrcFile);
	private:
		///Loads the ASCII text of fileName and returns it as a char *
	const char * loadSource(char *fileName);
		/**
		*@brief creates a fragment shader, after checking it has not
		*already been created in m_fragObj.
		*@return object identifier of shader,
		*-1 if error
		*/
	GLuint compileShader(char *fileName, const char *source, GLuint type);
		///Check if shader was compiled successfully
	void compileErrors(GLuint object);
		///should be moved to general useful functions file
	unsigned long int fileLength(std::ifstream &file);
	
		///map compiled frag shader source file name to it's
		///GLUint object identifier.
		///Used to check if source has already been compiled
		///I presume compiled objects remain after they have been linked with 
	std::map<std::string, GLuint> m_fragObj;
		///map compuled vertex shader source file name to it's
		///GLUint object identifier.
	std::map<std::string, GLuint> m_vertObj;
	
		///Vector of all shader programs
	std::vector<GLuint> m_shaderPrograms;
		///prefix prepended to all shader source file names
	std::string m_pathPrefix;
};

/*********************************************************/

#endif
