//
// Created by blackcat on 10/06/2016.
//

#include "GuestScreen.hpp"
#include "../utils/MenuHelper.hpp"
#include "../utils/ExportHTML.hpp"
#include "../model/ProductManager.hpp"
#include "../model/OrderManager.hpp"

namespace GuestScreen {

    vector<pair<int, int>> cart; /* pair<product id - number> */

    void seeItemsList() {
        ExportHTML::exportProductList();
    }

    void orderAProduct() {
        printf("You need to know product ID to continue this action.\n"
                       "Do you want to see product list in browser (y/n)? ");
        if (Utils::yesOrNo())
            seeItemsList();
        int productPosition;
        do {
            printf("Product ID: ");
            int productId;
            do {
                cin.clear();
                cin >> productId;
            } while (cin.fail());
            productPosition = ProductManager::findProduct(productId);
            if (productPosition == -1) {
                printf("Product ID invalid.\n");
                printf("Retry (y/n)? "); /* Let user retry */
                if (!Utils::yesOrNo())
                    return;
            } else {
                int i = -1;
                for (auto item : cart) {
                    i++;
                    if (item.first == productId) {
                        printf("Product is already in cart.\n");
                        printf("Continue will remove it from cart (y/n)? "); /* Let user retry */
                        if (!Utils::yesOrNo())
                            return;
                        else
                            cart.erase(cart.begin() + i);
                    }
                }
            }
        } while (productPosition == -1);
        Product product = ProductManager::getProductAt(productPosition);
        printf("Add to cart product:\n");
        printf("%-20s: %d\n", "ID", product.getProductId());
        printf("%-20s: %s\n", "Product name", product.getProductName().c_str());
        printf("%-20s: %s\n", "Category", product.getCategory().c_str());
        printf("%-20s: %s\n", "Manufacturer", product.getManufacturer().c_str());
        printf("%-20s: %s\n", "Warranty info", product.getWarrantyInfo().c_str());
        printf("%-20s: %d$\n", "Price", product.getPrice());
        printf("%-20s: %d item(s)\n", "Available", product.getItemCount());
        printf("\n");

        int number;
        do {
            printf("Number: ");
            do {
                cin.clear();
                cin >> number;
            } while (cin.fail());
            if (number > 0 && number <= product.getItemCount())
                break;
            else {
                printf("Number must between 1 and amount available products.\n");
                printf("Retry (y/n)? "); /* Let user retry */
                if (!Utils::yesOrNo())
                    return;
            }
        } while (true);
        printf("Preview:\n");
        printf("%-20s: %s x %d\n", "Product", product.getProductName().c_str(), number);
        printf("%-20s: %d$\n", "Amount money", product.getPrice() * number);
        printf("Do you want to add to cart (y/n)? ");
        if (Utils::yesOrNo()) {
            cart.push_back(make_pair(product.getProductId(), number));
            printf("Done. ");
            Utils::pause();
        }
    }

    void viewCart() {
        if (cart.size() == 0) {
            printf("Cart is empty.");
        } else {
            printf("%-10s %-25s %-20s %-20s\n", "#", "Product name", "Number", "Amount money");
            int i = 0;
            int sum = 0;
            for (auto item : cart) {
                Product product = ProductManager::getProductAt(
                        ProductManager::findProduct(item.first));
                printf("%-10s %-25s %-20s %-20s\n", to_string(++i).c_str(),
                       product.getProductName().c_str(), to_string(item.second).c_str(),
                       (to_string(product.getPrice() * item.second) + "$").c_str());
                sum += product.getPrice() * item.second;
            }
            printf("%-10s %-25s %-20s %-20s\n", "", "", "", ("Sum " + to_string(sum) + "$").c_str());
        }
        cin.ignore();
        Utils::pause();
    }

    void removeAnItemFromCartWith(int temp, int position) {
        cart.erase(cart.begin() + position);
    }

    void removeAnItemFromCart() {
        MenuHelper *menu = new MenuHelper("Select a item to remove", MenuHelper::GO_BACK_CAPTION);
        do {
            menu->clear();
            for (auto item : cart) {
                Product product = ProductManager::getProductAt(ProductManager::findProduct(item.first));
                menu->addItem(
                        product.getProductName() + " x " + to_string(item.second),
                        removeAnItemFromCartWith, 0
                );
            }
        } while (menu->run(false));
        delete menu;
    }

    void submitOrders() {
        if (cart.size() == 0) {
            printf("Cart is empty.\n");
            Utils::pause();
            return;
        }
        string name, phone, address, additionInfo;
        printf("Please fill form information:\n");
        printf("Your name: ");
        Utils::getLine(cin, name);
        printf("Phone number: ");
        Utils::getLine(cin, phone);
        printf("Address: ");
        Utils::getLine(cin, address);
        printf("Addition information: ");
        Utils::getLine(cin, additionInfo);

        printf("\nReview:\n");
        printf("Name           : %s\n", name.c_str());
        printf("Phone number   : %s\n", phone.c_str());
        printf("Address        : %s\n", address.c_str());
        printf("Addition info  : %s\n", additionInfo.c_str());
        printf("Cart:\n");
        viewCart();

        printf("Confirm to submit orders (y/n)? ");
        if (Utils::yesOrNo()) {
            for (auto item : cart)
                OrderManager::addOrder(item.first, item.second,
                                       name, phone, address, additionInfo);
            cart.clear();
            printf("Submit success.");
            Utils::pause();
        }
    }

    void start() {
        cart.clear();
        MenuHelper *guestMenu = new MenuHelper("GUEST MENU", MenuHelper::GO_BACK_CAPTION);
        guestMenu->addItem("See Items list.", seeItemsList)
                ->addItem("Order a product", orderAProduct)
                ->addItem("View cart", viewCart)
                ->addItem("Remove an item from cart", removeAnItemFromCart)
                ->addItem("Submit orders", submitOrders);
        while (true) {
            bool exit = !guestMenu->run(false);
            if (exit) {
                if (cart.size() == 0)
                    break;
                else {
                    printf("Go back will remove all items in cart\n");
                    printf("Exit now (y/n)? ");
                    if (Utils::yesOrNo())
                        break;
                }
            }
        }

        delete guestMenu;
    }
}