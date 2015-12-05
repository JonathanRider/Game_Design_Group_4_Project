# Project name
project(RoysReality)

# Minimum Cmake Version
cmake_minimum_required(VERSION 2.6)

# Set include path to CMAKE_MODULE_PATH environment variable.
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})

# Find SFML
find_package(SFML COMPONENTS graphics window system audio network QUIET)
include_directories(${SFML_INCLUDE_DIR})
link_libraries(${SFML_LIBRARIES})

if(NOT SFML_FOUND)
  # SFML not found
  message(FATAL_ERROR " * Make sure CMAKE_MODULE_PATH points to the cmake/Modules directory of your SFML install.\n * Make sure LIB includes the directory where the SFML libraries are installed.\n * Make sure INCLUDE includes the directory where the SFML header files are installed.")
endif()



file(GLOB_RECURSE Foo_SOURCES "src/*.cpp" "lib/xmlParser/*.cpp")

file(GLOB_RECURSE Foo_HEADERS "include/*.h" "lib/xmlParser/*.h")


set (Foo_INCLUDE_DIRS "")
foreach (_headerFile ${Foo_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Foo_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Foo_INCLUDE_DIRS)

message("${Foo_INCLUDE_DIRS}\n")
message("${Foo_SOURCES}\n")
include_directories(${Foo_INCLUDE_DIRS})

# set include dirs
#include_directories(${pong_SOURCE_DIR}/include)

# get CPP files
#file(GLOB SRC src/*cpp)

# get executables
file(GLOB EXECLIST bin/*cpp)

foreach(EXEC ${EXECLIST})
  GET_FILENAME_COMPONENT(BASE ${EXEC} NAME_WE)
  message("-- Adding compile target: ${BASE}")
  add_executable(${BASE} ${Foo_SOURCES} ${EXEC})
endforeach(EXEC)
