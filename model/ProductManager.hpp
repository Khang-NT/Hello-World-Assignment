//
// Created by blackcat on 06/06/2016.
//

#ifndef CPPASSIGNMENT_PRODUCTMANAGER_HPP
#define CPPASSIGNMENT_PRODUCTMANAGER_HPP


#include <assert.h>
#include "ModelBase.hpp"
#include "Product.hpp"

/**
 * Inherit class ModelBase. <br>
 * This class provides feature managing products (count, search, add, update).
 * @see class ModelBase
 * @see class Product
 */
class ProductManager : public ModelBase {
public:
    ProductManager() : ModelBase() {}

    ProductManager &initialize() override {
        ModelBase::initialize();
        ModelBase::operator[](HEADER) = "MT2015-Shop";
        return *this;
    }

    unsigned getProductCount() {
        return (unsigned) getProductList()->size();
    }

    Product &operator[](int position) {
        return *static_cast<Product *>((*getProductList())[position]);
    }

    Product *findProduct(int productId) {
        for (ModelBase *product : *getProductList())
            if (((Product *) product)->match(productId))
                return (Product *) product;
        return nullptr;
    }

    Product &addProduct(string name, string manufacturer, string category, int price, int warrantyDays,
                        int count = 0) {
        Product *product = &(new Product())->initialize(
                increaseUniqueIndex(),
                name, manufacturer, category, price,
                warrantyDays, count
        );
        getProductList()->push_back(product);
        return *product;
    }

protected:
    static const int FIELD_COUNT = 3;
    static const int HEADER = 0;
    static const int AUTO_INCREASE_NUMBER = 1;
    static const int ARRAY_OF_PRODUCTS = 2;

    virtual unsigned int getFieldCount() override {
        return FIELD_COUNT;
    }

    virtual DataType getFieldType(int &fieldIndex) override {
        switch (fieldIndex) {
            case HEADER:
                return TYPE_STRING;
            case AUTO_INCREASE_NUMBER:
                return TYPE_INTEGER;
            case ARRAY_OF_PRODUCTS:
                return TYPE_ARRAY_OF_MODELS;
            default:
                assert(false);
        }
    }

    virtual ModelBase *createVectorItem() override {
        return &(new Product())->initialize();
    }

    vector<ModelBase *> *getProductList() {
        return ModelBase::operator[](TYPE_ARRAY_OF_MODELS);
    };

    int increaseUniqueIndex() {
        int currentIndex = ModelBase::operator[](AUTO_INCREASE_NUMBER);
        return ModelBase::operator[](AUTO_INCREASE_NUMBER) = ++currentIndex;
    }
};


#endif //CPPASSIGNMENT_PRODUCTMANAGER_HPP
