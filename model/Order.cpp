//
// Created by blackcat on 10/06/2016.
//


#include "Order.hpp"
#include <time.h>

Order &Order::initialize() {
    ModelBase::initialize();
    return *this;
}

Order &Order::initialize(int orderId, int productId, int number, string customerName, string customerAddress,
                         string customerPhone, string customerAdditionInfo, int status) {
    ModelBase::initialize();
    return setOrderId(orderId)
            .setProductId(productId)
            .setNumber(number)
            .setCustomerName(customerName)
            .setCustomerAddress(customerAddress)
            .setCustomerPhone(customerPhone)
            .setCustomerAdditionInfo(customerAdditionInfo)
            .setStatus(status)
            .setTimeMakeOrder((int) time(0));
}

unsigned int Order::getFieldCount() const {
    return FIELD_COUNT;
}

DataType Order::getFieldType(int &fieldIndex) const {
    switch (fieldIndex) {
        case ORDER_ID:
        case PRODUCT_ID:
        case NUMBER:
        case TIME_MAKE_ORDER:
        case STATUS:
        case AMOUNT:
            return TYPE_INTEGER;
        case CUSTOMER_ADDITION_INFO:
        case CUSTOMER_ADDRESS:
        case CUSTOMER_NAME:
        case CUSTOMER_PHONE:
            return TYPE_STRING;
        default:
            assert(false);
    }
}

int Order::getOrderId() const {
    return (*this)[ORDER_ID];
}

Order &Order::setOrderId(int orderId) {
    (*this)[ORDER_ID] = orderId;
    return *this;
}

int Order::getProductId() const {
    return (*this)[PRODUCT_ID];
}

Order &Order::setProductId(int productId) {
    (*this)[PRODUCT_ID] = productId;
    return *this;
}

int Order::getNumber() const {
    return (*this)[NUMBER];
}

Order &Order::setNumber(int number) {
    (*this)[NUMBER] = number;
    return *this;
}

int Order::getTimeMakeOrder() const {
    return (*this)[TIME_MAKE_ORDER];
}

Order &Order::setTimeMakeOrder(int timeMakeOrder) {
    (*this)[TIME_MAKE_ORDER] = timeMakeOrder;
    return *this;
}

const string Order::getCustomerName() const {
    return (*this)[CUSTOMER_NAME];
}

Order &Order::setCustomerName(const string &customerName) {
    (*this)[CUSTOMER_NAME] = customerName;
    return *this;
}

const string Order::getCustomerPhone() const {
    return (*this)[CUSTOMER_PHONE];
}

Order &Order::setCustomerPhone(const string &customerPhone) {
    (*this)[CUSTOMER_PHONE] = customerPhone;
    return *this;
}

const string Order::getCustomerAddress() const {
    return (*this)[CUSTOMER_ADDRESS];
}

Order &Order::setCustomerAddress(const string &customerAddress) {
    (*this)[CUSTOMER_ADDRESS] = customerAddress;
    return *this;
}

const string Order::getCustomerAdditionInfo() const {
    return (*this)[CUSTOMER_ADDITION_INFO];
}

Order &Order::setCustomerAdditionInfo(const string &customerAdditionInfo) {
    (*this)[CUSTOMER_ADDITION_INFO] = customerAdditionInfo;
    return *this;
}

Object &Order::operator[](size_t index) const {
    return ModelBase::operator[](index);
}

int Order::getStatus() {
    return (*this)[STATUS];
}

Order &Order::setStatus(int status) {
    (*this)[STATUS] = status;
    return *this;
}

int Order::getAmountMoney() {
    return (*this)[AMOUNT];
}

Order &Order::setAmountMoney(int v) {
    (*this)[AMOUNT] = v;
    return *this;
}




