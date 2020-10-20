cmake_minimum_required(VERSION 3.17)
project(finite_difference_method C)

set(CMAKE_C_STANDARD 11)

add_executable(finite_difference_method main_23.c odu_23.c funkp_23.c funkq_23.c funkf_23.c)