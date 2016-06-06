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
    /* Constructors */
    Object(string str) : Object(new string(str)) { dataType = TYPE_STRING; }

    Object(int integer) : Object(new int(integer)) { dataType = TYPE_INTEGER; }

    Object(vector<ModelBase *> dataArray) :
            Object(new vector<ModelBase *>(dataArray)) { dataType = TYPE_ARRAY_OF_MODELS; }

    /* Operator conversion */
    operator vector<ModelBase *> *() {
        return static_cast<vector<ModelBase *> *>(value);
    }

    operator int() {
        return *static_cast<int *>(value);
    }

    operator string() {
        return *static_cast<string *>(value);
    }

    operator void *() {
        return value;
    }

    /* operator = (copy assignment) */
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

    /* Destructor */
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

/**
 * ModelBase is abstract class, provide ability serializing and deserializing (as string)
 * and common interfaces to interact with data.
 * to stream. Class design as a table, rows store in vector<Object *>, column with 3 data type.
 * @see class Object
 * @see enum DataType
 */
class ModelBase {
public:

    ModelBase() {}

    /* Copy constructor */
    ModelBase(ModelBase &model) {
        data.clear();
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

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (ModelBase&) reference itself.
     */
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

    /**
     * Get number of fields (columns) in data table.
     * @return (int) number of fields (columns).
     */
    virtual unsigned int getFieldCount() {
        return 0;
    }

    /**
     * Get field (column) type at filedIndex.
     * @param fieldIndex field (column) index.
     * @return (DataType) data type.
     * @see enum DataType.
     */
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

/**
 * Serialize to output stream.
 * @param output (ostream)
 * @param model (ModelBase&)
 * @return (ostream &)
 */
ostream &operator<<(ostream &output, ModelBase &modelBase);

/**
 * Deserialize from input stream.
 * @param input (istream)
 * @param model (ModelBase&)
 * @return (istream&)
 */
istream &operator>>(istream &input, ModelBase &modelBase);


#endif //CPPASSIGNMENT_MODELBASE_HPP
