//
// Created by blackcat on 08/06/2016.
//

#include "ManagerScreen.hpp"
#include "../utils/ExportHTML.hpp"
#include "../model/ProductManager.hpp"

namespace ManagerScreen {

    void openItemListSnapshot() {
        ExportHTML::exportProductList();
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
        cin >> price;
        printf("Count: ");
        cin >> count;
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

    void editAnItem() {

    }

    void removeAnItem() {

    }


    void start(string exitCaption) {
        MenuHelper *managerMenu = (new MenuHelper("Manager Control Panel", exitCaption))
                ->addItem("Add new item", addNewItem)
                ->addItem("Edit an item", editAnItem)
                ->addItem("Remove an item", removeAnItem)
                ->addItem("Open Item list snapshot", openItemListSnapshot);
        managerMenu->run(true);
    }
};