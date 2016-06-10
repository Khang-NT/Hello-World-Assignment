//
// Created by blackcat on 04/06/2016.
//

#ifndef CPPASSIGNMENT_ACCOUNT_HPP
#define CPPASSIGNMENT_ACCOUNT_HPP


#include <assert.h>
#include <time.h>
#include "ModelBase.hpp"

static const int LEVEL_ADMIN = 0, LEVEL_MANAGER = 1;
static const int PASSWORD_MIN_LENGTH = 5, USER_NAME_MIN_LENGTH = 5;
static const int USER_NAME_MAX_LENGTH = 15;

/**
 * Inherit class ModelBase. <br>
 * This class stores account properties: id, user name, password, level.
 * @see class ModelBase
 * @see class AccountManager
 */
class Account : public ModelBase {
public:
    Account() : ModelBase() {}

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (Account&) reference itself.
     */
    Account &initialize() override;

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (Account&) reference itself.
     */
    Account &initialize(int userId, string userName, string staffId, string password, int level);

    /* check if matching with unique properties */
    bool match(string userName);

    bool matchPassword(string password);

    bool match(int userId);

    /* set / get */
    int getUserId();

    string getUserName();

    int getPasswordHash();

    int getLevel();

    const char *getLevelAsString();

    int getLastModified();

    int getLastLoginTime();

    string getStaffId();

    Account &setUserId(int id);

    Account &setUserName(string userName);

    Account &setPasswordHash(int passwordHash);

    /**
     * Password will be transformed to hash code.
     * @param password (string)
     * @return (Account&) itself.
     */
    Account &setPassword(string password);

    Account &setLevel(int level);

    Account &setStaffId(string staffId);

    Account &modified();

    Account &loggedIn();

protected:
    /* Constants */
    static const int FIELD_COUNT = 7;
    static const int USER_ID = 0;
    static const int USER_NAME = 1;
    static const int PASSWORD_HASH = 2;
    static const int USER_LEVEL = 3;
    static const int LAST_MODIFIED = 4;
    static const int LAST_LOGIN = 5;
    static const int STAFF_ID = 6;

    /* Override base funcs */
    virtual unsigned int getFieldCount() const override;

    virtual DataType getFieldType(int &fieldIndex) const override;

    /* Make protected base's method */
    virtual Object &operator[](size_t index) const override;
};


#endif //CPPASSIGNMENT_ACCOUNT_HPP
