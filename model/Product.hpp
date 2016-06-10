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
    Product &initialize() override;

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (Product&) reference itself.
     */
    Product &initialize(int produceId, string name, string manufacturer,
                        string category, int price, string warrantyInfo,
                        int count = 0);

    /* check if matching with unique properties */
    bool match(int id);

    /* set / get */
    Product &setProductId(int id);

    Product &setProductName(string name);

    Product &setManufacturer(string manufacturer);

    Product &setCategory(string category);

    Product &setPrice(int price);

    Product &setWarranty(string warrantyInfo);

    /**
     * Set number of products available.
     * @param count the number of products available.
     * @return (Product&) reference itself.
     */
    Product &setItemCount(int count);

    /**
     * Update number of products available.
     * @param offset changing offset.
     * @return (Product&) reference itself.
     * @brief
     * <li> changeItemCount(-2); // sold 2 products, remove them in "available" products.
     * <li> changeItemCount(5); // imported 5 products to  "available" products will be sold.
     */
    Product &changeItemCount(int offset);

    int getProductId();

    string getProductName();

    int getPrice();

    string getWarrantyInfo();

    string getManufacturer();

    string getCategory();

    int getItemCount();

    int getLastModifiedTime();

protected:
    /* Constants */
    static const int FIELD_COUNT = 8;
    static const int ID = 0;
    static const int NAME = 1;
    static const int PRICE = 2;
    static const int WARRANTY_INFO = 3;
    static const int ITEM_COUNT = 4;
    static const int MANUFACTURER = 5;
    static const int CATEGORY = 6;
    static const int LAST_MODIFIED = 7;

    /* Override base funcs */
    virtual unsigned int getFieldCount() const override;

    virtual DataType getFieldType(int &fieldIndex) const override;

    /* Make protected base's method */
    virtual Object &operator[](size_t index) const override;
};


#endif //CPPASSIGNMENT_PRODUCT_HPP
