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

    /* check match with given unique properties value */
    bool match(string userName) {
        return getUserName() == userName;
    }

    bool matchPassword(string password);

    bool match(int userId) {
        return getUserId() == userId;
    }

    /* set / get */
    int getUserId() {
        return (*this)[USER_ID];
    }

    string getUserName() {
        return (*this)[USER_NAME];
    }

    int getPasswordHash() {
        return (*this)[PASSWORD_HASH];
    }

    int getLevel() {
        return (*this)[USER_LEVEL];
    }

    const char *getLevelAsString();

    int getLastModified() {
        return (*this)[LAST_MODIFIED];
    }

    int getLastLoginTime() {
        return (*this)[LAST_LOGIN];
    }

    string getStaffId() {
        return (*this)[STAFF_ID];
    }

    Account &setUserId(int id) {
        (*this)[USER_ID] = id;
        return *this;
    }

    Account &setUserName(string userName) {
        (*this)[USER_NAME] = userName;
        return *this;
    }

    Account &setPasswordHash(int passwordHash) {
        (*this)[PASSWORD_HASH] = passwordHash;
        return *this;
    }

    /**
     * Password will be transformed to hash code.
     * @param password (string)
     * @return (Account&) itself.
     */
    Account &setPassword(string password) {
        return setPasswordHash(HashSum::Builder().add(password).build());
    }

    Account &setLevel(int level) {
        (*this)[USER_LEVEL] = level;
        return *this;
    }

    Account &setStaffId(string staffId) {
        (*this)[STAFF_ID] = staffId;
        return *this;
    }

    Account &modified() {
        (*this)[LAST_MODIFIED] = time(0);
        return *this;
    }

    Account &loggedIn() {
        (*this)[LAST_LOGIN] = time(0);
        return *this;
    }

protected:
    static const int FIELD_COUNT = 7;
    static const int USER_ID = 0;
    static const int USER_NAME = 1;
    static const int PASSWORD_HASH = 2;
    static const int USER_LEVEL = 3;
    static const int LAST_MODIFIED = 4;
    static const int LAST_LOGIN = 5;
    static const int STAFF_ID = 6;

    virtual unsigned int getFieldCount() const override {
        return FIELD_COUNT;
    }

    virtual DataType getFieldType(int &fieldIndex) const override;

    virtual Object &operator[](size_t index) const override {
        return ModelBase::operator[](index);
    }
};


#endif //CPPASSIGNMENT_ACCOUNT_HPP
