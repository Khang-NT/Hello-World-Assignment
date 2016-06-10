//
// Created by blackcat on 07/06/2016.
//

#include "LoginScreen.hpp"
#include "../utils/MenuHelper.hpp"
#include "../model/AccountManager.hpp"
#include "AdminScreen.hpp"
#include "ManagerScreen.hpp"
#include "GuestScreen.hpp"

namespace LoginScreen {

    void signIn() {
        AccountManager *accountManager = AccountManager::getInstance();
        while (true) {
            string userName, password;
            printf("User name: ");
            Utils::getLine(std::cin, userName);
            printf("Password: ");
            Utils::getLine(std::cin, password);
            int accountPos = accountManager->findAccountWith(userName, password);
            if (accountPos == -1) {
                printf("User name or password incorrect!\n");
                printf("Retry (y/n)? "); /* Let user retry */
                if (!Utils::yesOrNo())
                    break;
            } else {
                signedInAccountPosition = accountPos; /* update global variant: an account has signed in */
                accountManager->getAccountAt(accountPos).loggedIn();
                switch (accountManager->getAccountAt(accountPos).getLevel()) {
                    case LEVEL_ADMIN:
                        AdminScreen::start();
                        return;
                    case LEVEL_MANAGER:
                        ManagerScreen::start();
                        return;
                    default:
                        break;
                }
            }
        }
    }

    void guest() {
        GuestScreen::start();
    }

    void start() {
        MenuHelper *menuHelper = (new MenuHelper("LOG IN", MenuHelper::QUIT_CAPTION))
                ->addItem("Sign in", signIn)
                ->addItem("Log in as guest", guest);
        menuHelper->run(true);
        delete menuHelper;
    }
}