cmake_minimum_required(VERSION 2.8)
project(icg)

#--- Load the common ICG configuration
include(common/config.cmake)
include(common/Eigen.cmake)
include(common/OpenGP.cmake)

#--- OpenGL configuration
include(common/OpenGL.cmake)
include(common/GLEW.cmake)
include(common/GLFW.cmake)

#--- Subprojects
add_subdirectory(raytrace)

#--- Live editing
SET(GCC_LIVE_EDIT_COMPILE_FLAGS " /FASTLINK /ZI")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_LIVE_EDIT_COMPILE_FLAGS}" )