#pragma once
#include<GL/glew.h>
#include"VertexArray.h"
#include"IndexBuffer.h"
//#include"Shader.h"
class Shader;
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLLogCall(#x,__FILE__,__LINE__))
using namespace std;
 void GLClearError();
 bool GLLogCall(const char* function, const char* FILE, int line);

 class Renderer
 {
 public:
     void Clear() const;
     void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
 };


