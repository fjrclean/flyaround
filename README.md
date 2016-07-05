# flyaround
My first game engine attempt. No use to anyone at this stage.

## State
Uses old fixed GL pipeline for rendering, camera working nicely, class that can manually load in wavefront .obj to be drawn.

## Contributing
* Guidelines can be found in CONVENTIONS.MD
* This project is licensed under the GNU General Public License v3.0.
 * Any code contributed must be under this license.
 * See LICENSE.txt for the full text.

## TODO
1. STARTED: entity class (entity.cpp,.hpp): representing a physical object.
 * Rotation of object should be stored as change to it's local axes. Each axis stored as a vec3. Using glm.
3. Logging class with severity levels.
 * Message pacing (eg error message happening at every step only is written to stderr each second). 
4. Add methods in netinst class to regulate game speed, ie only 30 steps a second.
 * Method that is called before each run of main loop, returning how long to wait? IDK!!
5. Release Matthew from HJ slavery.
6. Eat 4 snow cones at once.
* See TODO.md for list of specific things to do in sourcecode.

## Dependencies
* GLFW3 -- with GLU
* cmake >= 3.0
* Lua 5.3.2 dev files
* GLEW -- 'libglew-dev' package should work.
* 'pkg-config' package.
* [tinyobjloader](https://github.com/syoyo/tinyobjloader)
 * All of it's code is included in the header, meant to be placed in project directory. However I used the Makefile it comes with to install it's header to /usr/local/include and a useless lib in /usr/local/lib/ -- using the 'make && make install' after cloning it should work.
* 'pandoc' & 'doxygen' packages for documentation generation
 * Currently only docbook doxygen is output, with doxygen @todo commands embedded in source code extracted & converted to TODO.md
 * See CMakeLists.txt for more info -- need to clean it up.
 * To skip, use specific make targets 'game', 'server' & 'client'
