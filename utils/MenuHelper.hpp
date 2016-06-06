//
// Created by khang on 26/05/2016.
//

#ifndef ASSIGNMENT_CPP_MENUHELPER_HPP
#define ASSIGNMENT_CPP_MENUHELPER_HPP

#include <vector>
#include <string>
#include <functional>

using namespace std;

class MenuHelper {
public:
    MenuHelper(string title, string exitCaption) : title(title), exitCaption(exitCaption) {
        addItem(exitCaption, nullptr);
    };

    MenuHelper *addItem(string caption, function<void()>);

    void run(bool showTitle) const;

    static const string GO_BACK_CAPTION;
    static const string QUIT_CAPTION;
    static const string LOG_OUT_CAPTION;
private:
    string title, exitCaption;
    vector<pair<string, function<void()>>> menus;
};


#endif //ASSIGNMENT_CPP_MENUHELPER_HPP
