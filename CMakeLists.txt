cmake_minimum_required(VERSION 3.5)
project(CppAssignment)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libgcc -static-libstdc++")

set(SOURCE_FILES
        main.cpp
        model/ModelBase.cpp model/ModelBase.hpp
        model/Account.hpp
        model/AccountManager.hpp model/AccountManager.cpp
        model/Product.hpp
        model/ProductManager.hpp
        utils/HashSum.hpp
        utils/Utils.cpp utils/Utils.hpp
        utils/MenuHelper.cpp utils/MenuHelper.hpp
        utils/ExportHTML.hpp utils/ExportHTML.cpp
        utils/DateTimeFormat.cpp utils/DateTimeFormat.hpp
        screen/LoginScreen.hpp screen/LoginScreen.cpp
        screen/AdminScreen.cpp screen/AdminScreen.hpp
        screen/ManagerScreen.cpp screen/ManagerScreen.hpp
        template/AccountListTemplate.hpp model/Account.cpp
        template/ProductListTemplate.hpp model/ProductManager.cpp model/Product.cpp model/Order.cpp model/Order.hpp model/OrderManager.cpp model/OrderManager.hpp screen/GuestScreen.cpp screen/GuestScreen.hpp)
add_executable(CppAssignment ${SOURCE_FILES})