#include "screen/LoginScreen.hpp"
#include "utils/ExportHTML.hpp"

int main(int argsCount, char *args[]) {
    ExportHTML::exportProductList();
    LoginScreen::start();

    return 0;
}