//
// Created by blackcat on 04/06/2016.
//

#ifndef CPPASSIGNMENT_PRODUCT_HPP
#define CPPASSIGNMENT_PRODUCT_HPP

#include <time.h>
#include <assert.h>
#include "ModelBase.hpp"

/**
 * Inherit class ModelBase. <br>
 * This class stores product properties: id, name, manufacturer, category, price, warranty time, number avalable.
 * @see class ModelBase
 * @see class ProductManager
 */
class Product : public ModelBase {
public:
    Product() : ModelBase() {}

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (Product&) reference itself.
     */
    Product &initialize() override {
        ModelBase::initialize();
        return *this;
    }

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (Product&) reference itself.
     */
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

    /* check if matching with unique properties */
    bool match(int id) {
        return getProductId() == id;
    }

    /* set / get */
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

    /**
     * Set number of products available.
     * @param count the number of products available.
     * @return (Product&) reference itself.
     */
    Product &setProductCount(int count) {
        (*this)[ITEM_COUNT] = count;
        (*this)[LAST_MODIFIED] = time(nullptr);
        return *this;
    }

    /**
     * Update number of products available.
     * @param offset changing offset
     * @return (Product&) reference itself.
     * @example
     * <li> changeItemCount(-2); // sold 2 products, remove them in "available" products.
     * <li> changeItemCount(5); // import 5 products to  "available" products will be sold.
     */
    Product &changeItemCount(int offset) {
        return setProductCount(getItemCount() + offset);
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

    int getItemCount() {
        return (*this)[ITEM_COUNT];
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
    static const int ITEM_COUNT = 4;
    static const int MANUFACTURER = 5;
    static const int CATEGORY = 6;
    static const int LAST_MODIFIED = 7;

    virtual unsigned int getFieldCount() const override {
        return FIELD_COUNT;
    }

    virtual DataType getFieldType(int &fieldIndex) const override {
        switch (fieldIndex) {
            case ID:
            case PRICE:
            case WARRANTY_DAYS:
            case ITEM_COUNT:
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
