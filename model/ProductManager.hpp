//
// Created by blackcat on 06/06/2016.
//

#ifndef CPPASSIGNMENT_PRODUCTMANAGER_HPP
#define CPPASSIGNMENT_PRODUCTMANAGER_HPP


#include <assert.h>
#include "ModelBase.hpp"
#include "Product.hpp"
#include "../utils/Utils.hpp"

const string ITEM_DB_FILE = "ItemDB.dat";
const string ITEM_DB_FILE_HEADER = "MT2015-Shop";

/**
 * Inherit class ModelBase. <br>
 * This class provides feature managing products (count, search, add, update).
 * @see class ModelBase
 * @see class Product
 */
class ProductManager : public ModelBase {
private:
    /**
     * Singleton instance.
     */
    static ProductManager *sInstance;
public:
    ProductManager() : ModelBase() {}

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (ProductManager&) reference itself.
     */
    ProductManager &initialize() override;

    /**
     * Get singleton instance. <br>
     * If it wasn't created, do initialization with default data (include admin account).
     * @return (AccountManager &) singleton instance of AccountManager.
     */
    static ProductManager *getInstance();

    /**
     * Get number of existing products.
     * @return (unsigned) number of existing products.
     */
    static unsigned getProductCount() {
        return (unsigned) getInstance()->getProductList()->size();
    }

    /**
     * Get a COPY of product object at given position.
     * @param position (int)
     * @return (Product) a COPY of product object at position.
     */
    static Product getProductAt(int position) {
        return *static_cast<Product *>((*getInstance()->getProductList())[position]);
    }

    /**
     * Find product by given ID.
     * @param productId product's id.
     * @return position of product matches given ID or -1 if not found.
     */
    static int findProduct(int productId);

    /**
     * Add product.<br>
     * After that, all data will be stored to disk automatically.
     * @param name
     * @param manufacturer
     * @param category
     * @param price
     * @param warrantyDays
     * @param count
     * @return Copy of new product object.
     */
    static Product addProduct(string name, string manufacturer, string category, int price, string warrantyInfo,
                              int count = 0);

    /**
     * Replace product at position with newData. <br>
     * After that, all data will be stored to disk automatically.
     * @param position (int)
     * @param newData (Product)
     */
    static void updateProduct(int position, Product newData);

    /**
     * Remove product at position.<br>
     * After that, all data will be stored to disk automatically.
     * @param position in product lists.
     */
    static void removeProductAt(int position);
protected:
    static const int FIELD_COUNT = 2;
    //static const int HEADER = 0;
    static const int AUTO_INCREASE_NUMBER = 0;
    static const int ARRAY_OF_PRODUCTS = 1;



    virtual unsigned int getFieldCount() const override {
        return FIELD_COUNT;
    }

    virtual DataType getFieldType(int &fieldIndex) const override;

    virtual ModelBase *createVectorItem() override {
        return &(new Product())->initialize();
    }

    vector<ModelBase *> *getProductList() {
        return ModelBase::operator[](ARRAY_OF_PRODUCTS);
    };

    int increaseUniqueIndex();

    /**
     * Save product list to ITEM_DB_FILE file. <br>
     * Include hash sum to make sure nobody touch this file outside the program.
     */
    void saveChange();
};


#endif //CPPASSIGNMENT_PRODUCTMANAGER_HPP
