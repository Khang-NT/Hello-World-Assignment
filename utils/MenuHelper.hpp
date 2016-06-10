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
    MenuHelper(string title = "", string exitCaption = "") {
        setCaptions(title, exitCaption);
    };

    MenuHelper *setCaptions(string title, string exitCaption);

    MenuHelper *addItem(string caption, function<void()> func);

    MenuHelper *addItem(string caption, function<void(int, int)> func, int var);

    MenuHelper *clear();

    /**
     * Print menu to screen and navigate user choice to funcs.
     * @param loop (bool) if true run loop until user choose EXIT.
     * @return false if user choose EXIT else return true.
     */
    bool run(bool loop) const;

    static const string GO_BACK_CAPTION;
    static const string QUIT_CAPTION;
    static const string LOG_OUT_CAPTION;

    ~MenuHelper() {
        menus.clear();
    }
private:
    string title, exitCaption;
    vector<tuple<string, void *, void *>> menus;
};


#endif //ASSIGNMENT_CPP_MENUHELPER_HPP
