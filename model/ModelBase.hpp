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

    Object(string str) : Object(new string(str)) { dataType = TYPE_STRING; }

    Object(int integer) : Object(new int(integer)) { dataType = TYPE_INTEGER; }

    Object(vector<ModelBase *> dataArray) :
            Object(new vector<ModelBase *>(dataArray)) { dataType = TYPE_ARRAY_OF_MODELS; }

    operator vector<ModelBase *> *() {
        return static_cast<vector<ModelBase *> *>(value);
    }

    operator int() {
        return *static_cast<int *>(value);
    }

    operator string() {
        return *static_cast<string *>(value);
    }

    Object &operator=(int newValue) {
        freeMem();
        value = new int(newValue);
        dataType = TYPE_INTEGER;
    }

    Object &operator=(string newValue) {
        freeMem();
        value = new string(newValue);
        dataType = TYPE_STRING;
    }

    Object &operator=(vector<ModelBase *> newValue) {
        freeMem();
        value = new vector<ModelBase *>(newValue);
        dataType = TYPE_ARRAY_OF_MODELS;
    }

    operator void *() {
        return value;
    }

    ~Object() {
        freeMem();
    }

protected:
    void *value = nullptr;
    DataType dataType;

    Object(void *value) : value(value) {}

    void freeMem() {
        if (value != nullptr)
            switch (dataType) {
                case TYPE_STRING:
                    delete static_cast<string *>(value);
                    break;
                case TYPE_INTEGER:
                    delete static_cast<int *>(value);
                    break;
                case TYPE_ARRAY_OF_MODELS:
                    delete static_cast<vector<ModelBase *> *>(value);
            }
        value = nullptr;
    }
};

class ModelBase {
public:

    ModelBase() {}

    virtual ModelBase &initialize() {
        /* Assign default value */
        for (int i = 0; i < getFieldCount(); ++i)
            switch (getFieldType(i)) {
                case TYPE_INTEGER:
                    data.push_back(new Object(int(0)));
                    break;
                case TYPE_STRING:
                    data.push_back(new Object(string("")));
                    break;
                case TYPE_ARRAY_OF_MODELS:
                    data.push_back(new Object(vector<ModelBase *>(0)));
                    break;
            }
        return *this;
    }


    virtual Object &operator[](size_t index) {
        return *data[index];
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

    ~ModelBase() {
        data.clear();
    }
protected:
    vector<Object *> data;
    HashSum::Builder *builder;
};

ostream &operator<<(ostream &output, ModelBase &modelBase);

istream &operator>>(istream &input, ModelBase &modelBase);


#endif //CPPASSIGNMENT_MODELBASE_HPP
