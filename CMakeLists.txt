cmake_minimum_required(VERSION 2.6)
project(HUBO_work)

include_directories(include)

set(CMAKE_C_FLAGS "-std=gnu99")

set( CMAKE_VERBOSE_MAKEFILE true )

add_executable(tele_quad "src/tele_quad.cpp")
add_executable(tele_biped "src/tele_biped.cpp")
add_executable(tele_quad_maomao "src/tele_quad_maomao.cpp")
#target_link_libraries(tele_quad)
