#include"render.h"
#include<iostream>
#include"Shader.h"
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

 void Renderer::Clear() const
 {
     glClear(GL_COLOR_BUFFER_BIT);
 }

 void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
 {
     shader.Bind();
     va.Bind();
     ib.Bind();
     GLCall(glDrawElements(GL_TRIANGLES, ib.Getcount(), GL_UNSIGNED_INT, nullptr));
 }
