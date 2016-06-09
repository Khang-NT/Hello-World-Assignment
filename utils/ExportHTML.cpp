//
// Created by blackcat on 08/06/2016.
//

#include "ExportHTML.hpp"
#include "../template/AccountListTemplate.hpp"
#include "DateTimeFormat.hpp"
#include "../template/ProductListTemplate.hpp"
#include "../model/ProductManager.hpp"

#include <algorithm>

using namespace std;

namespace ExportHTML {

    void open(string filename) {
#ifdef _WIN32
        system(("cmd /c start " + filename).c_str());
#elif __APPLE__
        system(("open " + filename).c_str());
#else
        system(("xdg-open " + filename).c_str());
#endif
    }

    void replaceString(std::string &subject, const std::string &search,
                       const std::string &replace, unsigned repeatTime = 1) {
        unsigned long pos = 0;
        for (int i = 0; i < repeatTime; ++i) {
            pos = subject.find(search, pos);
            subject.replace(pos, search.length(), replace);
        }
    }

    void exportAccountList() {
        string html = string(ACCOUNT_LIST_TEMPLATE, ACCOUNT_LIST_TEMPLATE + ACCOUNT_LIST_TEMPLATE_LEN);

        string time = DateTimeFormat::format(std::time(0), "dd/MM/yyyy HH:mm:ss");
        replaceString(html, "%time%", time);
        int accountCount = AccountManager::getAccountCount();
        replaceString(html, "%total%", to_string(accountCount));

        string rows = "";
        for (int i = 0; i < accountCount; ++i) {
            string row_template = string(ROW_TEMPLATE, ROW_TEMPLATE + ROW_TEMPLATE_LEN);
            Account account = AccountManager::getInstance()->getAccountAt(i);
            replaceString(row_template, "%odd%", to_string(i % 2), 6);
            replaceString(row_template, "%userId%", to_string(account.getUserId()));
            replaceString(row_template, "%level%", account.getLevelAsString());
            replaceString(row_template, "%staffId%", account.getStaffId());
            replaceString(row_template, "%userName%", account.getUserName());
            replaceString(row_template, "%lastModified%",
                          DateTimeFormat::format(account.getLastModified(), "yyyy-MM-dd HH:mm:ss"));
            replaceString(row_template, "%lastLogin%",
                          DateTimeFormat::format(account.getLastLoginTime(), "yyyy/MM/dd hh:mm:ss aa"));
            rows += row_template;
        }

        replaceString(html, "%rows%", rows);

        ofstream f("account-snapshot.html");
        f << html;
        f.close();
        open("account-snapshot.html");
    }

    void exportProductList() {
        string html = string(PRODUCT_LIST_TEMPLATE, PRODUCT_LIST_TEMPLATE + PRODUCT_LIST_TEMPLATE_LEN);
        string time = DateTimeFormat::format(std::time(0), "dd/MM/yyyy HH:mm:ss");
        replaceString(html, "%time%", time);
        int productCount = ProductManager::getProductCount();
        replaceString(html, "%total%", to_string(productCount));

        string rows = "";
        for (int i = 0; i < productCount; ++i) {
            string row_template = string(PRODUCT_ROW_TEMPLATE, PRODUCT_ROW_TEMPLATE + PRODUCT_ROW_TEMPLATE_LEN);
            Product product = ProductManager::getProductAt(i);
            replaceString(row_template, "%odd%", to_string(i % 2), 8);
            replaceString(row_template, "%id%", to_string(product.getProductId()));
            replaceString(row_template, "%category%", product.getCategory());
            replaceString(row_template, "%name%", product.getProductName());
            replaceString(row_template, "%price%", to_string(product.getPrice()) + "$");
            replaceString(row_template, "%warranty%", product.getWarrantyInfo());
            replaceString(row_template, "%manufacturer%", product.getManufacturer());
            replaceString(row_template, "%available%", to_string(product.getItemCount()));
            replaceString(row_template, "%lastUpdate%",
                          DateTimeFormat::format(product.getLastModifiedTime(), "yyyy-MM-dd HH:mm:ss"));

            rows += row_template;
        }

        replaceString(html, "%rows%", rows);

        ofstream f("items-snapshot.html");
        f << html;
        f.close();
        open("items-snapshot.html");
    }
}

