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

namespace HashSum {
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

        int build() {
            return code;
        }

    protected:
        int code;
    };
}


#endif //CPPASSIGNMENT_HASHSUM_HPP
