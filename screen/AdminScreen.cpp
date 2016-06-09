//
// Created by blackcat on 07/06/2016.
//

#include "AdminScreen.hpp"
#include "../utils/MenuHelper.hpp"
#include "../utils/Utils.hpp"
#include "../model/AccountManager.hpp"
#include "../utils/ExportHTML.hpp"
#include "ManagerScreen.hpp"

namespace AdminScreen {

    void openAccountListSnapshot() {
        ExportHTML::exportAccountList();
    }

    void openManagerControlPanel() {
        ManagerScreen::start(MenuHelper::GO_BACK_CAPTION);
    }

    void promptOpenAccountsViewer(const char *why) {
        printf("%sDo you want open Accounts list Snapshot (Y/N)? ", why);
        if (Utils::yesOrNo()) {
            openAccountListSnapshot();
        }
    }

    void doChangePassword() {
        int thisUserId = AccountManager::getAccountAt(signedInAccountPosition).getUserId();
        Utils::doResetPassword(thisUserId);
    }

    void createAdminAccount() {
        Utils::doSignUp(LEVEL_ADMIN);
    }

    void createManagerAccount() {
        Utils::doSignUp(LEVEL_MANAGER);
    }

    void removeAnAccount() {
        promptOpenAccountsViewer("You need to know user ID of account to be removed.\n");
        while (true) {
            int id;
            printf("User id: ");
            cin >> id;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1024, '\n');
                cin >> id;
            }
            if (AccountManager::getAccountAt(signedInAccountPosition).getUserId() == id)
                printf("You cannot delete your account.\n");
            else {
                int accountPosition = AccountManager::findAccountWith(id);
                if (accountPosition < 0)
                    printf("Account ID not exist.\n");
                else {
                    Account account = AccountManager::getAccountAt(accountPosition);
                    printf("Remove account: %s - %s - staff ID: %s\n",
                           account.getUserName().c_str(),
                           account.getLevelAsString(),
                           account.getStaffId());
                    printf("Are you sure (y/n)? ");
                    if (Utils::yesOrNo()) {
                        AccountManager::removeAccountWith(id, accountPosition);
                        printf("Remove account %d success!", id);
                        Utils::pause();
                    }
                    return;
                }
            }
            printf("Retry (y/n)? "); /* Let user retry */
            if (!Utils::yesOrNo())
                break;
        }

    }

    void resetAnAccountPassword() {
        promptOpenAccountsViewer("You need to know user ID to change their password.\n");
        while (true) {
            int id;
            printf("User id: ");
            cin >> id;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1024, '\n');
                cin >> id;
            }
            int accountPosition = AccountManager::findAccountWith(id);
            if (accountPosition == -1)
                printf("Account ID not exist.\n");
            else {
                Account account = AccountManager::getAccountAt(accountPosition);
                printf("Reset password of account: %s - %s - staff ID: %s\n",
                       account.getUserName().c_str(),
                       account.getLevelAsString(),
                       account.getStaffId());
                Utils::doResetPassword(id, accountPosition);
                return;
            }
            printf("Retry (y/n)? "); /* Let user retry */
            if (!Utils::yesOrNo())
                break;
        }
    }

    void start() {
        MenuHelper *adminMenu = (new MenuHelper("Admin control panel", MenuHelper::LOG_OUT_CAPTION))
                ->addItem("Change password", doChangePassword)
                ->addItem("Open new admin account", createAdminAccount)
                ->addItem("Open new manager account", createManagerAccount)
                ->addItem("Remove an account", removeAnAccount)
                ->addItem("Reset an account's password", resetAnAccountPassword)
                ->addItem("Open Accounts list Snapshot", openAccountListSnapshot)
                ->addItem("Open manager control panel", openManagerControlPanel);
        adminMenu->run(true);
        delete adminMenu;
    }
};