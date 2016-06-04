//
// Created by root on 28/05/2016.
//

#ifndef ASSIGNMENT_UTILS_HPP
#define ASSIGNMENT_UTILS_HPP


#include <iosfwd>
#include <istream>
#include <iostream>

namespace Utils {
    void getLine(std::istream &stream, std::string &s);

    template<typename Base, typename T>
    inline bool instanceOf(const T *) {
        return std::is_base_of<Base, T>::value;
    }

    /**
     * Require user choose Yes or No
     * @return true if user choose yes.
     */
    bool yesOrNo();

    void clearScreen();

    /**
     * Show sign up form and add new account to AccountManager if sign up success.
     * @param accountType account type to create.
     * @see Account::TYPE_ADMIN Account::TYPE_MANAGER Account::TYPE_CUSTOMER
     */
    void doSignUp(int accountType);
}


#endif //ASSIGNMENT_UTILS_HPP
