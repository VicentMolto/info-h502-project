#pragma once

#include <glad/glad.h>; // 包含glad来获取所有的必须OpenGL头文件

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>



//(  vs路径,  fs路径 , gs路径 )
class Shader
{
public:
	const char* vs;
	const char* fs;
	const char* gs;
	unsigned int ID;

	Shader(const char* vs, const char* fs, const char* gs = nullptr) {
		this->vs = vs;
		this->fs = fs;
		this->gs = gs;


		// ----VS----
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER); // 创建Shader
		string vertShaderSrc = loadShaderSrc(vs); //读取glsl 到 vertShaderSrc
		const GLchar* vertShader = vertShaderSrc.c_str(); // 把 string转换为 GLchar 
		glShaderSource(vertexShader, 1, &vertShader, NULL);
		glCompileShader(vertexShader);

		checkError(vertexShader, "VS");

		// ----FS----
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		string fragShaderSrc = loadShaderSrc(fs);
		const GLchar* fragShader = fragShaderSrc.c_str();
		glShaderSource(fragmentShader, 1, &fragShader, NULL);
		glCompileShader(fragmentShader);

		checkError(fragmentShader, "FS");

		// ----GS----
		unsigned int geometryShader;
		if (gs != nullptr)
		{
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			string geomShaderSrc = loadShaderSrc(gs);
			const GLchar* geomShader = geomShaderSrc.c_str();
			glShaderSource(geometryShader, 1, &geomShader, NULL);
			glCompileShader(geometryShader);

			checkError(geometryShader, "GS");

		}

		// ----连接 VS 和 PS----
		
		ID = glCreateProgram();	// 创建 program
		glAttachShader(ID, vertexShader);	//	附加 VS
		glAttachShader(ID, fragmentShader); // 附加 PS
		if (gs != nullptr)
		{
			glAttachShader(ID, geometryShader); // 附加 PS
		}
		glLinkProgram(ID);	// 链接 
		checkError(ID, "program");

		// ----清除Shader----
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (gs != nullptr)
		{
			glDeleteShader(geometryShader);
		}
	}

	// ---- 读取 Shader 文件 ----
	string loadShaderSrc(const char* filePath)
	{
		ifstream file;		 // 创建文件
		stringstream buf;	// 创建文件buf
		string ret = "";	// 读取文件到 ret;

		file.open(filePath);

		if (file.is_open()) {
			buf << file.rdbuf(); // 把文件读取到buf
			ret = buf.str();	// 把buf 里的字符 给 ret
		}
		else {
			cout << "Could not open " << filePath << endl;
		}
		file.close();	// 关闭文件

		return ret;
	}

	// -- 使用shader --
	void use()
	{
		glUseProgram(ID);
		//cout << "Shader 使用成功!!" << endl;
	}

	void setBool(const string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setVec2(const string& name, const vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	// ------------------------------------------------------------------------
	void setVec3(const string& name, const vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}


	void setVec4(const string& name, const vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	void setMat3(const string& name, const mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setMat4(const string& name, const mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:

	void checkError(GLuint shader, string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "program")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << type << " Shader 编译错误!!!" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << type << "Shader 编译错误!!!"  <<   "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};



