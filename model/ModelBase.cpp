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
            case TYPE_ARRAY_OF_MODEL:
                vector<ModelBase *> modelArray = *(vector<ModelBase *> *) model[i];
                output << modelArray.size() << endl;
                model.getBuilder().add((int) modelArray.size());
                for (int j = 0; j < modelArray.size(); ++j)
                    output << modelArray[i]->with(model.getBuilder()) << endl;
                break;
            default:
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
            case TYPE_ARRAY_OF_MODEL: /* TYPE_ARRAY_OF_MODEL */
                input >> integer;
                model.getBuilder().add(integer);
                vector<ModelBase *> modelArray;
                for (int j = 0; j < integer; ++j) {
                    ModelBase *temp = model.createVectorItem();
                    input >> temp->with(model.getBuilder());
                    modelArray.push_back(temp);
                }
                model[i] = modelArray;
                break;
            default:
                break;
        }
    }
    return input;
}


