cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_BUILD_TYPE Debug)

project(SDD2022)

file(GLOB files_srcs CONFIGURE_DEPENDS "*/*.c")
file(GLOB files_others CONFIGURE_DEPENDS "*/*.txt")

foreach(file IN LISTS files_srcs)
    get_filename_component(fname "${file}" NAME_WE)
    add_executable("${fname}" "${file}")
endforeach()

foreach (file IN LISTS files_others)
    get_filename_component(fname "${file}" NAME)
    configure_file("${file}" "${fname}" COPYONLY)
endforeach ()