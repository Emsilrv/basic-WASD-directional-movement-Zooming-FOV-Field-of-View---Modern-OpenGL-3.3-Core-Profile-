#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "glad.h"

class Shader {
public:
    GLuint ID;
    Shader(const char* vertexSrc, const char* fragmentSrc);

    void Activate();
    void Delete();
};

#endif