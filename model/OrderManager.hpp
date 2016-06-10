//
// Created by blackcat on 10/06/2016.
//

#ifndef CPPASSIGNMENT_ORDERMANAGER_HPP
#define CPPASSIGNMENT_ORDERMANAGER_HPP


#include <assert.h>
#include "ModelBase.hpp"
#include "Order.hpp"

const string ORDER_DB_FILE = "OrdersDB.dat";
const string ORDER_DB_FILE_HEADER = "MT2015-Orders";

class OrderManager : public ModelBase {
private:
    /**
     * Singleton instance.
     */
    static OrderManager *sInstance;
public:

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (Account&) reference itself.
     */
    OrderManager &initialize() override;

    /**
     * Get singleton instance. <br>
     * If it wasn't created, do initialization with default data (empty).
     * @return (OrderManager *) singleton instance of OrderManager.
     */
    static OrderManager *getInstance();

    /**
     * Get number of orders in queue.
     * @return (int) number of orders in queue.
     */
    static unsigned long getOrdersCount();

    /**
     * Find order position in list by order ID
     * @param orderId order ID
     * @return position of order matches with orderID or -1 if not found.
     */
    static int findOrderPosition(int orderId);

    /**
     * Get a COPY of Order instance at position.
     * @param position position
     * @return a COPY of Order instance at position.
     */
    static Order getOrderAt(int position);

    /**
     * Add order to list and generate its unique ID.
     * @param order (Order) order of customer
     * @return (OrderManager &) reference itself.
     */
    static OrderManager &addOrder(int productId, int number, string customerName,
                                  string customerPhoneNo, string customerAddress, string customerAdditionInfo) {
        OrderManager *orderManager = getInstance();
        Order *order = &(new Order())->initialize(
                orderManager->increaseUniqueIndex(),
                productId, number,
                customerName, customerAddress, customerPhoneNo, customerAdditionInfo
        );
        orderManager->getOrderList()->push_back(order);
        orderManager->saveChange();
    }

    /**
     * Set status STATUS_SOLD for order with orderId. <br>
     * If orderPosition == -1, using orderId to find orderPosition.
     * @warning Order's number must &les; available products.
     * @param orderId Order ID
     * @param orderPosition order position in list.
     */
    static void setStatusSoldAnOrder(int orderId, int orderPosition = -1);

    /**
     * Set status STATUS_CANCELED for order with orderID. <br>
     * If orderPosition == -1, using orderId to find orderPosition.
     * @param orderId Order ID
     * @param orderPosition order position in list.
     */
    static void setStatusCanceledAnOrder(int orderId, int orderPosition = -1);

    /**
     * Override order at position with newData
     * @param position position in list.
     * @param newData new Order data
     */
    static void updateOrderAt(int position, Order newData);

protected:
    static const int FIELD_COUNT = 2;
    static const int AUTO_INCREASE_NUMBER = 0;
    static const int ARRAY_OF_ORDERS = 1;

    /* Override base funcs */
    virtual unsigned int getFieldCount() const override;

    virtual DataType getFieldType(int &fieldIndex) const override;

    virtual ModelBase *createVectorItem() override;

    /* Make protected base's method */
    virtual Object &operator[](size_t index) const override;

    vector<ModelBase *> *getOrderList();;

    int increaseUniqueIndex();

    /**
     * Save order list to ORDER_DB_FILE file. <br>
     * Include hash sum to make sure nobody touch this file outside the program.
     */
    void saveChange();
};


#endif //CPPASSIGNMENT_ORDERMANAGER_HPP
