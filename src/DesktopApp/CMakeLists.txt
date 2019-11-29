# File generated at : 16:11:15, Thu 28 Nov 
# Converted Project : src\DesktopApp/DesktopApp.vcxproj
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

##################### Variables ############################
# Change if you want modify path or other values           #
############################################################

# Project
get_filename_component(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
set(DEPENDENCIES_DIR ${PROJECT_DIR}/dependencies)
set(PROJECT_NAME DesktopApp)

# Dependencies
set(DESKTOPCORE_DIR ../DesktopCore)

# Outputs
set(OUTPUT_DEBUG ../../bin/Debug/DesktopApp/)
set(OUTPUT_RELEASE ../../bin/Release/DesktopApp/)

################# CMake Project ############################
# The main options of project                              #
############################################################

project(${PROJECT_NAME} CXX)

include_directories(${PROJECT_DIR})

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: Use Release by default.")
endif(NOT CMAKE_BUILD_TYPE)

############## Artefacts Output ############################
# Defines outputs , depending BUILD TYPE                   #
############################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${PROJECT_DIR}/${OUTPUT_DEBUG}")
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  "${PROJECT_DIR}/${OUTPUT_RELEASE}")
endif()

# Messages
message("${PROJECT_NAME}: MAIN PROJECT: ${CMAKE_PROJECT_NAME}")
message("${PROJECT_NAME}: CURR PROJECT: ${CMAKE_CURRENT_SOURCE_DIR}")
message("${PROJECT_NAME}: CURR BIN DIR: ${CMAKE_CURRENT_BINARY_DIR}")

################## Dependencies ############################
# Add Dependencies to project                              #
############################################################

# Dependencies: disable BUILD_DEPENDS to link with libraries already built
option(BUILD_DEPENDS "Build other CMake project." ON)

if(BUILD_DEPENDS)
  if(NOT TARGET DesktopCore)
    add_subdirectory("${DESKTOPCORE_DIR}" ${CMAKE_BINARY_DIR}/DesktopCore)
  endif()
else()
   link_directories(${DEPENDENCIES_DIR}/DesktopCore)
endif()

############### Files & Targets ############################
# Files of project and target to build                     #
############################################################

file(GLOB_RECURSE SRC_FILES "*.cpp" "*.cc" "*.rc")
file(GLOB_RECURSE HEADERS_FILES "*.h")

source_group("Sources" FILES ${SRC_FILES})
source_group("Headers" FILES ${HEADERS_FILES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    link_directories(${CMAKE_SOURCE_DIR}/lib/cef/Debug ${CMAKE_SOURCE_DIR}/lib/openssl/Debug ${CMAKE_SOURCE_DIR}/lib/sevenzip/Debug ${CMAKE_SOURCE_DIR}/lib/7zip/Static/Debug ${CMAKE_SOURCE_DIR}/lib/crashrpt/Debug ${CMAKE_SOURCE_DIR}/lib/cpprestsdk/Debug)
else()
    link_directories(${CMAKE_SOURCE_DIR}/lib/cef/Release ${CMAKE_SOURCE_DIR}/lib/openssl/Release ${CMAKE_SOURCE_DIR}/lib/sevenzip/Release ${CMAKE_SOURCE_DIR}/lib/7zip/Static/Release ${CMAKE_SOURCE_DIR}/lib/crashrpt/Release ${CMAKE_SOURCE_DIR}/lib/cpprestsdk/Release)
endif()

# Add executable to build.
add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES} ${HEADERS_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Jirafy")

######################### Flags ############################
# Defines Flags for Windows and Linux                      #
############################################################

if(NOT MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
   endif()
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /wd4100 /wd4127 /wd4244 /wd4481 /wd4512 /wd4701 /wd4702 /wd4996")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /wd4100 /wd4127 /wd4244 /wd4481 /wd4512 /wd4701 /wd4702 /wd4996")
endif()

# Preprocessor definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
   -D_WINDOWS 
   -D__STDC_CONSTANT_MACROS 
   -D__STDC_FORMAT_MACROS 
   -D_WIN32 
   -DUNICODE 
   -D_UNICODE 
   -DWINVER=0x0601 
   -D_WIN32_WINNT=0x601 
   -DNOMINMAX 
   -DWIN32_LEAN_AND_MEAN 
   -D_HAS_EXCEPTIONS=0 
   -DPSAPI_VERSION=1 
   # -DCEF_USE_SANDBOX 
   -DCEF_USE_ATL 
   -DCMAKE_INTDIR="Debug" 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W4 /Od /GR /Gy /Zi)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
   -D_WINDOWS 
   -DNDEBUG 
   -D__STDC_CONSTANT_MACROS 
   -D__STDC_FORMAT_MACROS 
   -D_WIN32 
   -DUNICODE 
   -D_UNICODE 
   -DWINVER=0x0601 
   -D_WIN32_WINNT=0x601 
   -DNOMINMAX 
   -DWIN32_LEAN_AND_MEAN 
   -D_HAS_EXCEPTIONS=0 
   -DPSAPI_VERSION=1 
   # -DCEF_USE_SANDBOX 
   -DCEF_USE_ATL 
   -D_NDEBUG 
   -DCMAKE_INTDIR="Release" 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W4 /GR /Gy)
    endif()
endif()

########### Link & Dependencies ############################
# Add project dependencies and Link to project             #
############################################################

# Project dependencies
add_dependencies(${PROJECT_NAME} DesktopCore)

# Link with other dependencies.
target_link_libraries(${PROJECT_NAME} DesktopCore )
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

if(MSVC)
    add_custom_command(
        TARGET ${PROJECT_NAME} 
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/src/DesktopUI/
            ${CMAKE_EXECUTABLE_OUTPUT_DIRECTORY}/Html/loading
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_libraries(${PROJECT_NAME} cpprest_2_10d.lib)
    else()
        target_link_libraries(${PROJECT_NAME} cpprest_2_10.lib)
    endif()
   target_link_libraries(${PROJECT_NAME} libeay32.lib ssleay32.lib version.lib CrashRpt.lib runtimeobject.lib comctl32.lib rpcrt4.lib shlwapi.lib ws2_32.lib d3d11.lib glu32.lib imm32.lib opengl32.lib oleacc.lib dbghelp.lib psapi.lib version.lib wbemuuid.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib )
endif(MSVC)