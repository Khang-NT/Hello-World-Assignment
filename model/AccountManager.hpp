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
        return (unsigned) getAccountMap().size();
    }

    Account &operator[](int accountId) {
        return *static_cast<Account *>(getAccountMap()[accountId]);
    }

    Account &getAccountAt(int position) {
        unordered_map<int, ModelBase *>::iterator it = getAccountMap().begin();
        advance(it, position);
        return *static_cast<Account *>((*it).second);
    }

    bool
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

    unordered_map<int, ModelBase *> &getAccountMap() {
        return *(unordered_map<int, ModelBase *> *) ModelBase::operator[](MAP_OF_ACCOUNTS);
    };
};


#endif //CPPASSIGNMENT_ACCOUNTMANAGER_HPP
