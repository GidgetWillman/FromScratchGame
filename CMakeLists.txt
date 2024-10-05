cmake_minimum_required(VERSION 3.28)
project(BumblyBingusEngine VERSION 0.0.1)
cmake_policy(SET CMP0072 NEW)
set(source_dir "${PROJECT_SOURCE_DIR}/src/")
set(CMAKE_TOOLCHAIN_FILE "${PROJECT_SOURCE_DIR}/mingw_toolchain.cmake")

file (GLOB source_files "${source_dir}/*.cpp" "${source_dir}/*.c")

find_package(OpenGL REQUIRED)

add_executable(BumblyBingusEngine 
    ${source_files}
)

target_include_directories(BumblyBingusEngine
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(BumblyBingusEngine glfw)