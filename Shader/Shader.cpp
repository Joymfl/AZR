//
// Created by joydm on 24-09-2025.
//
#include <fstream>
#include <iostream>
#include <string>

#include "Shader.h"
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            vShaderFile.open( "../shaders/"+vertexPath);
            fShaderFile.open("../shaders/"+fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure e) {
            std::cout<<"ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ"<< std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        //compilation
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            std::cout<<"ERROR:SHADER::VERTEX::COMPILATION_FAILED\n"<< std::endl;
        }

        // fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            std::cout<<"ERROR:SHADER::FRAGMENT::COMPILATION_FAILED\n"<< std::endl;
        }

        // shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
           glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            std::cout<<"ERROR:SHADER::PROGRAM::LINKING_FAILED\n"<< std::endl;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
}
