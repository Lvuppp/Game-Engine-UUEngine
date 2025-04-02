#include "Model.h"

cModel::cModel(cModel::ModelType type)
    : p_modelType(type)
{
}

cModel::ModelType cModel::modelType()
{
    return p_modelType;
}
