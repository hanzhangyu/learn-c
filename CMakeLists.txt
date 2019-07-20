cmake_minimum_required(VERSION 3.14)
project(learn_c C)

set(CMAKE_C_STANDARD 11)

add_executable(touch info/touch.c)
add_executable(exed mult/exec.c)
