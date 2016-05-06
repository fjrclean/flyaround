//glshader.cpp

/********************************************************/

#include "glshader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
/********************************************************/

glShader::glShader(){
	m_pathPrefix = "";
}

glShader::glShader(std::string pathPrefix){
	m_pathPrefix = pathPrefix;
}

void glShader::addShader(char *fragSrcFile, char *vertSrcFile){
	char const *fragSrc = loadSource(fragSrcFile);
	if(fragSrc != NULL)
		std::cout << "fragment shader source loaded: " << fragSrc << std::endl;

	char const *vertSrc = loadSource(vertSrcFile);
	if(vertSrc != NULL)
		std::cout << "vertex shader source loaded: " << vertSrc << std::endl;

	if(vertSrc == NULL || fragSrc == NULL)
		std::cout << "Aborting..." << std::endl;
}


const char * glShader::loadSource(char *fileName){
	std::ifstream src;
	std::string fullPath = m_pathPrefix + fileName;
	src.open(fullPath.c_str());
	if(!src){
		std::cout << "Error: file '" << fullPath << "' does not exist." << std::endl;
		return NULL;
	}
	
	//add error check for file size
	
	if(!src.good()){
		std::cout << "Error: file '" << fullPath << "' is bad." << std::endl;
		return NULL;
	}
	
	std::stringstream ss;
	ss << src.rdbuf();
	src.close();
	
	std::string source = ss.str();
	const char *cSrc = source.c_str();
	return cSrc;
}

GLuint glShader::compileFrag(char *fileName, char *source){
	if(m_fragObj.find(fileName) == m_fragObj.end()){// no object for source exists
		//compile & add
		//m_fragObj[fileName] =
	}
	
	//test 
	//return  
}


/********************************************************/
