//
// Created by blackcat on 10/06/2016.
//

#include "OrderManager.hpp"
#include "../utils/Utils.hpp"
#include "ProductManager.hpp"

OrderManager *OrderManager::sInstance = nullptr;

OrderManager &OrderManager::initialize() {
    ModelBase::initialize();
    return *this;
}

OrderManager *OrderManager::getInstance() {
    if (sInstance)
        return sInstance;
    try {
        sInstance = Utils::deserialize<OrderManager>(ORDER_DB_FILE, ORDER_DB_FILE_HEADER);
    } catch (const char *e) {
        printf("Error while reading file %s: %s\n", ORDER_DB_FILE.c_str(), e);
        printf("Do you want to continue process and override file %s with empty data (y/n)? ", ORDER_DB_FILE.c_str());
        if (Utils::yesOrNo()) {
            /* Write default data (empty) */
            sInstance = &(new OrderManager())->initialize();
            sInstance->saveChange();
        } else
            exit(0);
    }
    return sInstance;
}

unsigned int OrderManager::getFieldCount() const {
    return FIELD_COUNT;
}

DataType OrderManager::getFieldType(int &fieldIndex) const {
    switch (fieldIndex) {
        case AUTO_INCREASE_NUMBER:
            return TYPE_INTEGER;
        case ARRAY_OF_ORDERS:
            return TYPE_ARRAY_OF_MODELS;
        default:
            assert(false);
    }
}

ModelBase *OrderManager::createVectorItem() {
    return &(new Order())->initialize();
}

Object &OrderManager::operator[](size_t index) const {
    return ModelBase::operator[](index);
}

vector<ModelBase *> *OrderManager::getOrderList() {
    return (*this)[ARRAY_OF_ORDERS];
}

int OrderManager::increaseUniqueIndex() {
    int currentIndex = (*this)[AUTO_INCREASE_NUMBER];
    return (*this)[AUTO_INCREASE_NUMBER] = ++currentIndex;
}

void OrderManager::saveChange() {
    Utils::serialize(*this, ORDER_DB_FILE, ORDER_DB_FILE_HEADER,
                     "Warning: All orders request will be lost after close the program");
}

unsigned long OrderManager::getOrdersCount() {
    return getInstance()->getOrderList()->size();
}

void OrderManager::setStatusSoldAnOrder(int orderId, int orderPosition) {
    if (orderPosition == -1)
        orderPosition = findOrderPosition(orderId);
    if (orderPosition >= 0) {
        Order *order = (Order *) (*getInstance()->getOrderList())[orderPosition];
        int productPosition;
        if ((productPosition = ProductManager::findProduct(order->getProductId())) >
            -1) { /* Check if product ID valid */
            order->setStatus(STATUS_SOLD);                                                  /* Set status sold */
            Product product = ProductManager::getProductAt(productPosition);
            ProductManager::updateProduct(productPosition,
                                          product.changeItemCount(
                                                  -1 * order->getNumber())); /* Decrease number of available products */
            order->setAmountMoney(
                    product.getPrice() * (order->getNumber()));          /* Set amount money of this order*/
            getInstance()->saveChange(); /* Save changes to disk */
        }
    }
}

signed OrderManager::findOrderPosition(int orderId) {
    for (int i = 0; i < getOrdersCount(); ++i)
        if (getOrderAt(i).getOrderId() == orderId)
            return i;
    return -1;
}

Order OrderManager::getOrderAt(int position) {
    return *(Order *) ((*getInstance()->getOrderList())[position]);
}

void OrderManager::setStatusCanceledAnOrder(int orderId, int orderPosition) {
    if (orderPosition == -1)
        orderPosition = findOrderPosition(orderId);
    if (orderPosition >= 0) {
        Order *order = (Order *) (*getInstance()->getOrderList())[orderPosition];
        order->setStatus(STATUS_CANCELED);
        getInstance()->saveChange(); /* Save changes to disk */
    }
}

void OrderManager::updateOrderAt(int position, Order order) {
    *(*getInstance()->getOrderList())[position] = order;
    getInstance()->saveChange();
}
