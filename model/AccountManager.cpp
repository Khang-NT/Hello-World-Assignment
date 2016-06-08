//
// Created by blackcat on 07/06/2016.
//

#include "AccountManager.hpp"

int signedInAccountPosition = -1;
AccountManager *AccountManager::sInstance = nullptr;

bool AccountManager::removeAccountWith(int userId) {
    int position = findAccountWith(userId);
    if (position > 0) {
        vector<ModelBase *> *accountList = getInstance()->getAccountList();
        accountList->erase(accountList->begin() + position);
        getInstance()->saveChange();
        return true;
    }
    return false;
}

void AccountManager::changePassword(int userId, string newPassword) {
    AccountManager *accountManager = getInstance();
    int position = findAccountWith(userId);
    if (position > 0) {
        vector<ModelBase *> accountList = *getInstance()->getAccountList();
        ((Account *) accountList[position])->setPassword(newPassword);
        accountManager->saveChange();
    }

}

void AccountManager::createAccount(string userName, string password, string staffId, int level) {
    AccountManager *accountManager = getInstance();
    ModelBase *account = &(new Account())->initialize(
            accountManager->increaseUniqueIndex(),
            userName,
            staffId,
            password,
            level
    );
    accountManager->getAccountList()->push_back(account);
    accountManager->saveChange();
}

int AccountManager::findAccountWith(int userId) {
    vector<ModelBase *> accountList = *getInstance()->getAccountList();
    for (int i = 0; i < accountList.size(); ++i)
        if (((Account *) accountList[i])->match(userId))
            return i;
    return -1;
}

int AccountManager::findAccountWith(string userName, string password) {
    int position = findAccountWith(userName);
    return position == -1 || !AccountManager::getAccountAt(position).matchPassword(password) ?
           -1 : position;
}

int AccountManager::findAccountWith(string userName) {
    vector<ModelBase *> accountList = *getInstance()->getAccountList();
    for (int i = 0; i < accountList.size(); ++i)
        if (((Account *) accountList[i])->match(userName))
            return i;
    return -1;
}

Account AccountManager::getAccountAt(int position) {
    return *static_cast<Account *>((*getInstance()->getAccountList())[position]);
}

unsigned AccountManager::getAccountCount() {
    return (unsigned) getInstance()->getAccountList()->size();
}

AccountManager *AccountManager::getInstance() {
    if (sInstance)
        return sInstance;
    signedInAccountPosition = -1; /* Initialization, no account has logged in */
    try {
        sInstance = Utils::deserialize<AccountManager>(USER_DB_FILE, USER_DB_FILE_HEADER);
    } catch (const char *e) {
        cout << "Error: " << e << endl;
        printf("Do you want to continue process and override file %s with default data (y/n)? ",
               USER_DB_FILE.c_str());
        if (Utils::yesOrNo()) {
            /* Write default data */
            sInstance = &(new AccountManager())->initialize();
            createAccount(ADMIN_NAME, ADMIN_PASSWORD, ADMIN_STAFF_ID, LEVEL_ADMIN);
        } else
            exit(0);
    }
    return sInstance;
}

AccountManager &AccountManager::initialize() {
    ModelBase::initialize();
    //ModelBase::operator[](HEADER) = "MT2015-Users";
    return *this;
}

DataType AccountManager::getFieldType(int &fieldIndex) const {
    switch (fieldIndex) {
        //case HEADER:
        //return TYPE_STRING;
        case AUTO_INCREASE_NUMBER:
            return TYPE_INTEGER;
        case ARRAY_OF_ACCOUNTS:
            return TYPE_ARRAY_OF_MODELS;
        default:
            assert(false);
    }
}

ModelBase *AccountManager::createVectorItem() {
    return &(new Account())->initialize();
}

unsigned int AccountManager::getFieldCount() const {
    return FIELD_COUNT;
}

vector<ModelBase *> *AccountManager::getAccountList() {
    return ModelBase::operator[](ARRAY_OF_ACCOUNTS);
}

int AccountManager::increaseUniqueIndex() {
    int currentIndex = (*getInstance())[AUTO_INCREASE_NUMBER];
    return (*getInstance())[AUTO_INCREASE_NUMBER] = ++currentIndex;
}

void AccountManager::saveChange() {
    try {
        Utils::serialize(*this, USER_DB_FILE, USER_DB_FILE_HEADER);
    } catch (const char *e) {
        cout << "Update file " << USER_DB_FILE << " error: " << e << endl;
        cout << "Warning: All changes will be aborted after closed program?\n"
                "Do you want to retry (y/n)? ";
        if (Utils::yesOrNo())
            saveChange();
    }
}
