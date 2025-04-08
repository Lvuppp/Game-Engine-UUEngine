#include "CustomModel.h"

// cCustomModel::cCustomModel()
//     : cModel(ModelType::CustomModel)
// {

// }

// cCustomModel::cCustomModel(QVector<cModelParticle *> modelParticles) : cModel(ModelType::CustomModel)
// {
//     m_modelParticles.append(modelParticles);
//     p_modelType = ModelType::CustomModel;
// }

// cCustomModel::~cCustomModel()
// {
// //    for(auto it = m_modelParticles.begin(), end = m_modelParticles.end(); it != end; it++ ){
// //        delete it;
// //    }

//     m_modelParticles.clear();

// }


// void cCustomModel::drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions)
// {
//     for (const auto& model : m_modelParticles)
//     {
//         model->drawModelParticle(modelMatrix, shaderProgram, isUsingTexture, functions);
//     }
// }

// void cCustomModel::setModel(std::vector<cModelParticle *> modelParticles)
// {
//     for(auto it = m_modelParticles.begin(), end = m_modelParticles.end(); it != end; it++ ){
//         delete *it;
//     }

//     m_modelParticles.clear();
//     m_modelParticles.append(modelParticles);
// }

// cModelParticle *cCustomModel::modelParticle(const int &index)
// {
//     return m_modelParticles.at(index);
// }

// const std::vector<std::unique_ptr<cModelParticle>>& cCustomModel::allModelParticle() const
// {
//     return m_modelParticles;
// }
