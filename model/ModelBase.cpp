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
            case TYPE_MAP_OF_MODELS:
                unordered_map<int, ModelBase *> mapModels = *(unordered_map<int, ModelBase *> *) model[i];
                output << mapModels.size() << endl;
                model.getBuilder().add((int) mapModels.size());
                for (auto item : mapModels) {
                    output << item.first << endl;
                    model.getBuilder().add(item.first);
                    output << item.second->with(model.getBuilder()) << endl;
                }
                break;
        }
    }
    return output;
}

istream &operator>>(istream &input, ModelBase &model) {
    int integer;
    string str;
    for (int i = 0; i < model.getFieldCount(); ++i) {
        switch (model.getFieldType(i)) {
            case TYPE_INTEGER:
                input >> integer;
                model[i] = integer;
                model.getBuilder().add(integer);
                break;
            case TYPE_STRING:
                Utils::getLine(input, str);
                model[i] = str;
                model.getBuilder().add(str);
                break;
            case TYPE_MAP_OF_MODELS:
                input >> integer;
                model.getBuilder().add(integer);
                unordered_map<int, ModelBase *> mapModels;
                for (int j = 0; j < integer; ++j) {
                    ModelBase *temp = model.createVectorItem();
                    input >> integer;
                    input >> temp->with(model.getBuilder());
                    mapModels[integer] = temp;
                }
                model[i] = mapModels;
                break;
        }
    }
    return input;
}


