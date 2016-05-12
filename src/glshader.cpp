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
	m_programID = 0;

}

glShader::glShader(std::string pathPrefix){
	m_pathPrefix = pathPrefix;

}

void glShader::addShader(char *fragSrcFile, char *vertSrcFile){

	std::string fragSrc = readTextFile(m_pathPrefix + fragSrcFile);  
	if(fragSrc != ""){
		std::cout << "fragment shader source loaded from file" << std::endl;
	}
	else{
		std::cout << "fragment shader source failed to load from file" << std::endl;
	}

	std::string vertSrc = readTextFile(m_pathPrefix + vertSrcFile);  
	if(vertSrc != ""){
		std::cout << "vertex shader source loaded from file" << std::endl;
	}
	else{
		std::cout << "vertex shader source failed to load from file" << std::endl;
	}

	if(vertSrc == "" || fragSrc == "")
		std::cout << "Aborting..." << std::endl;
	else{
		int numShaders = 2;
		GLuint shaderIDs[2];
		shaderIDs[0] = compileShader(fragSrc,GL_FRAGMENT_SHADER);
		shaderIDs[1] = compileShader(vertSrc,GL_VERTEX_SHADER);

		m_programID = createProgram(shaderIDs, numShaders);
	}
	
}

void glShader::enable(){
	glUseProgram(m_programID);
}

void glShader::disable(){
	glUseProgram(0);
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

	const char *cSrc = new char[source.size()]; 
	cSrc = source.c_str(); 

	return cSrc;
}

GLuint glShader::compileShader(std::string source, GLenum type){
	GLuint shaderHndl;

	//compile & add
	shaderHndl = glCreateShader(type);
	const char *shaderFileString = source.c_str();
	glShaderSource(shaderHndl,1,&shaderFileString,NULL);
	glCompileShader(shaderHndl);
	
	std::string shaderTypeName;
	switch(type){
		case GL_VERTEX_SHADER: shaderTypeName = "Vertex"; break;
		case GL_FRAGMENT_SHADER: shaderTypeName = "Fragment"; break;
	}

	GLint compiled;
	glGetShaderiv(shaderHndl, GL_COMPILE_STATUS, &compiled);
	if (compiled)
		std::cout << shaderTypeName << " shader compiled successfully: " << std::endl;
	else{
		std::cout << shaderTypeName << " shader compilation failed: " << std::endl;

		//get length of shader compile info log
		GLint infoLogLength;
		glGetShaderiv(shaderHndl, GL_INFO_LOG_LENGTH, &infoLogLength);

		//get string of shader compile info log
		GLchar *infoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shaderHndl, infoLogLength, NULL, infoLog);
		

		std::string errorLogContents = shaderTypeName;
			
		errorLogContents += " shader compile error: \n";
		errorLogContents += infoLog;
		
		std::cout << errorLogContents << std::endl;

		delete[] infoLog;
	
		return -1;
	}

	return shaderHndl;
}

std::string glShader::readTextFile(std::string filePath){
	std::ifstream textFile(filePath.c_str());
	std::stringstream fileContentsStream;

	if(textFile.is_open()){
		fileContentsStream << textFile.rdbuf();
		textFile.close();
	}
	else{
		return "";
	}

	return fileContentsStream.str();
}

unsigned long int glShader::fileLength(std::ifstream &file){
	unsigned long int length;
	file.seekg(0,std::ios_base::end);
	length = file.tellg();
	file.seekg(0,std::ios_base::beg);
	
	return length;

}

//used by load() to create a program and link the ShaderProgramIDs in the list
GLuint glShader::createProgram(const GLuint* shaderList, int numShaders){
	GLuint programID = glCreateProgram();

	//attach each shader id within shaderList into the program
	int shaderNum;
	for(shaderNum = 0; shaderNum<numShaders; shaderNum++){
		glAttachShader(programID, shaderList[shaderNum]);
	}

	glLinkProgram(programID);

	//check program linking status
	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if(linkStatus == GL_FALSE){
		//get length of linking info log
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

		//get linking info log string
		GLchar *infoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(programID, infoLogLength, NULL, infoLog);

		std::string errorLogContents = "Shader program linking error: \n";
		errorLogContents += infoLog;

		std::cout << infoLog << std::endl;

		delete[] infoLog;
	}
	
	glBindAttribLocation(programID, 0, "a_position");

	//detach each shader from the program (ShaderProgram now exist in program after linking)
	for(shaderNum = 0; shaderNum<numShaders; shaderNum++){
		glDetachShader(programID, shaderList[shaderNum]);
	}

	return programID;
}

/********************************************************/
