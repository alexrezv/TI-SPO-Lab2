cmake_minimum_required(VERSION 3.6)
project(Lab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Shennon_algorithm/Coder.cpp Shennon_algorithm/Coder.h Shennon_algorithm/Decoder.cpp Shennon_algorithm/Decoder.h StringParser/StringParser.cpp StringParser/StringParser.h util/VectorUtil.cpp util/VectorUtil.h)
add_executable(Lab2 ${SOURCE_FILES})