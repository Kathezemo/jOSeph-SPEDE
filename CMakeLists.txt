cmake_minimum_required(VERSION 3.15)
project(JosH C)

set(CMAKE_C_STANDARD 99)

add_executable(JosH kernel.c proc.c misc.c boot.c syscall.c syscall.h)