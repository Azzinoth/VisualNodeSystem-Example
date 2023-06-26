cmake_minimum_required(VERSION 3.1)

set(BUILD_TYPE "Debug and Release" CACHE STRING "Choose Build type")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# set the project name
project(Visual_Node_System_Example LANGUAGES CXX)

# set different compiler flags depending on build type
set(CMAKE_CXX_FLAGS_DEBUG "/MP /ZI /W3 /Od /MDd /JMC /sdl /FC /D WIN32 /D IMGUI_IMPL_OPENGL_LOADER_GLEW /D _WINDOWS /D _DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "/MP /W3 /O2 /Oi /Gy /sdl /FC /GL /OPT:REF /OPT:ICF /D WIN32 /D IMGUI_IMPL_OPENGL_LOADER_GLEW /D NDEBUG /D _WINDOWS")

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT TARGET VisualNodeSystem)
	add_subdirectory(SubSystems/VisualNodeSystem)
endif()

file(GLOB source_SRC
	"CustomNode.h"
	"CustomNode.cpp"
	"CustomNode2.h"
	"CustomNode2.cpp"
	"CustomNode3.h"
	"CustomNode3.cpp"
	"CustomNode4.h"
	"CustomNode4.cpp"
	"main.cpp"
)

link_directories(${GLEW_LIB_DIR})
link_directories(${GLFW_LIB_DIR})

# add the executable
add_executable(Visual_Node_System_Example WIN32
			   ${source_SRC}
)

target_link_libraries(Visual_Node_System_Example VisualNodeSystem)

target_link_libraries(Visual_Node_System_Example glew32s.lib)
target_link_libraries(Visual_Node_System_Example glfw3.lib)
target_link_libraries(Visual_Node_System_Example glfw3dll.lib)
target_link_libraries(Visual_Node_System_Example opengl32.lib)

source_group("Source Files" FILES ${source_SRC})

# set the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Visual_Node_System_Example)

include_directories(
	${GLEW_INCLUDE_DIR}
	${BASICAPP_THIRDPARTY_DIR}
	${BASICAPP_DIR}
	${VISUAL_NODE_SYSTEM_DIR}
	${VISUAL_NODE_SYSTEM_THIRDPARTY_DIR}
)