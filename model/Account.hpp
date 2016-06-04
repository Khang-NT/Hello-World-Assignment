//
// Created by blackcat on 04/06/2016.
//

#ifndef CPPASSIGNMENT_ACCOUNT_HPP
#define CPPASSIGNMENT_ACCOUNT_HPP


#include <assert.h>
#include "ModelBase.hpp"

class Account : public ModelBase {
public:
    Account() : ModelBase() {}

    Account(int userId, string userName, string password, int level) : Account() {
        setUserId(userId)
                .setUserName(userName)
                .setPassword(password)
                .setLevel(level);
    }

    bool match(string userName) {
        return getUserName() == userName;
    }

    bool match(string userName, string password) {
        return match(userName) &&
               *HashSum::Builder().add(password).build() == getPasswordHash();
    }

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

    Account &setPassword(string password) {
        return setPasswordHash(*HashSum::Builder().add(password).build());
    }

    Account &setLevel(int level) {
        (*this)[USER_LEVEL] = level;
        return *this;
    }

protected:
    static const int FIELD_COUNT = 5;
    static const int USER_ID = 0;
    static const int USER_NAME = 1;
    static const int PASSWORD_HASH = 2;
    static const int USER_LEVEL = 3;

    virtual unsigned int getFieldCount() override {
        return FIELD_COUNT;
    }

    virtual DataType getFieldType(int &fieldIndex) override {
        switch (fieldIndex) {
            case USER_ID:
            case PASSWORD_HASH:
            case USER_LEVEL:
                return TYPE_INTEGER;
            case USER_NAME:
                return TYPE_STRING;
            default:
                assert(false);
        }
    }
};


#endif //CPPASSIGNMENT_ACCOUNT_HPP
