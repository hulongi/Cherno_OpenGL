#include"render.h"
#include<iostream>
 void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

 bool GLLogCall(const char* function, const char* FILE, int line)
{
    while (GLenum error = glGetError())
    {
        cout << "[OpenGL Error](" << error << "):" << function << " " << FILE << ":" << line << endl;
        return false;
    }
    return true;
}