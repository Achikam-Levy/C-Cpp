cmake_minimum_required(VERSION 3.16.3)
project(ex5-aaa997)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex5-aaa997
        Movie.cpp
        Movie.h
        presubmit.cpp
        RecommenderSystem.h
        RecommenderSystem.cpp
        RecommenderSystemLoader.h
        RecommenderSystemLoader.cpp
        RSUsersLoader.h
        RSUsersLoader.cpp
        RSUser.cpp
        RSUser.h
        )
