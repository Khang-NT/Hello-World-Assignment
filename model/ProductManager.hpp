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

/**
 * Inherit class ModelBase. <br>
 * This class provides feature managing products (count, search, add, update).
 * @see class ModelBase
 * @see class Product
 */
class ProductManager : public ModelBase {
public:
    ProductManager() : ModelBase() {}

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (ProductManager&) reference itself.
     */
    ProductManager &initialize() override {
        ModelBase::initialize();
        ModelBase::operator[](HEADER) = "MT2015-Shop";
        return *this;
    }

    /**
     * Get singleton instance. <br>
     * If it wasn't created, do initialization with default data (include admin account).
     * @return (AccountManager &) singleton instance of AccountManager.
     */
    static ProductManager &getInstance() {
        if (sInstance)
            return *sInstance;
        else {
            try {
                sInstance = Utils::deserialize<ProductManager>(ITEM_DB_FILE);
            } catch (const char *e) {
                printf("Error while reading file %s: %s\n", ITEM_DB_FILE, e);
                printf("Do you want to continue process and override file %s with empty data (y/n)? ");
                if (Utils::yesOrNo()) {
                    /* Write default data */
                    sInstance = &(new ProductManager())->initialize();
                    sInstance->saveChange();
                } else
                    exit(0);
            }
        }
    }

    /**
     * Get number of existing products.
     * @return (unsigned) number of existing products.
     */
    static unsigned getProductCount() {
        return (unsigned) getInstance().getProductList()->size();
    }

    /**
     * Get a COPY of product object at given position.
     * @param position (int)
     * @return (Product) a COPY of product object at position.
     */
    static Product getProductAt(int position) {
        return *static_cast<Product *>((*getInstance().getProductList())[position]);
    }

    /**
     * Find product by given ID.
     * @param productId product's id.
     * @return position of product matches given ID or -1 if not found.
     */
    static int findProduct(int productId) {
        vector<ModelBase *> productList = *getInstance().getProductList();
        for (int i = 0; i < productList.size(); ++i)
            if (((Product *) productList[i])->match(productId))
                return i;
        return -1;
    }

    /**
     * Add product.
     * @param name
     * @param manufacturer
     * @param category
     * @param price
     * @param warrantyDays
     * @param count
     * @return Copy of new product object.
     */
    static Product addProduct(string name, string manufacturer, string category, int price, int warrantyDays,
                        int count = 0) {
        ProductManager productManager = getInstance();
        Product *product = &(new Product())->initialize(
                productManager.increaseUniqueIndex(),
                name, manufacturer, category, price,
                warrantyDays, count
        );
        productManager.getProductList()->push_back(product);
        return *product;
    }

    /**
     * Replace product at position with newData. <br>
     * After that, all data will be stored to disk automatically.
     * @param position (int)
     * @param newData (Product)
     */
    static void updateProduct(int position, Product newData) {
        ProductManager manager = getInstance();
        *(*manager.getProductList())[position] = newData;
        manager.saveChange();
    }
protected:
    static const int FIELD_COUNT = 3;
    static const int HEADER = 0;
    static const int AUTO_INCREASE_NUMBER = 1;
    static const int ARRAY_OF_PRODUCTS = 2;

    /**
     * Singleton instance.
     */
    static ProductManager *sInstance;

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

    void saveChange() {
        try {
            Utils::serialize(*this, ITEM_DB_FILE);
        } catch (const char *e) {
            cout << "Update file " << ITEM_DB_FILE << " error: " << e << endl;
            cout << "Warning: All changes will be aborted after closed program?\n"
                    "Do you want to retry (y/n)? ";
            if (Utils::yesOrNo())
                saveChange();
        }
    }
};


#endif //CPPASSIGNMENT_PRODUCTMANAGER_HPP
