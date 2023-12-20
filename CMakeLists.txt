cmake_minimum_required(VERSION 3.27)
project(untitled)

find_package(OpenCL REQUIRED)
include_directories( ${OPENCL_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp
        Butterfly.h
        RealAnalogTransformer.h
        OpenCLExecutor.h
        BFVectorCalculator.h
        RMCode.h
        utils.h
        VectorExpander.h
        LinearCoefsExtractor.h
        IntToBinaryConverter.h)

target_link_libraries(untitled "-framework OpenCL" )
