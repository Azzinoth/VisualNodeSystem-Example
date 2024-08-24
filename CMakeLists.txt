cmake_minimum_required(VERSION 3.10)

set(BUILD_TYPE "Debug and Release" CACHE STRING "Choose Build type")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# set the project name
project(Visual_Node_System_Example LANGUAGES CXX)

# Set compiler flags based on VISUAL_NODE_SYSTEM_USE_STATIC_RUNTIME
if(MSVC)
    # Disable C4251 warning
    add_compile_options(/wd4251)

    if(VISUAL_NODE_SYSTEM_USE_STATIC_RUNTIME)
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

# Force your path to Dear ImGui
set(DEAR_IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui CACHE PATH "Path to Dear ImGui directory." FORCE)

# Adjust GLFW and GLEW linking based on VISUAL_NODE_SYSTEM_BUILD_SHARED_LIBS and VISUAL_NODE_SYSTEM_USE_STATIC_RUNTIME
if(VISUAL_NODE_SYSTEM_BUILD_SHARED_LIBS)
    if(VISUAL_NODE_SYSTEM_USE_STATIC_RUNTIME)
        message(WARNING "Building a shared library with static runtime is uncommon and may lead to issues.")
        set(VISUAL_NODE_SYSTEM_GLFW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/lib/x64/glfw3_mt.lib CACHE PATH "Path to GLFW library." FORCE)
        set(GLEW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew2/lib/x64/glew32s.lib)
    else()
        set(VISUAL_NODE_SYSTEM_GLFW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/lib/x64/glfw3dll.lib CACHE PATH "Path to GLFW library." FORCE)
        set(GLEW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew2/lib/x64/glew32.lib)
    endif()

    set(VISUAL_NODE_SYSTEM_GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ CACHE PATH "Path to GLFW include directory." FORCE)
else()
    if(VISUAL_NODE_SYSTEM_USE_STATIC_RUNTIME)
        set(VISUAL_NODE_SYSTEM_GLFW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/lib/x64/glfw3_mt.lib CACHE PATH "Path to GLFW library." FORCE)
        set(GLEW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew2/lib/x64/glew32s.lib)
    else()
        set(VISUAL_NODE_SYSTEM_GLFW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/lib/x64/glfw3.lib CACHE PATH "Path to GLFW library." FORCE)
        set(GLEW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew2/lib/x64/glew32.lib)
    endif()
endif()

# Define GLEW_STATIC for static builds
if(USE_STATIC_RUNTIME)
    add_definitions(-DGLEW_STATIC)
endif()

if(NOT TARGET VisualNodeSystem)
	add_subdirectory(SubSystems/VisualNodeSystem)
endif()

# *************** THIRD_PARTY ***************

set(imgui_SRC "")
if(NOT VISUAL_NODE_SYSTEM_BUILD_SHARED_LIBS)
    list(APPEND imgui_SRC
        "ThirdParty/imgui/imgui.cpp"
	    "ThirdParty/imgui/imgui_demo.cpp"
	    "ThirdParty/imgui/imgui_draw.cpp"
	    "ThirdParty/imgui/imgui_impl_glfw.cpp"
	    "ThirdParty/imgui/imgui_impl_opengl3.cpp"
	    "ThirdParty/imgui/imgui_tables.cpp"
	    "ThirdParty/imgui/imgui_widgets.cpp"
    )
endif()

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

link_directories(${GLFW_LIB_DIR})

# add the executable
add_executable(Visual_Node_System_Example WIN32
			   ${source_SRC}
			   # *************** THIRD_PARTY ***************
			   ${imgui_SRC}
)

# Define GLEW_STATIC for static builds
if(VISUAL_NODE_SYSTEM_USE_STATIC_RUNTIME)
    add_definitions(-DGLEW_STATIC)
endif()

target_link_libraries(Visual_Node_System_Example 
    PRIVATE
        VisualNodeSystem
        ${GLEW_LIBRARY}
        ${VISUAL_NODE_SYSTEM_GLFW_LIBRARY}
        opengl32.lib
)

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

# If building as DLL, copy necessary DLLs to output directory
if(VISUAL_NODE_SYSTEM_BUILD_SHARED_LIBS)
    add_custom_command(TARGET Visual_Node_System_Example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GLFW/lib/x64/glfw3.dll"
            "$<TARGET_FILE_DIR:Visual_Node_System_Example>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE_DIR:VisualNodeSystem>/VisualNodeSystem.dll"
            "$<TARGET_FILE_DIR:Visual_Node_System_Example>"
    )
endif()

# If using dynamic runtime, copy necessary DLLs to output directory
if(NOT VISUAL_NODE_SYSTEM_USE_STATIC_RUNTIME)
    add_custom_command(TARGET Visual_Node_System_Example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew2/lib/x64/glew32.dll"
            "$<TARGET_FILE_DIR:Visual_Node_System_Example>"
    )
endif()