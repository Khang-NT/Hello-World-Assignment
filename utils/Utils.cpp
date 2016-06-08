//
// Created by root on 28/05/2016.
//

#include "Utils.hpp"
#include "../model/AccountManager.hpp"

namespace Utils {
    void getLine(std::istream &stream, std::string &s) {
        do {
            std::getline(stream, s);
        } while (s == "");
    }

    bool yesOrNo() {
        string c = "";
        while (c != "Y" && c != "y" && c != "N" && c != "n")
            getLine(cin, c);
        return (c == "y" || c == "Y");
    }

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void pause() {
#ifdef WINDOWS
        system("pause");
#else
        system("read blabla");
#endif
    }

    void doSignUp(int level) {
        while (true) {
            std::string userName, staffId, password;
            printf("User name: ");
            getLine(std::cin, userName);
            printf("Staff ID: ");
            getLine(std::cin, staffId);
            printf("Password: ");
            getLine(std::cin, password);
            if (userName.length() < USER_NAME_MIN_LENGTH) {
                printf("User name too short.\n");
            } else if (password.length() < PASSWORD_MIN_LENGTH) {
                printf("Password too short.\n");
            } else if (userName.length() > USER_NAME_MAX_LENGTH) {
                printf("User name too long.\n");
            } else {
                if (AccountManager::findAccountWith(userName) != -1) {
                    printf("User name exists.\n");
                } else {
                    AccountManager::createAccount(userName, staffId, password, level);
                    printf("Create account success!\n");
                    pause();
                    return;
                }
            }
            printf("Retry (y/n)? "); /* Let user retry */
            if (!yesOrNo())
                break;
        }
    }

    void doResetPassword(int userId) {
        while (true) {
            string password;
            printf("Password: ");
            getLine(std::cin, password);
            if (password.length() < PASSWORD_MIN_LENGTH) {
                printf("Password too short.\n");
                printf("Retry (y/n)? "); /* Let user retry */
                if (!yesOrNo())
                    break;
            } else {
                AccountManager::changePassword(userId, password);
                printf("Change password success!\n");
                pause();
                return;
            }
        }
    }
}