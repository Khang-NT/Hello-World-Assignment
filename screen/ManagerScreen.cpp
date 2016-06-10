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
        cin.clear();
        do {
            cin >> price;
        } while (cin.fail());
        printf("Count: ");
        cin.clear();
        do {
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
                cin.clear();
                do {
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
            cin.clear();
            do {
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
            cin.clear();
            do {
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
        printf("%-20s: %d item\n", "Available", product.getItemCount());

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
        Utils::pause();
    }


    void start(string exitCaption) {
        MenuHelper *managerMenu = (new MenuHelper("Manager Control Panel", exitCaption))
                ->addItem("Add new item", addNewItem)
                ->addItem("Edit an item", editAnItem)
                ->addItem("Remove an item", removeAnItem)
                ->addItem("Print statistic", simpleStatistic)
                ->addItem("Open Item list snapshot", openItemListSnapshot);
        managerMenu->run(true);
    }
};