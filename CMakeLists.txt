cmake_minimum_required(VERSION 3.16)
project(DSA_LeetCode CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-Wall -Wextra -g)

# Your own data structure implementations (header-only) live in common/include,
# e.g. common/include/list_node.hpp, common/include/tree_node.hpp, ...
include_directories(${CMAKE_SOURCE_DIR}/common/include)

# Every .cpp file under a chapter folder (ch03/, ch04/, ...) is treated as one
# self-contained LeetCode question with its own main(). Each becomes its own
# executable, built to sit right next to its source file.
file(GLOB_RECURSE QUESTION_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/*.cpp)
list(FILTER QUESTION_SOURCES EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/common/")

foreach(src ${QUESTION_SOURCES})
    get_filename_component(src_dir ${src} DIRECTORY)
    get_filename_component(src_name ${src} NAME_WE)
    file(RELATIVE_PATH rel_dir ${CMAKE_SOURCE_DIR} ${src_dir})
    string(REPLACE "/" "_" target_name "${rel_dir}_${src_name}")

    add_executable(${target_name} ${src})
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${src_dir}
        OUTPUT_NAME ${src_name}
    )
endforeach()
