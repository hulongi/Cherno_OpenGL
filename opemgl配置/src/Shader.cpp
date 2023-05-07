#include"Shader.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath),m_RenderID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RenderID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RenderID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RenderID));
}

void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2, float v3)
{
   
        GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

 int Shader::GetUniformLocation(const std::string name)
{
     if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
         return m_UniformLocationCache[name];

    GLCall( int location=glGetUniformLocation(m_RenderID, name.c_str()));
    if (location == -1)
    {
        cout << "Waring Uniform" << name<<"Doesn't exit " << endl;
    }
    m_UniformLocationCache[name] = location;
	return location;
}

 unsigned int Shader::CreateShader(const string& vertexShader, const string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

 ShaderProgramSource Shader::ParseShader(const string& filepath)//读取并分离着色器
{
    ifstream stream(filepath);
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != string::npos)
        {
            if (line.find("vertex") != string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }

    }
    return{ ss[0].str(),ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const string& source)//编译着色器
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Faild to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "Shader" << endl;
        cout << message << endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}
