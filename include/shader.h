#ifndef SHADER_H //include guards, will prevent the file from recursively defining things we've already defined
#define SHADER_H

#include <glad/glad.h> //include glad to get all the OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        //program ID
        unsigned int ID;

        //constructor reads and builds the shader
        Shader(const char* vertexPath, const char* fragmentPath) //constructor requires the filepaths
        {
            //1) retrieve the vertex/fragment source code from filepath
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            //ensure ifstream objects can throw exceptions
            vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                //open files
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;
                //read file's buffer contents into streams
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                //close file handlers
                vShaderFile.close();
                fShaderFile.close();
                //convert stream to string
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch(std::ifstream::failure e)
            {
                std::cout << "SHADER ERROR::COULDN'T READ SHADER FILE" << std::endl;
            }
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();

            //2) compile shaders
            unsigned int vertex, fragment;
            int success;
            char infoLog[512];
            
            //vertex shader
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, nullptr);
            glCompileShader(vertex);
            //print errors if there are any
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
                std::cout << "SHADER ERROR::COULDN'T COMPILE VERTEX SHADER" << infoLog << std::endl;
            }
            
            //fragment shader
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, nullptr);
            glCompileShader(fragment);
            //errors yay
            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
                std::cout << "SHADER ERROR::COULDN'T COMPILE FRAGMENT SHADER" << infoLog << std::endl;
            }

            //shader program
            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);
            //print linking errors
            glGetProgramiv(ID, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(ID, 512, nullptr, infoLog);
                std::cout << "SHADER PROGRAM ERROR::LINKING FAILED" << infoLog << std::endl;
            }

            //delete the shaders since they're linked and no longer needed
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }
        //use/activate the shader
        void use()
        {
            glUseProgram(ID);
        }
        //utility uniform functions
        void setBool(const std::string &name, bool value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }
        void setInt(const std::string &name, int value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }
        void setFloat(const std::string &name, float value) const
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }
        void setVec3(const std::string &name, float valueA, float valueB, float valueC) const
        {
            glUniform3f(glGetUniformLocation(ID, name.c_str()), valueA, valueB, valueC);
        }
};

#endif

