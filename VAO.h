#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "glad.h"
#include "VBO.h"

class VAO {
public:
    GLuint ID;
    VAO();

    void LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, const void* offset);
    void Bind();
    void Unbind();
    void Delete();
};

#endif
