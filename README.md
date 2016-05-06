# flyaround
My first game engine attempt. No use to anyone at this stage.

## State
Uses old fixed GL pipeline for rendering, camera working but stuffy, class that can manually load in wavefront .obj to be drawn.

## TODO
Complete glshader.hpp & .cpp to create & manage shader programs.
Create class to add & remove vertices from .objs to be drawn by shaders.
Lua integration -- logical game objects will be in lua.
Basic netcode

## Dependencies
GLFW3 -- with GLU
cmake 3.5
Lua 5.3.2
GLEW
