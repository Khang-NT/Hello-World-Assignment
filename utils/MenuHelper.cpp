//
// Created by khang on 26/05/2016.
//

#include <iostream>
#include "MenuHelper.hpp"
#include "Utils.hpp"


const string MenuHelper::GO_BACK_CAPTION = "Go back";
const string MenuHelper::QUIT_CAPTION = "Quit";
const string MenuHelper::LOG_OUT_CAPTION = "Log out";

MenuHelper *MenuHelper::addItem(string caption, function<void()> func) {
    menus.push_back(make_tuple(caption, &func, nullptr));
    return this;
}

MenuHelper *MenuHelper::addItem(string caption, function<void(int, int)> func, int var) {
    menus.push_back(make_tuple(caption, &func, new int(var)));
    return this;
}

bool MenuHelper::run(bool loop) const {
    Utils::clearScreen();
    printf("---------------------- %s ----------------------\n", title.c_str());

    printf("%d. %s\n", 0, exitCaption.c_str());
    for (int i = 0; i < menus.size(); ++i)
        printf("%d. %s\n", i + 1, std::get<0>(menus[i]).c_str());
    printf("Select: ");
    int select = -1;
    cin >> select;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1024, '\n');
        cin >> select;
    }
    if (select < 0 || select > menus.size()) {
        return run(loop);
    }
    switch (select) {
        case 0:
            return false;
        default:
            select--; /* Convert to index-base-0 of menu */
            printf("---------------------------> %s\n", std::get<0>(menus[select]).c_str());
            if (std::get<2>(menus[select]) != nullptr) { /* If var != nullptr */
                function<void(int, int)> func =
                        *static_cast<function<void(int, int)> *>
                        (std::get<1>(menus[select]));
                int var = *((int *) std::get<2>(menus[select]));
                func(var, select);
            } else {
                function<void()> func =
                        *static_cast<function<void()> *>
                        (std::get<1>(menus[select]));
                func();
            }
            if (loop)
                return run(true);
            else
                return true; /* Convert to index-base-1 of menu */
    }
}

MenuHelper *MenuHelper::clear() {
    menus.clear();
    return this;
}

MenuHelper *MenuHelper::setCaptions(string title, string exitCaption) {
    this->title = title;
    this->exitCaption = exitCaption;
    return this;
}







