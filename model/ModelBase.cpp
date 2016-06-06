//
// Created by blackcat on 04/06/2016.
//

#include "ModelBase.hpp"
#include "../utils/Utils.hpp"

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


