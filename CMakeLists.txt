cmake_minimum_required(VERSION 3.10)
project(allocator)
add_library(allocator SHARED allocator.c)
set_target_properties(allocator PROPERTIES PUBLIC include/allocator.h)
