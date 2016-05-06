#flyaround project
#basic 3d game world with flyaround camera for development of other engine parts

add_executable(flyaround
	main.cpp
	vector_math.cpp
	camera.cpp
	obj_model.cpp
	#lua_object.cpp
)

find_package(GLEW)
if(GLEW_FOUND)
	target_link_libraries(flyaround ${GLEW_LIBRARIES})
	include_directories(${GLEW_INCLUDE_DIRS})
endif(GLEW_FOUND)

#glu includes handled by GLFW_INCLUDE_GLU define in main.cpp
find_package (OpenGL)
if (OPENGL_GLU_FOUND)
	target_link_libraries (flyaround ${OPENGL_glu_LIBRARY})
endif (OPENGL_GLU_FOUND)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories (${GLFW_INCLUDE_DIRS})
target_link_libraries (flyaround
	 ${GLFW_STATIC_LIBRARIES}
)

#Lua5.3.2
find_package(Lua)
if(LUA_FOUND)
	target_link_libraries(flyaround ${LUA_LIBRARIES})
	include_directories(${LUA_INCLUDE_DIR})
endif(LUA_FOUND)