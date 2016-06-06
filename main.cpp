#include <iostream>
#include "model/AccountManager.hpp"

using namespace std;

int main() {
    AccountManager::createAccount("Test", "2123", LEVEL_MANAGER);
    return 0;
}