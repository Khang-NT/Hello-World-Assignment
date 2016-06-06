cmake_minimum_required(VERSION 3.5)
project(CppAssignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        model/ModelBase.cpp model/ModelBase.hpp
        model/Account.hpp
        model/AccountManager.hpp
        model/Product.hpp
        model/ProductManager.hpp
        utils/HashSum.hpp
        utils/Utils.cpp utils/Utils.hpp
        utils/MenuHelper.cpp utils/MenuHelper.hpp)
add_executable(CppAssignment ${SOURCE_FILES})