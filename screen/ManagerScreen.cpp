//
// Created by blackcat on 08/06/2016.
//

#include "ManagerScreen.hpp"

namespace ManagerScreen {

    void openItemListSnapshot() {

    }

    void addNewItem() {

    }

    void editAnItem() {

    }

    void removeAnItem() {

    }


    void start(string exitCaption) {
        MenuHelper *managerMenu = (new MenuHelper("Manager Control Panel", exitCaption))
                ->addItem("Add new item", addNewItem)
                ->addItem("Edit an item", editAnItem)
                ->addItem("Remove an item", removeAnItem);
        managerMenu->run(true);
    }
};