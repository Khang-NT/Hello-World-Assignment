//
// Created by blackcat on 04/06/2016.
//

#ifndef CPPASSIGNMENT_PRODUCT_HPP
#define CPPASSIGNMENT_PRODUCT_HPP

#include <time.h>
#include <assert.h>
#include "ModelBase.hpp"

class Product : public ModelBase {
public:
    Product() : ModelBase() {}

    Product &initialize() override {
        ModelBase::initialize();
        return *this;
    }

    Product &initialize(int produceId, string name, string manufacturer, string category, int price, int warrantyDays,
                          int count = 0) {
        ModelBase::initialize();
        setProductId(produceId)
                .setProductName(name)
                .setManufacturer(manufacturer)
                .setCategory(category)
                .setPrice(price)
                .setWarranty(warrantyDays)
                .setProductCount(count);
        return *this;
    }

    bool match(int id) {
        return getProductId() == id;
    }

    Product &setProductId(int id) {
        (*this)[ID] = id;
        (*this)[LAST_MODIFIED] = time(nullptr);
        return *this;
    }

    Product &setProductName(string name) {
        (*this)[NAME] = name;
        (*this)[LAST_MODIFIED] = time(nullptr);
        return *this;
    }

    Product &setManufacturer(string manufacturer) {
        (*this)[MANUFACTURER] = manufacturer;
        (*this)[LAST_MODIFIED] = time(nullptr);
        return *this;
    }

    Product &setCategory(string category) {
        (*this)[CATEGORY] = category;
        (*this)[LAST_MODIFIED] = time(nullptr);
        return *this;
    }

    Product &setPrice(int price) {
        (*this)[PRICE] = price;
        (*this)[LAST_MODIFIED] = time(nullptr);
        return *this;
    }

    Product &setWarranty(int warrantyDays) {
        (*this)[WARRANTY_DAYS] = warrantyDays;
        (*this)[LAST_MODIFIED] = time(nullptr);
        return *this;
    }

    Product &setProductCount(int count) {
        (*this)[PRODUCT_COUNT] = count;
        (*this)[LAST_MODIFIED] = time(nullptr);
        return *this;
    }

    Product &changeProductCount(int offset) {
        return setProductCount(getProductCount() + offset);
    }

    int getProductId() {
        return (*this)[ID];
    }

    string getProductName() {
        return (*this)[NAME];
    }

    int getPrice() {
        return (*this)[PRICE];
    }

    int getWarrantyDays() {
        return (*this)[WARRANTY_DAYS];
    }

    string getManufacturer() {
        return (*this)[MANUFACTURER];
    }

    int getCategory() {
        return (*this)[CATEGORY];
    }

    int getProductCount() {
        return (*this)[PRODUCT_COUNT];
    }

    int getLastModifiedTime() {
        return (*this)[LAST_MODIFIED];
    }

protected:
    static const int FIELD_COUNT = 8;
    static const int ID = 0;
    static const int NAME = 1;
    static const int PRICE = 2;
    static const int WARRANTY_DAYS = 3;
    static const int PRODUCT_COUNT = 4;
    static const int MANUFACTURER = 5;
    static const int CATEGORY = 6;
    static const int LAST_MODIFIED = 7;

    virtual unsigned int getFieldCount() override {
        return FIELD_COUNT;
    }

    virtual DataType getFieldType(int &fieldIndex) override {
        switch (fieldIndex) {
            case ID:
            case PRICE:
            case WARRANTY_DAYS:
            case PRODUCT_COUNT:
            case LAST_MODIFIED:
                return TYPE_INTEGER;
            case NAME:
            case MANUFACTURER:
            case CATEGORY:
                return TYPE_STRING;
            default:
                assert(false);
        }
    }
};


#endif //CPPASSIGNMENT_PRODUCT_HPP
