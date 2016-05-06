# flyaround
My first game engine attempt. No use to anyone at this stage.

## State
Uses old fixed GL pipeline for rendering, camera working but stuffy, class that can manually load in wavefront .obj to be drawn.

## TODO
1. Complete glshader.hpp & .cpp to create & manage shader programs.
2. Create class to add & remove vertices from .objs to be drawn by shaders.
3. Lua integration -- logical game objects will be in lua.
4. Basic netcode
5. Release Matthew from HJ slavery.

## Dependencies
	GLFW3 -- with GLU
	cmake >= 3.0
	Lua 5.3.2 dev files
	GLEW -- 'libglew-dev' package should work.
	'pkg-config' package.
	https://github.com/syoyo/tinyobjloader -- all of it's code is included in the header, meant to be placed in project directory. However I used the Makefile it comes with to install it's header to /usr/local/include and a useless lib in /usr/local/lib/ -- using the 'make && make install' after cloning it should work.
