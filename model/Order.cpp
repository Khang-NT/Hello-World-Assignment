//
// Created by dell on 6/10/2016.
//


#include "Order.hpp"

ModelBase &Order::initialize() {
    return ModelBase::initialize();
}

void Order::setOrderId(int orderId) {
    (*this)[ORDER_ID] = orderId;
}

int Order::getOrderId() {
    return (*this)[ORDER_ID];
}

void Order::setGuestName(string name) {
    (*this)[NAME] = name;
}



