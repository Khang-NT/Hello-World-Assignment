//
// Created by blackcat on 04/06/2016.
//

#ifndef CPPASSIGNMENT_ACCOUNTMANAGER_HPP
#define CPPASSIGNMENT_ACCOUNTMANAGER_HPP


#include <assert.h>
#include "ModelBase.hpp"
#include "Account.hpp"
#include "../utils/Utils.hpp"

const string USER_DB_FILE_HEADER = "MT2015-Users";
const string USER_DB_FILE = "UserDB.dat";
const string ADMIN_NAME = "admin";
const string ADMIN_PASSWORD = "admin";
static string ADMIN_STAFF_ID = "BOSS";

/**
 * Global variant define position of current signed in account.
 */
extern int signedInAccountPosition;

/**
 * Inherit class ModelBase. <br>
 * This class provides feature managing accounts (add, update, search).
 * @see class ModelBase
 * @see class Account
 */
class AccountManager : public ModelBase {
private:
    /**
     * Singleton instance
     */
    static AccountManager *sInstance;

public:
    AccountManager() : ModelBase() {}

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (AccountManager&) reference itself.
     */
    AccountManager &initialize() override;


    /**
     * Get singleton instance. <br>
     * If it wasn't created, do initialization with default data (include admin account).
     * @return (AccountManager &) singleton instance of AccountManager.
     */
    static AccountManager *getInstance();

    /**
     * Get number of existing accounts.
     * @return (unsigned) number of existing accounts.
     */
    static unsigned getAccountCount();

    /**
     * Get a copy of account object at given position.
     * @param position (int)
     * @return (Account) a copy of account object at position.
     */
    static Account getAccountAt(int position);

    /**
     * Find account position (index) in storing array (using for dertimine if user name exists).
     * @see AccountManager::getAccountAt()
     * @param userName (string) unique user name.
     * @return (int) Return position (index) of account which matches
     * given username if found, if not return -1;
     */
    static int findAccountWith(string userName);

    /**
     * Find account position (index) in storing array (using for sign in).
     * @see AccountManager::getAccountAt()
     * @param userName (string) unique user name.
     * @param password (string) password in string.
     * @return (int) Return position (index) of account which matches
     * given username and password, if not return -1;
     */
    static int findAccountWith(string userName, string password);

    /**
     * Find account position (index) in storing array (using for updating account).
     * @see AccountManager::getAccountAt()
     * @param userId (int) unique user ID.
     * @return (int) Return position (index) of account which matches
     * given userId, if not return -1;
     */
    static int findAccountWith(int userId);

    /**
     * Open new account, new data will be stored to disk automatically. <br>
     * Password will be encoded with Hash algorithm.
     * @param userName (string) user name
     * @param userName (string) Staff ID
     * @param password (string) password.
     * @param level (int) level is one of (LEVEL_ADMIN, LEVEL_MANAGER, LEVEL_GUEST).
     */
    static void createAccount(string userName, string password, string staffId, int level);

    /**
     * Change password of account which maches given ID, new data will be stored to disk automatically. <br>
     * Password will be encoded with Hash algorithm.
     * @param userId (int) user name
     * @param newPassword (string) new password.
     */
    static void changePassword(int userId, string newPassword);

    /**
     * Remove account with user ID.
     * @param userId (int) user ID of account to be removed.
     * @return (bool) return true if user Id is valid else return false.
     */
    static bool removeAccountWith(int userId);

protected:
    static const int FIELD_COUNT = 2;
    //static const int HEADER = 0;
    static const int AUTO_INCREASE_NUMBER = 0;
    static const int ARRAY_OF_ACCOUNTS = 1;

    virtual unsigned int getFieldCount() const override;

    virtual DataType getFieldType(int &fieldIndex) const override;

    virtual ModelBase *createVectorItem() override;


    vector<ModelBase *> *getAccountList();;

    int increaseUniqueIndex();

    /**
     * Save account list to USER_DB_FILE file. <br>
     * Include hash sum to make sure nobody touch this file outside the program.
     */
    void saveChange();
};

#endif //CPPASSIGNMENT_ACCOUNTMANAGER_HPP
