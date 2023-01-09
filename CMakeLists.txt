#Template for INFOH502
#Heavily inspired from https://github.com/Polytonic/Glitter/blob/master/CMakeLists.txt

#project setup
project(infoh502-project-cpp)

#set the minimal version of cmake and the minimal version of the c++ language
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)     
set(CMAKE_VERBOSE_MAKEFILE ON)



find_package(OpenGL REQUIRED)

#for glad library
add_library( glad STATIC 3rdParty/glad/src/glad.c)
set(GLAD_INCLUDE "3rdParty/glad/include")
target_include_directories(glad PUBLIC ${GLAD_INCLUDE})

#for GLFW
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(3rdParty/glfw)

# CONFIGURE ASSIMP
add_subdirectory(assimp-master) 
include_directories(assimp-master/include/)


include_directories(3rdParty/glad/include/
                    3rdParty/glfw/include/
                    3rdParty/glm/
                    3rdParty/stb/)

        

# set(SOURCES_PROJECT "main.cpp")
set(SOURCES_PROJECT "main.cpp")

add_compile_definitions(PATH_TO_OBJECTS="${CMAKE_CURRENT_SOURCE_DIR}/objects")
add_compile_definitions(PATH_TO_TEXTURE="${CMAKE_CURRENT_SOURCE_DIR}/textures")

add_library(
    stb_image STATIC
    stb_image.cpp
    3rdParty/stb/stb_image.h
)
set(STB_INCLUDE "3rdParty/stb")
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(stb_image PUBLIC ${STB_INCLUDE})


add_executable(${PROJECT_NAME} ${SOURCES_PROJECT})
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL glfw glad stb_image assimp)
