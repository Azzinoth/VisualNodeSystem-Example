cmake_minimum_required(VERSION 3.10)

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

# Force your path to Dear ImGui
set(DEAR_IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui CACHE PATH "Path to Dear ImGui directory." FORCE)

if(NOT TARGET VisualNodeSystem)
	add_subdirectory(SubSystems/VisualNodeSystem)
endif()

# *************** THIRD_PARTY ***************

file(GLOB imgui_SRC
	"ThirdParty/imgui/imgui.cpp"
	"ThirdParty/imgui/imgui_demo.cpp"
	"ThirdParty/imgui/imgui_draw.cpp"
	"ThirdParty/imgui/imgui_impl_glfw.cpp"
	"ThirdParty/imgui/imgui_impl_opengl3.cpp"
	"ThirdParty/imgui/imgui_tables.cpp"
	"ThirdParty/imgui/imgui_widgets.cpp"
)

# *************** THIRD_PARTY END ***************

file(GLOB source_SRC
	"CustomNode.h"
	"CustomNode.cpp"
	"CustomNode2.h"
	"CustomNode2.cpp"
	"CustomNode3.h"
	"CustomNode3.cpp"
	"CustomNode4.h"
	"CustomNode4.cpp"
	"CustomNodeStyleDemonstration.h"
	"CustomNodeStyleDemonstration.cpp"
	"main.cpp"
)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew2/lib/$(PlatformTarget))
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/lib/$(PlatformTarget))

# add the executable
add_executable(Visual_Node_System_Example WIN32
			   ${source_SRC}
			   # *************** THIRD_PARTY ***************
			   ${imgui_SRC}
)

target_link_libraries(Visual_Node_System_Example VisualNodeSystem)

target_link_libraries(Visual_Node_System_Example glew32s.lib)
target_link_libraries(Visual_Node_System_Example glfw3.lib)
target_link_libraries(Visual_Node_System_Example glfw3dll.lib)
target_link_libraries(Visual_Node_System_Example opengl32.lib)

source_group("Source Files" FILES ${source_SRC})
# *************** THIRD_PARTY ***************
source_group("Source Files/ThirdParty/imgui" FILES ${imgui_SRC})

# set the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Visual_Node_System_Example)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew2/include
	${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty
	${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui
	${VISUAL_NODE_SYSTEM_DIR}
	${VISUAL_NODE_SYSTEM_THIRDPARTY_DIR}
)