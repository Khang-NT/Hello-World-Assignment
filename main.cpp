#include <iostream>
#include <fstream>
#include "model/AccountManager.hpp"

using namespace std;

int main() {
    ifstream file("test.txt");
    int a;
    file >> a;
    cout << a;
    return 0;
}