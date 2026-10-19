cmake_minimum_required(VERSION 3.28)
project(ExamWaitlist LANGUAGES CXX)

add_executable(program main.cpp waitlist.cpp)
target_compile_features(program PRIVATE cxx_std_20)
target_sources(program PRIVATE
    FILE_SET CXX_MODULES FILES waitlist.cppm
)
