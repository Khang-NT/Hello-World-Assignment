//
// Created by blackcat on 04/06/2016.
//

#include "ModelBase.hpp"
#include "../utils/Utils.hpp"

/* Class Object */

void Object::freeMem() {
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

Object::operator vector<ModelBase *> *() {
    return static_cast<vector<ModelBase *> *>(value);
}

Object::operator int() {
    return *static_cast<int *>(value);
}

Object::operator string() {
    return *static_cast<string *>(value);
}

Object::operator void *() {
    return value;
}

Object &Object::operator=(int newValue) {
    freeMem();
    value = new int(newValue);
    dataType = TYPE_INTEGER;
}

Object &Object::operator=(string newValue) {
    freeMem();
    value = new string(newValue);
    dataType = TYPE_STRING;
}

Object &Object::operator=(vector<ModelBase *> newValue) {
    freeMem();
    value = new vector<ModelBase *>(newValue);
    dataType = TYPE_ARRAY_OF_MODELS;
}

Object::~Object() {
    freeMem();
}

/* Class ModelBase */

ModelBase::ModelBase(const ModelBase &model) {
    clearData();
    /* Copy value */
    for (int i = 0; i < model.getFieldCount(); ++i)
        switch (model.getFieldType(i)) {
            case TYPE_INTEGER:
                data.push_back(new Object((int) model[i]));
                break;
            case TYPE_STRING:
                data.push_back(new Object((string) model[i]));
                break;
            case TYPE_ARRAY_OF_MODELS:
                data.push_back(new Object(*model[i].operator vector<ModelBase *> *()));
                break;
        }
    /* copy pointer - using same builder */
    this->builder = model.builder;
}

ModelBase &ModelBase::initialize() {
    data.clear();
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

Object &ModelBase::operator[](size_t index) const {
    return *data[index];
}

ModelBase &ModelBase::with(HashSum::Builder &builder) {
    this->builder = &builder;
    return *this;
}

HashSum::Builder &ModelBase::getBuilder() {
    return *builder;
}

unsigned int ModelBase::getFieldCount() const {
    return 0;
}

DataType ModelBase::getFieldType(int &fieldIndex) const {
    return DataType::TYPE_INTEGER;
}

ModelBase *ModelBase::createVectorItem() {
    return new ModelBase();
}

void ModelBase::clearData() {
    while (!data.empty()) { /* free memory each element of vector */
        delete data.back();
        data.pop_back();
    }
}

ModelBase::~ModelBase() {
    clearData();
}

ostream &operator<<(ostream &output, ModelBase &model) {
    for (int i = 0; i < model.getFieldCount(); ++i) {
        switch (model.getFieldType(i)) {
            case TYPE_INTEGER:
                output << (int) model[i] << endl;
                model.getBuilder().add((int) model[i]);
                break;
            case TYPE_STRING:
                output << (string) model[i] << endl;
                model.getBuilder().add((string) model[i]);
                break;
            case TYPE_ARRAY_OF_MODELS:
                vector<ModelBase *> *dataArray = model[i];
                output << dataArray->size() << endl;
                model.getBuilder().add((int) dataArray->size());

                for (ModelBase *item : *dataArray)
                    output << item->with(model.getBuilder());
                break;
        }
    }
    return output;
}

istream &operator>>(istream &input, ModelBase &model) {
    int *integer = new int;
    string *str = new string;
    for (int i = 0; i < model.getFieldCount(); ++i) {
        switch (model.getFieldType(i)) {
            case TYPE_INTEGER:
                input >> *integer;
                model[i] = *integer;
                model.getBuilder().add(*integer);
                break;
            case TYPE_STRING:
                Utils::getLine(input, *str);
                model[i] = *str;
                model.getBuilder().add(*str);
                break;
            case TYPE_ARRAY_OF_MODELS:
                input >> *integer; // read size of data array
                model.getBuilder().add(*integer);
                vector<ModelBase *> dataArray;
                for (int j = 0; j < *integer; ++j) {
                    ModelBase *temp = model.createVectorItem();
                    input >> temp->with(model.getBuilder());
                    dataArray.push_back(temp);
                }
                model[i] = dataArray;
                break;
        }
    }
    delete str;
    delete integer;
    return input;
}

