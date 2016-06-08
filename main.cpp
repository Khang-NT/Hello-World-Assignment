#include <iostream>
#include "screen/LoginScreen.hpp"
#include "utils/ExportHTML.hpp"

using namespace std;

int main(int argsCount, char *args[]) {
    ExportHTML::exportAccountList();
    LoginScreen::start();
    return 0;
}