/*
	Copyright (C) 2012 Alexander Overvoorde

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#include <GL/GL/Shader.hpp>
#include <vector>
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
namespace GL
{
	Shader::Shader(ShaderType::shader_type_t type, std::filesystem::directory_entry entry)
	{
		obj = gc.Create(glCreateShader(type), glDeleteShader);
		std::string str;
		std::ifstream code(entry.path());

		if (code.is_open()) {
			std::string line;
			while (std::getline(code, line)) {
				str += line +'\n';
			}
			code.close();
		}
		else {
			std::cerr << "Error opening file " << std::endl;
		}
		std::cout << "COMPILNING : " << str<< '\n';
		Source(str);
		Compile();
	}
	Shader::Shader()
	{
		//add some code to indicate it has not been initialized, should raise an exception when used if obj is null.

	}
	Shader::Shader( const Shader& other )
	{
		gc.Copy( other.obj, obj );
	}

	Shader::Shader( ShaderType::shader_type_t shader )
	{
		obj = gc.Create( glCreateShader( shader ), glDeleteShader );
	}

	Shader::Shader( ShaderType::shader_type_t shader, const std::string& code )
	{
		obj = gc.Create( glCreateShader( shader ), glDeleteShader );
		Source( code );
		Compile();
	}

	Shader::~Shader()
	{
		gc.Destroy( obj );
	}

	Shader::operator GLuint() const
	{
		return obj;
	}

	const Shader& Shader::operator=( const Shader& other )
	{
		gc.Copy( other.obj, obj, true );
		return *this;
	}
	const Shader& Shader::operator=(Shader& other) 
	{
		gc.Copy(other.obj, obj, true);
		return *this;
	};

	void Shader::Source( const std::string& code )
	{
		const char* c = code.c_str();
		glShaderSource( obj, 1, &c, NULL );
	}

	void Shader::Compile()
	{
		GLint res;

		glCompileShader( obj );
		glGetShaderiv( obj, GL_COMPILE_STATUS, &res );
		std::cout << GetInfoLog();
		if ( res == 0 )
			throw CompileException( GetInfoLog() );
	}

	std::string Shader::GetInfoLog()
	{
		GLint res;
		glGetShaderiv( obj, GL_INFO_LOG_LENGTH, &res );

		if ( res > 0 )
		{
			std::string infoLog( res, 0 );
			glGetShaderInfoLog( obj, res, &res, &infoLog[0] );
			return infoLog;
		} else {
			return "";
		}
	}

	GC Shader::gc;
}