#include "model.h"

Model::Model(Model::ModelType type)
    : p_modelType(type)
{
}

Model::ModelType Model::modelType()
{
    return p_modelType;
}
