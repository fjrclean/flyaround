#flyaround project
#basic 3d game world with flyaround camera for development of other engine parts

cmake_minimum_required(VERSION 3.0)
project(flyaround)

cmake_policy(SET CMP0003 NEW)

add_subdirectory(src bin)

# add target to generate various documentation:
#	needs other refinement
# generate doxygen documentation under doxy/
# convert /doxy/docbook/todo.xml to github markdown
#	requires pandoc
#	requires GENERATE_DOCBOOK to be YES in flyaround.doxy
add_custom_target(doxy ALL
	COMMAND rm -f TODO.md
	COMMAND echo "* Generated from doxygen using @todo commands in source" > TODO.md
	COMMAND echo "* Do not manually add to this file, it will be overwritten!" >> TODO.md
	COMMAND echo "* This file will be generated with the default make target" >> TODO.md
	COMMAND doxygen flyaround.doxy
	COMMAND pandoc -f docbook -t markdown_github doxy/docbook/todo.xml >> TODO.md
)
