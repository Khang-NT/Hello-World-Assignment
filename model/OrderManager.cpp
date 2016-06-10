//
// Created by dell on 6/10/2016.
//

#include "OrderManager.hpp"

ModelBase virtual *OrderManager::createVectorItem() {
    return &(new Order())->initialize();
}

void OrderManager::addNewOrder(int productId, string guestName) {
    Order *order = new Order;
    order->initialize();
    order->setGuestName(guestName);
    //...

    getOrderList()->push_back(order);
}



