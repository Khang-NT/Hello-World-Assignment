cmake_minimum_required(VERSION 3.5)
project(CppAssignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        model/ModelBase.cpp model/ModelBase.hpp
        utils/HashSum.hpp
        utils/Utils.cpp utils/Utils.hpp
        model/Account.cpp model/Account.hpp)
add_executable(CppAssignment ${SOURCE_FILES})