#pragma once

#include <glad/glad.h>; // include all headfiles for OPENGL

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>



//(  vs path,  fs path , gs path)
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
		vertexShader = glCreateShader(GL_VERTEX_SHADER); // create Shader
		string vertShaderSrc = loadShaderSrc(vs); //read glsl into vertShaderSrc
		const GLchar* vertShader = vertShaderSrc.c_str(); // convert string into GLchar 
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

		// ----connect VS and fs----
		
		ID = glCreateProgram();	// create program
		glAttachShader(ID, vertexShader);	//	add VS
		glAttachShader(ID, fragmentShader); // add fS
		if (gs != nullptr)
		{
			glAttachShader(ID, geometryShader); // add fS
		}
		glLinkProgram(ID);	// link
		checkError(ID, "program");

		// ----clear Shader----
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (gs != nullptr)
		{
			glDeleteShader(geometryShader);
		}
	}

	// ---- read Shader file ----
	string loadShaderSrc(const char* filePath)
	{
		ifstream file;		 // create file
		stringstream buf;	// create file buf
		string ret = "";	// create file to ret;

		file.open(filePath);

		if (file.is_open()) {
			buf << file.rdbuf(); // read into buf
			ret = buf.str();	// read strings of buf into ret
		}
		else {
			cout << "Could not open " << filePath << endl;
		}
		file.close();	// close

		return ret;
	}

	// -- use shader --
	void use()
	{
		glUseProgram(ID);
		//cout << "Shader sucessfully!!" << endl;
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
				std::cout << type << " Shader compiling wrongly!!!" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << type << "Shader compiling wrongly!!!"  <<   "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};

