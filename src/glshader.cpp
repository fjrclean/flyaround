//glshader.cpp

/********************************************************/

#include "glshader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <GL/glew.h>

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
	else{
		addFrag(fragSrcFile,fragSrc);
		addVert(vertSrcFile,vertSrc);
		//then link
	}
	
}


const char * glShader::loadSource(char *fileName){
	std::ifstream src;
	std::string fullPath = m_pathPrefix + fileName;
	src.open(fullPath.c_str());
	if(!src){
		std::cout << "Error: file '" << fullPath << "' does not exist." << std::endl;
		return NULL;
	}
	
	if(!src.good()){
		std::cout << "Error: file '" << fullPath << "' is bad." << std::endl;
		return NULL;
	}

	std::stringstream ss;
	ss << src.rdbuf();
	src.close();
	
	std::string source = ss.str();
	
	if(source.size() <= 0){
		std::cout << "Error: file '" << fullPath << "' is empty." << std::endl;
		return NULL;
	}
	
	source.append("\0");
	const char *cSrc = new char[source.size()]; 
	cSrc = source.c_str(); 

	return cSrc;
}

GLuint glShader::addFrag(char *fileNameC, const char *source){
	int size;
	GLuint fragHndl;
	std::string fileName = fileNameC;
	if(m_fragObj.find(fileName) == m_fragObj.end()){// no object for source exists
		//compile & add
		m_fragObj[fileName] = glCreateShader(GL_FRAGMENT_SHADER);
		fragHndl = m_fragObj[fileName];
		size = strlen(source);
		glShaderSource(fragHndl,1,&source,&size);
		glCompileShader(fragHndl);
		
		GLint compiled;
		glGetShaderiv(fragHndl, GL_COMPILE_STATUS, &compiled);
		if (compiled)
			std::cout << "frag shader compiled successfully: " << m_pathPrefix << fileName << std::endl;
		else{
			std::cout << "error: frag shader compiled failed: " << m_pathPrefix << fileName << std::endl;
			return -1;
		}
	}
	
	return m_fragObj[fileName];
}

GLuint glShader::addVert(char *fileNameC, const char *source){
	int size;
	GLuint fragHndl;
	std::string fileName = fileNameC;
	if(m_vertObj.find(fileName) == m_vertObj.end()){// no object for source exists
		//compile & add
		m_vertObj[fileName] = glCreateShader(GL_FRAGMENT_SHADER);
		fragHndl = m_vertObj[fileName];
		size = strlen(source);
		glShaderSource(fragHndl,1,&source,&size);
		glCompileShader(fragHndl);
		
		GLint compiled;
		glGetShaderiv(fragHndl, GL_COMPILE_STATUS, &compiled);
		if (compiled)
			std::cout << "vert shader compiled successfully: " << m_pathPrefix << fileName << std::endl;
		else{
			std::cout << "error: vert shader compiled failed: " << m_pathPrefix << fileName << std::endl;
			return -1;
		}
	}
	
	return m_vertObj[fileName];
}

unsigned long int glShader::fileLength(std::ifstream &file){
	unsigned long int length;
	file.seekg(0,std::ios_base::end);
	length = file.tellg();
	file.seekg(0,std::ios_base::beg);
	
	return length;

}

/********************************************************/
