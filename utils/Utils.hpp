//
// Created by root on 28/05/2016.
//

#ifndef ASSIGNMENT_UTILS_HPP
#define ASSIGNMENT_UTILS_HPP


#include <ostream>
#include <fstream>
#include <cstring>
#include "../model/ModelBase.hpp"


namespace Utils {
    void getLine(std::istream &stream, std::string &s);

    /**
     * Require user choose Yes or No
     * @return true if user choose yes.
     */
    bool yesOrNo();

    void clearScreen();

    void pause();

    /**
     * Show sign up form and add new account to AccountManager if sign up success.
     * @param level level account to be created.
     * @see LEVEL_ADMIN, LEVEL_MANAGER, LEVEL_GUEST
     */
    void doSignUp(int level);

    /**
     * Show reset password form to update password of user. <br>
     * Password will be tranformed to hash code.
     * @param userId user ID of account to be updated.
     */
    void doResetPassword(int userId, int accountPosition = -1);


    template<typename T, typename = typename std::enable_if<std::is_base_of<ModelBase, T>::value, T>::type>
    inline T *deserialize(string fileName, string header) throw(const char*) {
        ifstream file(fileName);
        if (file.is_open()) {
            file.exceptions(ifstream::failbit | ifstream::badbit);
            if (header != "") {
                string fileHeader;
                getLine(file, fileHeader);
                if (fileHeader != header) {
                    file.close();
                    throw "Unknown file header.";
                }
            }
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

    inline void serialize(ModelBase &model, string fileName, string header, const char *errorConfirmMessage) {
        ofstream file;
        file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        try {
            file.open(fileName);
            if (header != "")
                file << header << endl;
            HashSum::Builder builder;
            file << model.with(builder);
            file << builder.build();
            file.close();
        } catch (std::ofstream::failure &e) {
            printf("Occurs an error while writing to file %s : %s\n"
                           "%s\n"
                           "Do you want to retry (y/n)? ",
                   fileName.c_str(), e.what(), errorConfirmMessage);
            if (Utils::yesOrNo())
                serialize(model, fileName, header, errorConfirmMessage);
        }
    };
}


#endif //ASSIGNMENT_UTILS_HPP
