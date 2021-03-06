cmake_minimum_required (VERSION 3.18)
set(CMAKE_C_COMPILER /usr/bin/gcc)

message("Building with CMake version: ${CMAKE_VERSION}")
message("Compiling with: ${CMAKE_C_COMPILER}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(td
    LANGUAGES C
    VERSION 1.0.0
)

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/main.c
    ${PROJECT_SOURCE_DIR}/parser.c
    ${PROJECT_SOURCE_DIR}/td.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
                          "${PROJECT_BINARY_DIR}"
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Credits to https://stackoverflow.com/a/69804923 
add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
            install_manifest.txt to be uninstalled!
)
