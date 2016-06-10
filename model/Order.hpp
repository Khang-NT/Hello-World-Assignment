//
// Created by blackcat on 10/06/2016.
//

#ifndef CPPASSIGNMENT_ORDER_HPP
#define CPPASSIGNMENT_ORDER_HPP


#include <assert.h>
#include "ModelBase.hpp"


const static int STATUS_PENDING = 0;
const static int STATUS_SOLD = 1;
const static int STATUS_CANCELED = 2;

class Order : public ModelBase {

public:
    Order() : ModelBase() {}

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (Account&) reference itself.
     */
    Order &initialize() override;

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (Account&) reference itself.
     */
    Order &initialize(int orderId, int productId, int number, string customerName, string customerAddress,
                      string customerPhone, string customerAdditionInfo, int status = STATUS_PENDING);

    /* set / get */

    int getOrderId() const;

    Order &setOrderId(int orderId);

    int getProductId() const;

    Order &setProductId(int productId);

    int getNumber() const;

    Order &setNumber(int number);

    int getTimeMakeOrder() const;

    Order &setTimeMakeOrder(int timeMakeOrder);

    const string getCustomerName() const;

    Order &setCustomerName(const string &customerName);

    const string getCustomerPhone() const;

    Order &setCustomerPhone(const string &customerPhone);

    const string getCustomerAddress() const;

    Order &setCustomerAddress(const string &customerAddress);

    const string getCustomerAdditionInfo() const;

    Order &setCustomerAdditionInfo(const string &customerAdditionInfo);

    /**
     * @See STATUS_PENDING, STATUS_SOLD, STATUS_CANCELED
     * @return order status.
     */
    int getStatus();

    /**
     * @See STATUS_PENDING, STATUS_SOLD, STATUS_CANCELED
     * @param status (int) one of (STATUS_PENDING, STATUS_SOLD, STATUS_CANCELED)
     * @return (Order &) reference itself.
     */
    Order &setStatus(int status);

    int getAmountMoney();

    /**
     * Set amount money after sold.
     * @param v amount money of this order.
     * @return  (Order &) reference itself.
     */
    Order &setAmountMoney(int v);

protected:
    /* Constants */
    static const int FIELD_COUNT = 10;
    static const int ORDER_ID = 0;
    static const int PRODUCT_ID = 1;
    static const int NUMBER = 2;
    static const int CUSTOMER_NAME = 3;
    static const int CUSTOMER_PHONE = 4;
    static const int CUSTOMER_ADDRESS = 5;
    static const int CUSTOMER_ADDITION_INFO = 6;
    static const int TIME_MAKE_ORDER = 7;
    static const int STATUS = 8;
    static const int AMOUNT = 9;

    /* Override base funcs */
    virtual unsigned int getFieldCount() const override;

    virtual DataType getFieldType(int &fieldIndex) const override;

    /* Make protected base's method */
    virtual Object &operator[](size_t index) const override;

};


#endif //CPPASSIGNMENT_ORDER_HPP
