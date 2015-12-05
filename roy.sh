 #!/bin/bash 

export CMAKE_MODULE_PATH=./lib/SFML/share/SFML/cmake/Modules
export LIB=./lib/SFML/lib
export INCLUDE=./lib/SFML/include

cmake .
make
