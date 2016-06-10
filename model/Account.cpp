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

bool Account::match(string userName) {
    return getUserName() == userName;
}

bool Account::match(int userId) {
    return getUserId() == userId;
}

int Account::getUserId() {
    return (*this)[USER_ID];
}

string Account::getUserName() {
    return (*this)[USER_NAME];
}

int Account::getPasswordHash() {
    return (*this)[PASSWORD_HASH];
}

int Account::getLevel() {
    return (*this)[USER_LEVEL];
}

int Account::getLastModified() {
    return (*this)[LAST_MODIFIED];
}

int Account::getLastLoginTime() {
    return (*this)[LAST_LOGIN];
}

string Account::getStaffId() {
    return (*this)[STAFF_ID];
}

Account &Account::setUserId(int id) {
    (*this)[USER_ID] = id;
    return *this;
}

Account &Account::setUserName(string userName) {
    (*this)[USER_NAME] = userName;
    return *this;
}

Account &Account::setPasswordHash(int passwordHash) {
    (*this)[PASSWORD_HASH] = passwordHash;
    return *this;
}

Account &Account::setPassword(string password) {
    return setPasswordHash(HashSum::Builder().add(password).build());
}

Account &Account::setLevel(int level) {
    (*this)[USER_LEVEL] = level;
    return *this;
}

Account &Account::setStaffId(string staffId) {
    (*this)[STAFF_ID] = staffId;
    return *this;
}

Account &Account::modified() {
    (*this)[LAST_MODIFIED] = time(0);
    return *this;
}

Account &Account::loggedIn() {
    (*this)[LAST_LOGIN] = time(0);
    return *this;
}

unsigned int Account::getFieldCount() const {
    return FIELD_COUNT;
}

Object &Account::operator[](size_t index) const {
    return ModelBase::operator[](index);
}
