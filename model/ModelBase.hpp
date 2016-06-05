//
// Created by blackcat on 04/06/2016.
//

#ifndef CPPASSIGNMENT_MODELBASE_HPP
#define CPPASSIGNMENT_MODELBASE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include "../utils/HashSum.hpp"

using namespace std;

class ModelBase;

enum DataType {
    TYPE_INTEGER,
    TYPE_STRING,
    TYPE_ARRAY_OF_MODELS
};

/**
 * Object wrapper (int, string, vector<ModelBase*>)
 */
class Object {
public:
    Object(void *value) : value(value) {}

    Object(string str) : Object((void *) &str) {}

    Object(int integer) : Object((void *) &integer) {}

    Object(vector<ModelBase *> dataArray) : Object((void *) &dataArray) {}

    operator int() {
        return *static_cast<int *>(value);
    }

    operator string() {
        return *static_cast<string *>(value);
    }

    operator vector<ModelBase *>() {
        return *static_cast<vector<ModelBase *> *>(value);
    }

    operator void *() {
        return value;
    }

protected:
    void *value;
};

class ModelBase {
public:

    ModelBase() {
        /* Assign default value */
        for (int i = 0; i < getFieldCount(); ++i)
            switch (getFieldType(i)) {
                case TYPE_INTEGER:
                    data.push_back(new int(0));
                    break;
                case TYPE_STRING:
                    data.push_back(new Object(""));
                    break;
                case TYPE_ARRAY_OF_MODELS:
                    data.push_back(new unordered_map<int, ModelBase *>);
                    break;
            }
    }


    virtual Object &operator[](size_t index) {
        return data[index];
    }

    ModelBase &with(HashSum::Builder &builder) {
        this->builder = &builder;
        return *this;
    }

    HashSum::Builder &getBuilder() {
        return *builder;
    }

    virtual unsigned int getFieldCount() {
        return 0;
    }

    virtual DataType getFieldType(int &fieldIndex) {
        return DataType::TYPE_INTEGER;
    };

    virtual ModelBase *createVectorItem() {
        return new ModelBase();
    }

protected:
    vector<Object> data;
    HashSum::Builder *builder;
};

ostream &operator<<(ostream &output, ModelBase &modelBase);

istream &operator>>(istream &input, ModelBase &modelBase);


#endif //CPPASSIGNMENT_MODELBASE_HPP
