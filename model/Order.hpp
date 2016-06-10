//
// Created by dell on 6/10/2016.
//

#ifndef CPPASSIGNMENT_ORDER_HPP
#define CPPASSIGNMENT_ORDER_HPP


#include "ModelBase.hpp"

class Order : public ModelBase {

public:
    Order() : ModelBase() { }

    virtual ModelBase &initialize();

    void setOrderId(int orderId);

    int getOrderId();

    void setGuestName(string name);

protected:
    static const int FIELD_COUNT = 3;
    static const int ORDER_ID = 0;
    static const int PRODUCT_ID = 1;
    static const int NAME = 2;

    virtual unsigned int getFieldCount() const override {
        return FIELD_COUNT;
    }

    virtual DataType getFieldType(int &fieldIndex) const override {
        switch (fieldIndex) {
            case ORDER_ID:
            case PRODUCT_ID:
                return TYPE_INTEGER;
            case NAME:
                return TYPE_STRING;
        }
    }

};


#endif
 //CPPASSIGNMENT_ORDER_HPP
