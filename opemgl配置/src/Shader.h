#pragma once
#include<string>
#include"render.h"
#include<unordered_map>
struct ShaderProgramSource//存放分离的着色器
{
	std::string VertexSource;
	std::string FragmentSource;
};
class Shader
{
private:
	unsigned int m_RenderID;
	std::string m_FilePath;
	std::unordered_map<std::string, int > m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void UnBind() const;
	//统一变量
	void SetUniform4f(const std::string name, float v0, float v1, float v2, float v3);
private:
	unsigned int CompileShader(unsigned int type, const string& source);
	ShaderProgramSource ParseShader(const string& filepath);
	unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
	 int GetUniformLocation(const std::string name);
};
