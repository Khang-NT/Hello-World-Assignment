//
// Created by dell on 6/10/2016.
//

#ifndef CPPASSIGNMENT_ORDERMANAGER_HPP
#define CPPASSIGNMENT_ORDERMANAGER_HPP


#include <cassert>
#include "ModelBase.hpp"
#include "Order.hpp"

class OrderManager : public ModelBase {


    void addNewOrder(int productId, string guestName);

protected:
    static const int FIELD_COUNT = 2;
    static const int UNIQUE_ID = 0;
    static const int ORDER_LIST = 1;

    virtual unsigned int getFieldCount() const override {
        return FIELD_COUNT;
    }

    virtual DataType getFieldType(int &fieldIndex) const override {
        switch (fieldIndex) {
            case UNIQUE_ID:
                return TYPE_INTEGER;
            case ORDER_LIST:
                return TYPE_ARRAY_OF_MODELS;
            default:
                assert(false);
        }
    }

    vector<ModelBase *> *getOrderList() {
        return (*this)[ORDER_LIST];
    }

    virtual ModelBase *createVectorItem();
};


#endif //CPPASSIGNMENT_ORDERMANAGER_HPP
