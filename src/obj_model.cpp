//obj_model.cpp

/********************************************************/

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "obj_model.hpp"
#include <iostream>

/********************************************************/

objModel::objModel(std::string objFile){
	std::string objPath = "objmodels/";
	objPath.append(objFile);
	
	std::string err;
	bool ret = tinyobj::LoadObj(m_shapes, m_materials, err, objPath.c_str(), "objmodels/");
	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}
	  
	if (!ret){
		//delete self? 
	}
	
	test(m_shapes,m_materials);
	
	//check image files used by materials
	//add them to m_textures if not already present
	//store pointer to texture memory

}

void objModel::drawObj(void (*drawTri)(struct vector3d, struct vector3d, struct vector3d)){
       	struct vector3d vert[3]; //contains the 3 vectors representing the 3 vertices
       	int iVert[3]; //contains the indexes of the 3 vertices used by triangle
       	
	for (size_t i = 0; i < m_shapes.size(); i++) {
        	assert((m_shapes[i].mesh.indices.size() % 3) == 0);
        	for (size_t f = 0; f < m_shapes[i].mesh.indices.size() / 3; f++) {
              		//f is triangle index of current shape of this object
              		iVert[0] = m_shapes[i].mesh.indices[3*f+0];
              		iVert[1] = m_shapes[i].mesh.indices[3*f+1];
              		iVert[2] = m_shapes[i].mesh.indices[3*f+2];
              		
              		for(size_t i1 = 0; i1 < 3; i1++){
				vert[i1].x = m_shapes[i].mesh.positions[3*iVert[i1]+0];
      				vert[i1].y = m_shapes[i].mesh.positions[3*iVert[i1]+1];
            			vert[i1].z = m_shapes[i].mesh.positions[3*iVert[i1]+2];
            		}
		drawTri(vert[0],vert[1],vert[2]);

                }
	}
       	
}


void objModel::test(std::vector<tinyobj::shape_t> &shapes, std::vector<tinyobj::material_t> &materials){
std::cout << "# of shapes    : " << shapes.size() << std::endl;
std::cout << "# of materials : " << materials.size() << std::endl;

for (size_t i = 0; i < shapes.size(); i++) {
  printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
    printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
      printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
        assert((shapes[i].mesh.indices.size() % 3) == 0);
          for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
              printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3*f+0], shapes[i].mesh.indices[3*f+1], shapes[i].mesh.indices[3*f+2], shapes[i].mesh.material_ids[f]);
                }
                
                  printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
                    assert((shapes[i].mesh.positions.size() % 3) == 0);
                      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
                          printf("  v[%ld] = (%f, %f, %f)\n", v,
                                shapes[i].mesh.positions[3*v+0],
                                      shapes[i].mesh.positions[3*v+1],
                                            shapes[i].mesh.positions[3*v+2]);
                                              }
                                              }
                                              
                                              for (size_t i = 0; i < materials.size(); i++) {
                                                printf("material[%ld].name = %s\n", i, materials[i].name.c_str());
                                                  printf("  material.Ka = (%f, %f ,%f)\n", materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]);
                                                    printf("  material.Kd = (%f, %f ,%f)\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
                                                      printf("  material.Ks = (%f, %f ,%f)\n", materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]);
                                                        printf("  material.Tr = (%f, %f ,%f)\n", materials[i].transmittance[0], materials[i].transmittance[1], materials[i].transmittance[2]);
                                                          printf("  material.Ke = (%f, %f ,%f)\n", materials[i].emission[0], materials[i].emission[1], materials[i].emission[2]);
                                                            printf("  material.Ns = %f\n", materials[i].shininess);
                                                              printf("  material.Ni = %f\n", materials[i].ior);
                                                                printf("  material.dissolve = %f\n", materials[i].dissolve);
                                                                  printf("  material.illum = %d\n", materials[i].illum);
                                                                    printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
                                                                      printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
                                                                        printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
                                                                          printf("  material.map_Ns = %s\n", materials[i].specular_highlight_texname.c_str());
                                                                            std::map<std::string, std::string>::const_iterator it(materials[i].unknown_parameter.begin());
                                                                              std::map<std::string, std::string>::const_iterator itEnd(materials[i].unknown_parameter.end());
                                                                                for (; it != itEnd; it++) {
                                                                                    printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
                                                                                      }
                                                                                        printf("\n");
                                                                                        }
}
/********************************************************/
