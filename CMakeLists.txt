cmake_minimum_required(VERSION 2.8.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
# include(CreateLaunchers)

if(MSVS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
  if(NOT "${MSVC_VERSION}" LESS 1400)
    add_definitions( "/MP" )
  endif()
endif(MSVS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(glPlus)
set(OUTPUT glPlus)

include (Utils.cmake)
SET(SRC "")
SET(INC "")

### OpenGL ###
find_package(OpenGL REQUIRED)
list(APPEND LIB ${OPENGL_LIBRARY})

## SDL2 ###
#set(SDL2_ROOT "c:/projects/libs/SDL2")
#include_directories("${SDL2_ROOT}/include")
#link_directories("${SDL2_ROOT}/lib")
#list(APPEND LIB SDL2d)
#list(APPEND LIB SDL2maind)


### GLEW ###
set(GLEW_ROOT "c:/projects/libs/glew")
include_directories("${GLEW_ROOT}/include")
#set(GLEW_LIB "${GLEW_ROOT}/lib/glew32sd.lib")
#set(GLEW_LIB "${GLEW_ROOT}/lib64/glew32sd.lib")
#link_directories("${GLEW_ROOT}/lib64")
#list(APPEND LIB ${GLEW_LIB})
#list(APPEND LIB glew32sd)

add_definitions(-DGLEW_STATIC)


### ext 
include_directories("${CMAKE_SOURCE_DIR}/ext")

list(APPEND SRC src/GL/Error.cpp)
list(APPEND SRC src/GL/VertexBuffer.cpp)
list(APPEND SRC src/GL/IndexBuffer.cpp)
list(APPEND SRC src/GL/VertexArray.cpp)
list(APPEND SRC src/GL/Texture.cpp)
list(APPEND SRC src/GL/FrameBuffer.cpp)
list(APPEND SRC src/GL/Shader.cpp)
list(APPEND SRC src/GL/Program.cpp)

list(APPEND INC src)

list(APPEND INC "${CMAKE_SOURCE_DIR}/include")

FILE(GLOB_RECURSE JPEG_SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/GL/util/libjpeg/*.c" )
FILE(GLOB_RECURSE PNG_SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/GL/util/libpng/*.c" )
FILE(GLOB_RECURSE ZLIB_SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/GL/util/zlib/*.c" )


list(APPEND SRC ${JPEG_SRC} )
list(APPEND SRC ${PNG_SRC} )
list(APPEND SRC ${ZLIB_SRC} )
list(APPEND SRC ${MATH_LIB_SRC} )

include_directories(src/GL/Math)
include_directories(src/GL/Util/libjpeg)
include_directories(src/GL/Util/libpng)
include_directories(src/GL/Util/zlib)


list(APPEND SRC src/Util/Image.cpp)

build_lib(${OUTPUT} SOURCES ${SRC} HEADERS ${INC} LIBS ${LIB})