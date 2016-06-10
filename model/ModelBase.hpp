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
    operator vector<ModelBase *> *();

    operator int();

    operator string();

    operator void *();

    /* operator = (copy assignment) */
    Object &operator=(int newValue);

    Object &operator=(string newValue);

    Object &operator=(vector<ModelBase *> newValue);

    /* Destructor */
    ~Object();

protected:
    void *value = nullptr;
    DataType dataType;

    Object(void *value) : value(value) {}

    void freeMem();
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
    ModelBase(const ModelBase &model);

    /* Main abstract methods */

    /**
     * IMPORTANT! Call this first, before everythings.
     * @return (ModelBase&) reference itself.
     */
    virtual ModelBase &initialize();


    virtual Object &operator[](size_t index) const;

    /**
     * Get number of fields (columns) in data table.
     * @return (int) number of fields (columns).
     */
    virtual unsigned int getFieldCount() const;

    /**
     * Get field (column) type at filedIndex.
     * @param fieldIndex field (column) index.
     * @return (DataType) data type.
     * @see enum DataType.
     */
    virtual DataType getFieldType(int &fieldIndex) const;;

    virtual ModelBase *createVectorItem();

    void clearData();

    ModelBase &with(HashSum::Builder &builder);

    HashSum::Builder &getBuilder();

    ~ModelBase();
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
