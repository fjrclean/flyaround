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
1. Create class/s to manage vertex array objects and buffers
2. Create class to add & remove vertices from .objs to be drawn by shaders.
3. Lua integration -- logical game objects will be in lua.
4. Logging class which can take appropriate action (such as close program). So every call does not need to be error checked. 
5. netcode -- client/server structure: WIP
 * Using UDP to avoid latency
 * Reimplementing retransmission & aknowledgment, inspired by [Quake3](http://fabiensanglard.net/quake3/network.php)
 * Server transmits current state of game (stored as struct) to clients per step.
 * Clients transmit events (stored as struct) to server per step.
 * Windows will require reimplementation in winsock2, should be fairly easy.
6. Release Matthew from HJ slavery.

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
