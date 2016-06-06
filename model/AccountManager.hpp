//
// Created by blackcat on 04/06/2016.
//

#ifndef CPPASSIGNMENT_ACCOUNTMANAGER_HPP
#define CPPASSIGNMENT_ACCOUNTMANAGER_HPP


#include <assert.h>
#include "ModelBase.hpp"
#include "Account.hpp"
#include "../utils/Utils.hpp"

const string DB_FILE = "UserDB.dat";
const string ADMIN_NAME = "admin";
const string ADMIN_PASSWORD = "admin";

/**
 * Inherit class ModelBase. <br>
 * This class provides feature managing accounts (add, update, search).
 * @see class ModelBase
 * @see class Account
 */
class AccountManager : public ModelBase {
public:
    AccountManager() : ModelBase() {}

    AccountManager &initialize() override {
        ModelBase::initialize();
        ModelBase::operator[](HEADER) = "MT2015-Users";
        return *this;
    }

    /**
     * Singlestone instance
     */
    static AccountManager *sInstance;

    /**
     * Get singlestone instance.
     * If it wasn't created, do initialization with default data (include admin account).
     * @return (AccountManager &) singlestone instance of AccountManager.
     */
    static AccountManager &getInstance() {
        if (sInstance)
            return *sInstance;
        else {
            try {
                sInstance = Utils::deserialize<AccountManager>(DB_FILE);
            } catch (const char *e) {
                cout << "Error: " << e << endl;
                printf("Do you want to continue process and override file %s as default (y/n)? ");
                if (Utils::yesOrNo()) {
                    /* Write default data */
                    sInstance = &(new AccountManager())->initialize();
                    createAccount(ADMIN_NAME, ADMIN_PASSWORD, LEVEL_ADMIN);
                } else
                    exit(0);
            }
        }
    }

    /**
     * Get number of existing accounts.
     * @return (unsigned) number of existing accounts.
     */
    static unsigned getAccountCount() {
        return (unsigned) getInstance().getAccountList()->size();
    }

    /**
     * Get reference of account at given position.
     * @param position (int)
     * @return (Account &) reference of account at position.
     */
    static Account &getAccountAt(int position) {
        return *static_cast<Account *>((*getInstance().getAccountList())[position]);
    }

    /**
     * Find account position (index) in storing array (using for dertimine if user name exists).
     * @see AccountManager::getAccountAt()
     * @param userName (string) unique user name.
     * @return (int) Return position (index) of account which matches
     * given username if found, if not return -1;
     */
    static int findAccountWith(string userName) {
        vector<ModelBase *> accountList = *getInstance().getAccountList();
        for (int i = 0; i < accountList.size(); ++i)
            if (((Account *) accountList[i])->match(userName))
                return i;
        return -1;
    }

    /**
     * Find account position (index) in storing array (using for sign in).
     * @see AccountManager::getAccountAt()
     * @param userName (string) unique user name.
     * @param password (string) password in string.
     * @return (int) Return position (index) of account which matches
     * given username and password, if not return -1;
     */
    static int findAccountWith(string userName, string password) {
        int position = findAccountWith(userName);
        return position == -1 || !AccountManager::getAccountAt(position).matchPassword(password) ?
               -1 : position;
    }

    /**
     * Find account position (index) in storing array (using for updating account).
     * @see AccountManager::getAccountAt()
     * @param userId (int) unique user ID.
     * @return (int) Return position (index) of account which matches
     * given userId, if not return -1;
     */
    static int findAccountWith(int userId) {
        vector<ModelBase *> accountList = *getInstance().getAccountList();
        for (int i = 0; i < accountList.size(); ++i)
            if (((Account *) accountList[i])->match(userId))
                return i;
        return -1;
    }

    /**
     * Open new account, new data will be stored to disk automatically.
     * Password will be encoded with Hash algorithm.
     * @param userName (string) user name
     * @param password (string) password.
     * @param level (int) level is one of (LEVEL_ADMIN, LEVEL_MANAGER, LEVEL_GUEST).
     */
    static void createAccount(string userName, string password, int level) {
        AccountManager accountManager = getInstance();
        ModelBase *account = &(new Account())->initialize(
                accountManager.increaseUniqueIndex(),
                userName,
                password,
                level
        );
        accountManager.getAccountList()->push_back(account);
        accountManager.saveChange();
    }

    /**
     * Change password of account which maches given ID, new data will be stored to disk automatically.
     * Password will be encoded with Hash algorithm.
     * @param userId (int) user name
     * @param newPassword (string) new password.
     */
    static void changePassword(int userId, string newPassword) {
        AccountManager accountManager = getInstance();
        int position = findAccountWith(userId);
        if (position > 0)
            accountManager.getAccountAt(position).setPassword(newPassword);
        accountManager.saveChange();
    }

protected:
    static const int FIELD_COUNT = 3;
    static const int HEADER = 0;
    static const int AUTO_INCREASE_NUMBER = 1;
    static const int ARRAY_OF_ACCOUNTS = 2;

    virtual unsigned int getFieldCount() override {
        return FIELD_COUNT;
    }

    virtual DataType getFieldType(int &fieldIndex) override {
        switch (fieldIndex) {
            case HEADER:
                return TYPE_STRING;
            case AUTO_INCREASE_NUMBER:
                return TYPE_INTEGER;
            case ARRAY_OF_ACCOUNTS:
                return TYPE_ARRAY_OF_MODELS;
            default:
                assert(false);
        }
    }

    virtual ModelBase *createVectorItem() {
        return &(new Account())->initialize();
    }


    vector<ModelBase *> *getAccountList() {
        return ModelBase::operator[](ARRAY_OF_ACCOUNTS);
    };

    int increaseUniqueIndex() {
        int currentIndex = getInstance()[AUTO_INCREASE_NUMBER];
        return getInstance()[AUTO_INCREASE_NUMBER] = ++currentIndex;
    }

    void saveChange() {
        try {
            Utils::serialize(*this, DB_FILE);
        } catch (const char *e) {
            cout << "Update file " << DB_FILE << " error: " << e << endl;
            cout << "Warning: All changes will be aborted after closed program?\n"
                    "Do you want to retry (y/n)? ";
            if (Utils::yesOrNo())
                saveChange();
        }
    }
};


#endif //CPPASSIGNMENT_ACCOUNTMANAGER_HPP
