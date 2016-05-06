//obj_model.hpp
//Part of project game_engine/flyaround
//Provides a wrapper for tinyobjloader*,storing the data of an .obj file
//https://github.com/syoyo/tinyobjloader

#ifndef OBJ_MODEL_HPP
#define OBJ_MODEL_HPP

/********************************************************/

#include <tiny_obj_loader.h>
#include <vector>
#include "vector_math.hpp"

/*********************************************************/

struct texture{
	char *fileName;
	void *mem;
};

struct materialMem{
	void *ambient;
	void *diffuse;
	void *spec;
	void *specHighlight;
};

		/**
		*@brief
		*
		*/
class objModel{

	public:
	objModel(std::string objFile);
		///takes file name of texture to add,
		///adds if not already present,
		///returns pointer to texture in memory
	void test(std::vector<tinyobj::shape_t> &shapes, std::vector<tinyobj::material_t> &materials);
		///takes a pointer to a function which draws a triangle
		///will parse each triangle of this object to that function to be drawn
	void drawObj(void (*drawTri)(struct vector3d, struct vector3d, struct vector3d));
	private:
	void * addTexture(char * fileName);

	static std::vector<struct texture> m_textures;
	std::vector<tinyobj::material_t> m_materials;
	std::vector<struct materialMem> m_materialsMem;
	std::vector<tinyobj::shape_t> m_shapes;

};

/*********************************************************/

#endif
