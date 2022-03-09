cmake_minimum_required (VERSION 3.0)

project(BvhConv)

#Find dependencies
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

#Generate the static library from the library sources
add_library(json_library STATIC 
    lib/json/json_reader.cpp
    lib/json/json_value.cpp
    lib/json/json_writer.cpp
)

# Add an executable with the above sources
add_executable(BvhConv
    main.cpp
    Motion.cpp 
    KinTree.cpp 
    SpAlg.cpp 
    RBDUtil.cpp 
    Shape.cpp 
    Rand.cpp 
    MathUtil.cpp 
    JsonUtil.cpp 
    FileUtil.cpp 
    BVHReader.cpp
)

target_include_directories(BvhConv
    PUBLIC 
        /usr/include/eigen3
)

# link the new hello_library target with the hello_binary target
target_link_libraries( BvhConv
    PRIVATE 
        json_library
)