//
// Created by blackcat on 04/06/2016.
//

#ifndef CPPASSIGNMENT_ACCOUNTMANAGER_HPP
#define CPPASSIGNMENT_ACCOUNTMANAGER_HPP


#include <assert.h>
#include "ModelBase.hpp"
#include "Account.hpp"

class AccountManager : public ModelBase {
public:
    AccountManager() : ModelBase() {}

    unsigned getAccountCount() {
        return (unsigned) getAccountList().size();
    }

    Account &operator[](int position) {
        return *static_cast<Account *>(getAccountList()[position]);
    }

    int findAccountWith(string userName) {
        int i = 0;
        for (auto account : getAccountList())
            if (((Account *) account)->match(userName))
                return i;
            else i++;
        return -1;
    }

    int findAccountWith(string userName, string password) {
        int position = findAccountWith(userName);
        return position == -1 || !(*this)[position].matchPassword(password) ?
               -1 : position;
    }

    int findAccountWith(int userId) {
        int i = 0;
        for (auto account : getAccountList())
            if (((Account *) account)->match(userId))
                return i;
            else i++;
        return -1;
    }

    void createAccount(string userName, string password, int level) {
        ModelBase *account = new Account(
                increaseUniqueIndex(),
                userName,
                password,
                level
        );
        getAccountList().push_back(account);
    }

    void changePassword(int userId, string newPassword) {
        int position = findAccountWith(userId);
        if (position > 0)
            (*this)[position].setPassword(newPassword);
    }

protected:
    static const int FIELD_COUNT = 2;
    static const int AUTO_INCREASE_NUMBER = 0;
    static const int MAP_OF_ACCOUNTS = 1;

    virtual unsigned int getFieldCount() override {
        return FIELD_COUNT;
    }

    virtual DataType getFieldType(int &fieldIndex) override {
        switch (fieldIndex) {
            case AUTO_INCREASE_NUMBER:
                return TYPE_INTEGER;
            case MAP_OF_ACCOUNTS:
                return TYPE_ARRAY_OF_MODELS;
            default:
                assert(false);
        }
    }

    vector<ModelBase *> &getAccountList() {
        return ModelBase::operator[](MAP_OF_ACCOUNTS);
    };

    int increaseUniqueIndex() {
        int currentIndex = ModelBase::operator[](AUTO_INCREASE_NUMBER);
        return ModelBase::operator[](AUTO_INCREASE_NUMBER) = ++currentIndex;
    }
};


#endif //CPPASSIGNMENT_ACCOUNTMANAGER_HPP
