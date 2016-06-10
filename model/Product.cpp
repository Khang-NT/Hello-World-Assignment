//
// Created by blackcat on 10/06/2016.
//

#include "Product.hpp"

Product &Product::initialize() {
    ModelBase::initialize();
    return *this;
}

Product &Product::initialize(int produceId, string name, string manufacturer,
                             string category, int price, string warrantyInfo, int count) {
    ModelBase::initialize();
    setProductId(produceId)
            .setProductName(name)
            .setManufacturer(manufacturer)
            .setCategory(category)
            .setPrice(price)
            .setWarranty(warrantyInfo)
            .setItemCount(count);
    return *this;
}

bool Product::match(int id) {
    return getProductId() == id;
}

Product &Product::setProductId(int id) {
    (*this)[ID] = id;
    (*this)[LAST_MODIFIED] = time(nullptr);
    return *this;
}

Product &Product::setProductName(string name) {
    (*this)[NAME] = name;
    (*this)[LAST_MODIFIED] = time(nullptr);
    return *this;
}

Product &Product::setManufacturer(string manufacturer) {
    (*this)[MANUFACTURER] = manufacturer;
    (*this)[LAST_MODIFIED] = time(nullptr);
    return *this;
}

Product &Product::setCategory(string category) {
    (*this)[CATEGORY] = category;
    (*this)[LAST_MODIFIED] = time(nullptr);
    return *this;
}

Product &Product::setPrice(int price) {
    (*this)[PRICE] = price;
    (*this)[LAST_MODIFIED] = time(nullptr);
    return *this;
}

Product &Product::setWarranty(string warrantyInfo) {
    (*this)[WARRANTY_INFO] = warrantyInfo;
    (*this)[LAST_MODIFIED] = time(nullptr);
    return *this;
}

Product &Product::setItemCount(int count) {
    (*this)[ITEM_COUNT] = count;
    (*this)[LAST_MODIFIED] = time(nullptr);
    return *this;
}

Product &Product::changeItemCount(int offset) {
    return setItemCount(getItemCount() + offset);
}

int Product::getProductId() {
    return (*this)[ID];
}

string Product::getProductName() {
    return (*this)[NAME];
}

int Product::getPrice() {
    return (*this)[PRICE];
}

string Product::getWarrantyInfo() {
    return (*this)[WARRANTY_INFO];
}

string Product::getManufacturer() {
    return (*this)[MANUFACTURER];
}

string Product::getCategory() {
    return (*this)[CATEGORY];
}

int Product::getItemCount() {
    return (*this)[ITEM_COUNT];
}

int Product::getLastModifiedTime() {
    return (*this)[LAST_MODIFIED];
}

unsigned int Product::getFieldCount() const {
    return FIELD_COUNT;
}

DataType Product::getFieldType(int &fieldIndex) const {
    switch (fieldIndex) {
        case ID:
        case PRICE:
        case ITEM_COUNT:
        case LAST_MODIFIED:
            return TYPE_INTEGER;
        case NAME:
        case MANUFACTURER:
        case CATEGORY:
        case WARRANTY_INFO:
            return TYPE_STRING;
        default:
            assert(false);
    }
}

Object &Product::operator[](size_t index) const {
    return ModelBase::operator[](index);
}
