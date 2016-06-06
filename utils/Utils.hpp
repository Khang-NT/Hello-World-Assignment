//
// Created by root on 28/05/2016.
//

#ifndef ASSIGNMENT_UTILS_HPP
#define ASSIGNMENT_UTILS_HPP


#include <iosfwd>
#include <istream>
#include <iostream>
#include <fstream>
#include "../model/ModelBase.hpp"

namespace Utils {
    void getLine(std::istream &stream, std::string &s);

    /**
     * Require user choose Yes or No
     * @return true if user choose yes.
     */
    bool yesOrNo();

    void clearScreen();

    /**
     * Show sign up form and add new account to AccountManager if sign up success.
     * @param accountType account type to create.
     * @see Account::TYPE_ADMIN Account::TYPE_MANAGER Account::TYPE_CUSTOMER
     */
    void doSignUp(int accountType);

    template<typename T, typename = typename std::enable_if<std::is_base_of<ModelBase, T>::value, T>::type>
    inline T *deserialize(string fileName) throw(const char*) {
        ifstream file(fileName);
        if (file.is_open()) {
            file.exceptions(ifstream::failbit | ifstream::badbit);
            HashSum::Builder builder;
            T *result = new T();
            result->initialize();
            try {
                file >> result->with(builder);
                int hashCode;
                file >> hashCode;
                file.close();
                if (hashCode == builder.build())
                    return result;
                else
                    throw "Hash sum mismatch.";
            } catch (std::ios_base::failure &) {
                file.close();
                throw "File struct invalid.";
            }
        } else
            throw "File does not exist!";
    };

    inline void serialize(ModelBase &model, string fileName) throw(const char*) {
        ofstream file;
        file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        try {
            file.open(fileName);
            HashSum::Builder builder;
            file << model.with(builder);
            file << builder.build();
            file.close();
        } catch (std::ofstream::failure &e) {
            throw e.what();
        }
    };
}


#endif //ASSIGNMENT_UTILS_HPP
