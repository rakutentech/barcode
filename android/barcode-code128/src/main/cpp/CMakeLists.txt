cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -fno-exceptions -fno-rtti")

include_directories(../../../../../src/code128/)

add_library(barcode-code128 SHARED barcode-code128.cpp ../../../../../src/code128/bar128encode.c)

