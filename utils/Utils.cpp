//
// Created by root on 28/05/2016.
//

#include "Utils.hpp"

namespace Utils {
    void getLine(std::istream &stream, std::string &s) {
        do {
            std::getline(stream, s);
        } while (s.compare("") == 0);
    }

    bool yesNo() {
        char c = ' ';
        while (c != 'Y' && c != 'y' && c != 'N' && c != 'n') {
            std::cin >> c;
        }
        return (c == 'y' || c == 'Y');
    }

    void clearScreen() {
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
    }

    void doSignUp(int accountType) {
        while (true) {
            std::string userName, password;
            printf("User name: ");
            getLine(std::cin, userName);
            printf("Password: ");
            getLine(std::cin, password);
            if (userName.length() < 5) {
                printf("User name too short.\n");
                continue;
            } else if (password.length() < 5) {
                printf("Password too short.\n");
                continue;
            } else if (userName.length() > 20) {
                printf("User name too long.\n");
                continue;
            } else {
//                if (AccountManager::getInstance()->existUserName(userName)) {
//                    printf("User name exists.\n");
//                    continue;
//                }
//                AccountManager::getInstance()->addAccount(userName, password, accountType);
//                printf("Create account success!\n");
                break;
            }
        }
    }
}