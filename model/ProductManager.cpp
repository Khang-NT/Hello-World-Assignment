//
// Created by blackcat on 09/06/2016.
//

#include "ProductManager.hpp"

ProductManager *ProductManager::sInstance = nullptr;

ProductManager *ProductManager::getInstance() {
    if (sInstance)
        return sInstance;
    try {
        sInstance = Utils::deserialize<ProductManager>(ITEM_DB_FILE, ITEM_DB_FILE_HEADER);
    } catch (const char *e) {
        printf("Error while reading file %s: %s\n", ITEM_DB_FILE.c_str(), e);
        printf("Do you want to continue process and override file %s with empty data (y/n)? ", ITEM_DB_FILE.c_str());
        if (Utils::yesOrNo()) {
            /* Write default data (empty) */
            sInstance = &(new ProductManager())->initialize();
            sInstance->saveChange();
        } else
            exit(0);
    }
    assert(sInstance);
    return sInstance;
}

ProductManager &ProductManager::initialize() {
    ModelBase::initialize();
    //ModelBase::operator[](HEADER) = "MT2015-Shop";
    return *this;
}

int ProductManager::findProduct(int productId) {
    vector<ModelBase *> productList = *getInstance()->getProductList();
    for (int i = 0; i < productList.size(); ++i)
        if (((Product *) productList[i])->match(productId))
            return i;
    return -1;
}

Product ProductManager::addProduct(string name, string manufacturer,
                                   string category, int price, string warrantyInfo, int count) {
    ProductManager *productManager = getInstance();
    Product *product = &(new Product())->initialize(
            productManager->increaseUniqueIndex(),
            name, manufacturer, category, price,
            warrantyInfo, count
    );
    productManager->getProductList()->push_back(product);
    productManager->saveChange();
    return *product;
}

void ProductManager::updateProduct(int position, Product newData) {
    ProductManager *manager = getInstance();
    *(*manager->getProductList())[position] = newData;
    manager->saveChange();
}

void ProductManager::removeProductAt(int position) {
    *getInstance()->getProductList()[position].erase
            (getInstance()->getProductList()->begin() + position);
    getInstance()->saveChange();
}

DataType ProductManager::getFieldType(int &fieldIndex) const {
    switch (fieldIndex) {
        //case HEADER:
        //return TYPE_STRING;
        case AUTO_INCREASE_NUMBER:
            return TYPE_INTEGER;
        case ARRAY_OF_PRODUCTS:
            return TYPE_ARRAY_OF_MODELS;
        default:
            assert(false);
    }
}

int ProductManager::increaseUniqueIndex() {
    int currentIndex = (*this)[AUTO_INCREASE_NUMBER];
    return (*this)[AUTO_INCREASE_NUMBER] = ++currentIndex;
}

unsigned ProductManager::getProductCount() {
    return (unsigned) getInstance()->getProductList()->size();
}

Product ProductManager::getProductAt(int position) {
    return *static_cast<Product *>((*getInstance()->getProductList())[position]);
}

unsigned int ProductManager::getFieldCount() const {
    return FIELD_COUNT;
}

ModelBase *ProductManager::createVectorItem() {
    return &(new Product())->initialize();
}

vector<ModelBase *> *ProductManager::getProductList() {
    return (*this)[ARRAY_OF_PRODUCTS];
}

Object &ProductManager::operator[](size_t index) const {
    return ModelBase::operator[](index);
}

void ProductManager::saveChange() {
    Utils::serialize(*this, ITEM_DB_FILE, ITEM_DB_FILE_HEADER,
                     "Warning: All products information will be lost after closed program");
}
