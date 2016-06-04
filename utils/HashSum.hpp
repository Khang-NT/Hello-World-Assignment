//
// Created by blackcat on 04/06/2016.
//

#ifndef CPPASSIGNMENT_HASHSUM_HPP
#define CPPASSIGNMENT_HASHSUM_HPP


#include <string>

using namespace std;

//Prime numbers
#define A 76963
#define B 86969

class HashSum {
public:
    HashSum() : HashSum(0) {}

    HashSum(int code) : code(code) {}

    class Builder {
    public:
        Builder() : code(51) {};

        Builder &add(string s) {
            for (int i = 0; i < s.length(); i++)
                code = (code * A) ^ (s[i] * B);
            return *this;
        };

        Builder &add(int v) {
            string s = to_string(v);
            return add(s);
        };

        HashSum *build() {
            return new HashSum(code);
        }

    private:
        int code;
    };

    operator int() {
        return code;
    }

    operator string() {
        return to_string(code);
    }

private:
    int code = 0;
};


#endif //CPPASSIGNMENT_HASHSUM_HPP
