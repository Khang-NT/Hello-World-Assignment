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
    menus.push_back(make_pair(caption, func));
    return this;
}

void MenuHelper::run(bool showTitle) const {
    Utils::clearScreen();
    if (showTitle)
        printf("---------------------- %s ----------------------\n", title.c_str());
    for (int i = 0; i < menus.size(); ++i)
        printf("%d. %s\n", i, menus[i].first.c_str());
    printf("Select: ");
    int select = -1;
    cin >> select;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1024, '\n');
        cin >> select;
    }
    if (select < 0 || select > menus.size()) {
        run(showTitle);
        return;
    }
    switch (select) {
        case 0:
            return;
        default:
            printf("---------------------------> %s\n", menus[select].first.c_str());
            menus[select].second();
            run(showTitle);
    }
}

