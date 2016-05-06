# flyaround
My first game engine attempt. No use to anyone at this stage.

## State
Uses old fixed GL pipeline for rendering, camera working but stuffy, class that can manually load in wavefront .obj to be drawn.

## TODO
1. Complete glshader.hpp & .cpp to create & manage shader programs.
2. Create class to add & remove vertices from .objs to be drawn by shaders.
3. Lua integration -- logical game objects will be in lua.
4. Basic netcode

## Dependencies
GLFW3 -- with GLU
cmake 3.5
Lua 5.3.2
GLEW
