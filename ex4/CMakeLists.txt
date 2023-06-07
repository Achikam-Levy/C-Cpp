cmake_minimum_required(VERSION 3.16.3)
project(ex4_aaa997)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex4_aaa997
        Activation.cpp
        Activation.h
        Dense.cpp
        Dense.h
        Matrix.cpp
        Matrix.h
        MlpNetwork.cpp
        MlpNetwork.h
        tests.cpp)
