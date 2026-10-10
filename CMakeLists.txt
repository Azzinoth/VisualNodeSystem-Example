cmake_minimum_required(VERSION 3.10)

set(BUILD_TYPE "Debug and Release" CACHE STRING "Choose Build type")
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# set the project name
project(Visual_Node_System_Example LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(USE_STATIC_RUNTIME ON CACHE BOOL "Use static runtime (/MT) instead of dynamic (/MD)" FORCE)

if(MSVC)
	# Disable C4251 warning
	add_compile_options(/wd4251)

	if(USE_STATIC_RUNTIME)
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	else()
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	endif()

	# Always add /MP for multi-processor compilation
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT TARGET FEBasicApplication)
	add_subdirectory(SubSystems/FEBasicApplication)
endif()

# VisualNodeSystem must be compiled against the same Dear ImGui that FEBasicApplication compiles.
set(DEAR_IMGUI_INCLUDE_DIR ${BASICAPP_THIRDPARTY_DIR}/imgui CACHE PATH "Path to Dear ImGui directory." FORCE)
set(VISUAL_NODE_SYSTEM_BUILD_SHARED_LIBS OFF CACHE BOOL "Build VisualNodeSystem as a shared library" FORCE)
set(VISUAL_NODE_SYSTEM_USE_STATIC_RUNTIME ${USE_STATIC_RUNTIME} CACHE BOOL "Use static runtime (/MT) instead of dynamic (/MD) for VisualNodeSystem" FORCE)

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
	"CustomNodeStyleDemonstration.h"
	"CustomNodeStyleDemonstration.cpp"
	"main.cpp"
)

if(NOT EMSCRIPTEN)
	link_directories(${GLEW_LIB_DIR})
	link_directories(${GLFW_LIB_DIR})
endif()

# add the executable
add_executable(Visual_Node_System_Example WIN32
			   ${source_SRC}
)

target_link_libraries(Visual_Node_System_Example
	PRIVATE
		VisualNodeSystem
		FEBasicApplication
)

# On Emscripten, emit an .html alongside the .js/.wasm, built from Web_Shell.html
# (a full-window #canvas that hosts the wasm app).
if(EMSCRIPTEN)
	set_target_properties(Visual_Node_System_Example PROPERTIES
		SUFFIX ".html"
		LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Web_Shell.html"
	)
	target_link_options(Visual_Node_System_Example PRIVATE "--shell-file=${CMAKE_CURRENT_SOURCE_DIR}/Web_Shell.html")
	target_link_options(Visual_Node_System_Example PRIVATE "-sALLOW_MEMORY_GROWTH=1")
endif()

if(FE_GRAPHIC_API_BACKEND STREQUAL "WebGPU" AND NOT EMSCRIPTEN)
	target_link_libraries(Visual_Node_System_Example
		PRIVATE
			debug ${DAWN_LIBRARY_DEBUG}
			optimized ${DAWN_LIBRARY_RELEASE}
	)
endif()

source_group("Source Files" FILES ${source_SRC})

# set the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Visual_Node_System_Example)

include_directories(
	${GLEW_INCLUDE_DIR}
	${BASICAPP_THIRDPARTY_DIR}
	${BASICAPP_THIRDPARTY_DIR}/imgui
	${VISUAL_NODE_SYSTEM_DIR}
	${VISUAL_NODE_SYSTEM_THIRDPARTY_DIR}
	$<$<STREQUAL:${FE_GRAPHIC_API_BACKEND},WebGPU>:${DAWN_INCLUDE_DIR}>
)

if(FE_GRAPHIC_API_BACKEND STREQUAL "WebGPU" AND NOT EMSCRIPTEN)
	add_custom_command(TARGET Visual_Node_System_Example POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${DAWN_LIB_DIR}$<IF:$<CONFIG:Debug>,Debug,Release>/Dynamic_runtime/"
			"$<TARGET_FILE_DIR:Visual_Node_System_Example>"
	)
endif()
