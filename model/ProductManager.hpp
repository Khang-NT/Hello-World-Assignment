//
// Created by blackcat on 06/06/2016.
//

#ifndef CPPASSIGNMENT_PRODUCTMANAGER_HPP
#define CPPASSIGNMENT_PRODUCTMANAGER_HPP


#include "ModelBase.hpp"

class ProductManager : public ModelBase {
public:
    ProductManager() : ModelBase() {}

    ProductManager &initialize() override {
        ModelBase::initialize();
        ModelBase::operator[](HEADER) = "MT2015-Shop";
        return *this;
    }

protected:
    static const int FIELD_COUNT = 3;
    static const int HEADER = 0;
    static const int AUTO_INCREASE_NUMBER = 1;
    static const int ARRAY_OF_PRODUCTS = 2;
};


#endif //CPPASSIGNMENT_PRODUCTMANAGER_HPP
