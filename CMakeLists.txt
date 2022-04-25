cmake_minimum_required(VERSION 3.22)
project(analisador_c C)

set(CMAKE_C_STANDARD 17)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})

add_executable(analisador_c main.c lexico.h lexico.c)

target_link_libraries(analisador_c ${GTK4_LIBRARIES})
install(TARGETS analisador_c)
