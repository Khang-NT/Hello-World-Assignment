//
// Created by blackcat on 08/06/2016.
//

#include "Account.hpp"

Account &Account::initialize() {
    ModelBase::initialize();
    return *this;
}

Account &Account::initialize(int userId, string userName, string staffId, string password, int level) {
    ModelBase::initialize();
    setUserId(userId)
            .setUserName(userName)
            .setStaffId(staffId)
            .setPassword(password)
            .setLevel(level)
            .modified()
            .loggedIn();
    return *this;
}

const char *Account::getLevelAsString() {
    switch (getLevel()) {
        case LEVEL_ADMIN:
            return "Admin";
        case LEVEL_MANAGER:
            return "Store Manager";
        default:
            return "Unknown";
    }
}

bool Account::matchPassword(string password) {
    return HashSum::Builder().add(password).build() == getPasswordHash();
}

DataType Account::getFieldType(int &fieldIndex) const {
    switch (fieldIndex) {
        case USER_ID:
        case PASSWORD_HASH:
        case USER_LEVEL:
        case LAST_MODIFIED:
        case LAST_LOGIN:
            return TYPE_INTEGER;
        case USER_NAME:
        case STAFF_ID:
            return TYPE_STRING;
        default:
            assert(false);
    }
}
