﻿# CMakeList.txt : CMake project for CustomPostProcessor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

project ("CustomPostProcessor")

# GLFW
set(GLFW_DIR ./glfw-3.3.8) # Set this to point to an up-to-date GLFW repo
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${GLFW_DIR} binary_dir EXCLUDE_FROM_ALL)
include_directories(${GLFW_DIR}/include)

# Dear ImGui
set(IMGUI_DIR ./DearImGUI)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ..)

# Vulkan
find_package(Vulkan REQUIRED)
#find_library(VULKAN_LIBRARY
  #NAMES vulkan vulkan-1)
#set(LIBRARIES "glfw;${VULKAN_LIBRARY}")
set(LIBRARIES "glfw;Vulkan::Vulkan")

# Use vulkan headers from glfw:
include_directories(${GLFW_DIR}/deps)

set (LINK_TO_MAIN 
${sources} 
${IMGUI_DIR}/backends/imgui_impl_glfw.cpp;
${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp; 
${IMGUI_DIR}/imgui.cpp; 
${IMGUI_DIR}/imgui_draw.cpp; 
${IMGUI_DIR}/imgui_demo.cpp; 
${IMGUI_DIR}/imgui_tables.cpp; 
${IMGUI_DIR}/imgui_widgets.cpp;
"src/application.cpp";
"src/application.h";
)

# Add source to this project's executable.
add_executable (CMakeTarget "main.cpp" ${LINK_TO_MAIN} )
target_link_libraries(CMakeTarget ${LIBRARIES})
target_compile_definitions(CMakeTarget PUBLIC -DImTextureID=ImU64)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()
