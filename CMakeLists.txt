cmake_minimum_required(VERSION 3.12)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

project(stroustrup_cpp)

set(CMAKE_CXX_STANDARD 17)

if(WIN32 AND MSVC AND MSVC_VERSION GREATER 1400)
    add_compile_options(/MP)
endif()

add_subdirectory ("src")

