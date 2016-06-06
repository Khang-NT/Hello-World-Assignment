#include <iostream>
#include <fstream>
#include "model/AccountManager.hpp"

using namespace std;

int main() {
    cout << "======================= OUT +++++++++++++++++++++++++" << endl;
    ofstream out("test.txt");
    AccountManager accountManager = AccountManager().initialize();
    accountManager.createAccount("admin", "admin", LEVEL_ADMIN);
    HashSum::Builder builder;
    out << accountManager.with(builder);
    out << *builder.build();
    out.close();

    cout << "======================= IN +++++++++++++++++++++++++" << endl;
    AccountManager *test = new AccountManager();
    test->initialize();
    ifstream in("test.txt");
    builder = HashSum::Builder();
    in >> test->with(builder);
    cout << test->getAccountCount() << endl;
    cout << *builder.build();
    return 0;
}