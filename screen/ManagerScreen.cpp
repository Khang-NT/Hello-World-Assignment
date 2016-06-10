//
// Created by blackcat on 08/06/2016.
//

#include "ManagerScreen.hpp"
#include "../utils/ExportHTML.hpp"
#include "../model/ProductManager.hpp"
#include "../model/OrderManager.hpp"
#include "../utils/DateTimeFormat.hpp"

namespace ManagerScreen {

    void openItemListSnapshot() {
        ExportHTML::exportProductList();
    }

    void promptOpenProductListSnapshot(const char *why) {
        printf("%sDo you want open Items list Snapshot (Y/N)? ", why);
        if (Utils::yesOrNo()) {
            openItemListSnapshot();
        }
    }

    void addNewItem() {
        string name, category, manufacturer, warrantyInfo;
        int price, count;
        printf("Product name: ");
        Utils::getLine(cin, name);
        printf("Category: ");
        Utils::getLine(cin, category);
        printf("Manufacturer: ");
        Utils::getLine(cin, manufacturer);
        printf("Warranty information: ");
        Utils::getLine(cin, warrantyInfo);
        printf("Price ($): ");
        do {
            cin.clear();
            cin >> price;
        } while (cin.fail());
        printf("Count: ");
        do {
            cin.clear();
            cin >> count;
        } while (cin.fail());
        printf("Review:\n");
        printf("%-20s: %s\n", "Product name", name.c_str());
        printf("%-20s: %s\n", "Category", category.c_str());
        printf("%-20s: %s\n", "Manufacturer", manufacturer.c_str());
        printf("%-20s: %s\n", "Warranty info", warrantyInfo.c_str());
        printf("%-20s: %d$\n", "Price", price);
        printf("%-20s: %d item\n", "Available", count);
        cin.clear();
        cin.ignore(1024, '\n');
        printf("Are you sure (y/n)? ");
        if (Utils::yesOrNo()) {
            ProductManager::addProduct(name, manufacturer, category, price, warrantyInfo, count);
            printf("Done. ");
            Utils::pause();
        }
    }

    void editProduct(int productPosition, int field) {
        string *newStringValue = new string;
        int *newIntValue = new int;
        printf("New value: ");
        switch (field) {
            case 0: /* Name */
            case 1: /* Category */
            case 3: /* Manufacturer */
            case 4: /* Warranty */
                Utils::getLine(cin, *newStringValue);
                break;
            default: /* Price, items available */
                do {
                    cin.clear();
                    cin >> *newIntValue;
                } while (cin.fail());
                break;
        }
        Product product = ProductManager::getProductAt(productPosition);
        if (field == 0)                                 /* Name */
            product.setProductName(*newStringValue);
        else if (field == 1)                            /* Category */
            product.setCategory(*newStringValue);
        else if (field == 2)                            /* Manufacturer */
            product.setManufacturer(*newStringValue);
        else if (field == 3)                            /* Warranty */
            product.setWarranty(*newStringValue);
        else if (field == 4)                            /* Price */
            product.setPrice(*newIntValue);
        else                                            /* Items available */
            product.setItemCount(*newIntValue);

        ProductManager::updateProduct(productPosition, product);

        delete newIntValue;
        delete newStringValue;
    }

    void editAnItem() {
        promptOpenProductListSnapshot("You need to know Product ID to use this function.\n");
        int id, productPosition = -1;
        while (productPosition == -1) {
            printf("Product ID: ");
            do {
                cin.clear();
                cin >> id;
            } while (cin.fail());

            productPosition = ProductManager::findProduct(id);
            if (productPosition == -1) {
                printf("Product ID invalid.\n");
                printf("Retry (y/n)? "); /* Let user retry */
                if (!Utils::yesOrNo())
                    return;
            }
        }
        MenuHelper *menuHelper = new MenuHelper();
        do {
            Product product = ProductManager::getProductAt(productPosition);
            menuHelper->setCaptions("Update product with ID: " + to_string(product.getProductId()),
                                    MenuHelper::GO_BACK_CAPTION)
                    ->clear()
                    ->addItem("Name (" + product.getProductName() + ")", editProduct, productPosition)
                    ->addItem("Category (" + product.getCategory() + ")", editProduct, productPosition)
                    ->addItem("Manufacturer (" + product.getManufacturer() + ")", editProduct, productPosition)
                    ->addItem("Warranty info (" + product.getWarrantyInfo() + ")", editProduct, productPosition)
                    ->addItem("Price (" + to_string(product.getPrice()) + "$)", editProduct, productPosition)
                    ->addItem("Available (" + to_string(product.getItemCount()) + ")", editProduct, productPosition);

        } while (menuHelper->run(false)); /* While NOT select go back */


        delete menuHelper;
    }

    void removeAnItem() {
        promptOpenProductListSnapshot("You need to know Product ID to use this function.\n");
        int id, productPosition = -1;
        while (productPosition == -1) {
            printf("Product ID: ");
            do {
                cin.clear();
                cin >> id;
            } while (cin.fail());

            productPosition = ProductManager::findProduct(id);
            if (productPosition == -1) {
                printf("Product ID invalid.\n");
                printf("Retry (y/n)? "); /* Let user retry */
                if (!Utils::yesOrNo())
                    return;
            }
        }
        Product product = ProductManager::getProductAt(productPosition);
        printf("Remove product:\n");
        printf("%-20s: %d\n", "ID", product.getProductId());
        printf("%-20s: %s\n", "Product name", product.getProductName().c_str());
        printf("%-20s: %s\n", "Category", product.getCategory().c_str());
        printf("%-20s: %s\n", "Manufacturer", product.getManufacturer().c_str());
        printf("%-20s: %s\n", "Warranty info", product.getWarrantyInfo().c_str());
        printf("%-20s: %d$\n", "Price", product.getPrice());
        printf("%-20s: %d item(s)\n", "Available", product.getItemCount());

        printf("Are you sure (y/n)? ");
        if (Utils::yesOrNo()) {
            ProductManager::removeProductAt(productPosition);
            printf("Done. ");
            Utils::pause();
        }
    }

    void simpleStatistic() {
        printf("Number of kind of products : %d\n", ProductManager::getProductCount());
        int totalValue = 0;
        for (int i = 0; i < ProductManager::getProductCount(); ++i) {
            Product product = ProductManager::getProductAt(i);
            totalValue += product.getPrice() * product.getItemCount();
        }
        printf("Total value                : %d$\n", totalValue);
        int earnings = 0, wasSold = 0;
        for (int j = 0; j < OrderManager::getOrdersCount(); ++j) {
            if (OrderManager::getOrderAt(j).getStatus() == STATUS_SOLD) {
                Order order = OrderManager::getOrderAt(j);
                wasSold += order.getNumber();
                earnings += order.getAmountMoney();
            }
        }
        printf("Items were sold            : %d\n", wasSold);
        printf("Earnings                   : %d$\n", earnings);
        cin.ignore();
        Utils::pause();
    }

    void handleOrder(int orderPosition, int temp = 0) {
        Order order = OrderManager::getOrderAt(orderPosition);
        int productPosition = ProductManager::findProduct(order.getProductId());
        if (productPosition >= 0) {
            Product product = ProductManager::getProductAt(productPosition);
            printf("%-25s: %s\n", "Time",
                   DateTimeFormat::format(order.getTimeMakeOrder(), "dd/MM/yyyy HH:mm.ss").c_str());
            printf("%-25s: %s\n", "Product", product.getProductName().c_str());
            printf("%-25s: %d item(s)\n", "Available", product.getItemCount());
            printf("%-25s: %d item(s)\n", "Number of items ordered", order.getNumber());
            printf("%-25s: %s\n", "Customer name", order.getCustomerName().c_str());
            printf("%-25s: %s\n", "Customer phone", order.getCustomerPhone().c_str());
            printf("%-25s: %s\n", "Customer address", order.getCustomerAddress().c_str());
            printf("%-25s: %s\n", "Customer addition info", order.getCustomerAdditionInfo().c_str());
            if (product.getItemCount() >= order.getNumber()) {
                printf("Update status \"SOLD\" for this order (y/n)? ");
                if (Utils::yesOrNo())
                    OrderManager::setStatusSoldAnOrder(order.getOrderId(), orderPosition);
            } else {
                printf("Available products not enough for this order.\n"
                               "Do you want to cancel this order (y/n)? ");
                if (Utils::yesOrNo())
                    OrderManager::setStatusCanceledAnOrder(order.getOrderId(), orderPosition);
                else if (product.getItemCount() > 0) {
                    printf("Do you want to change number items of this order to %d (y/n)? ", product.getItemCount());
                    if (Utils::yesOrNo()) {
                        order.setNumber(product.getItemCount());
                        OrderManager::updateOrderAt(orderPosition, order);
                        printf("Do you want to update status \"SOLD\" for this order (y/n)? ");
                        if (Utils::yesOrNo())
                            OrderManager::setStatusSoldAnOrder(order.getOrderId(), orderPosition);
                    }
                }
            }
        } else {
            printf("Product ordered didn't exist.\n"
                           "Do you want to cancel this order (y/n)? ");
            if (Utils::yesOrNo())
                OrderManager::setStatusCanceledAnOrder(order.getOrderId(), orderPosition);
        }

    }

    void handlePendingOrders() {
        MenuHelper *menuHelper = new MenuHelper();
        do {
            printf("Loading orders...");
            menuHelper->clear();
            int pendingOrderCount = 0;
            for (int i = 0; i < OrderManager::getOrdersCount(); ++i)
                if (OrderManager::getOrderAt(i).getStatus() == STATUS_PENDING) {
                    pendingOrderCount++;
                    Order order = OrderManager::getOrderAt(i);
                    int productPosition = ProductManager::findProduct(order.getProductId());
                    if (productPosition >= 0) {
                        Product product = ProductManager::getProductAt(productPosition);
                        menuHelper->addItem(
                                product.getProductName() + " x " + to_string(order.getNumber()),
                                handleOrder, i
                        );
                    } else
                        menuHelper->addItem(
                                "Unknown product x " + to_string(order.getNumber()), handleOrder, i
                        );
                }
            if (pendingOrderCount == 0) {
                printf("\nNo pending order was found.");
                Utils::pause();
                break;
            } else
                menuHelper->setCaptions("PENDING ORDERS - " + to_string(pendingOrderCount),
                                        MenuHelper::GO_BACK_CAPTION);


        } while (menuHelper->run(false));
        delete menuHelper;
    }


    void start(string exitCaption) {
        MenuHelper *managerMenu = (new MenuHelper("Manager Control Panel", exitCaption))
                ->addItem("Add new item", addNewItem)
                ->addItem("Edit an item", editAnItem)
                ->addItem("Remove an item", removeAnItem)
                ->addItem("Handle pending orders", handlePendingOrders)
                ->addItem("Print statistic", simpleStatistic)
                ->addItem("Open Item list snapshot", openItemListSnapshot);
        managerMenu->run(true);
    }
};