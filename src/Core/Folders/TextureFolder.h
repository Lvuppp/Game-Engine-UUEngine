#ifndef TEXTUREFOLDER_H
#define TEXTUREFOLDER_H

#include "Core/Folders/BaseFolder.h"

#include <map>

class QOpenGLTexture;

class cTextureManager : public cBaseFolder
{
public:
    cTextureManager() = default;
    ~cTextureManager() = default;

    void clean();

    QOpenGLTexture* loadTexture(std::string_view objectPath);

private:
    std::map<uint32_t, QOpenGLTexture*> m_textures;
};

#endif // TEXTUREFOLDER_H
