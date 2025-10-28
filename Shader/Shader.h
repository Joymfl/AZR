//
// Created by joydm on 24-09-2025.
//

#pragma once
#ifndef AZR_ENGINE_SHADER_H
#define AZR_ENGINE_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
public:
    unsigned int ID;
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const {
        glUseProgram(ID);
    }

    void destroy() const {
        glDeleteProgram(ID);
    }
    ~Shader() {
        destroy();
    }

    // utils
    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setVec3(const std::string &name, float x, float y , float z) const {
        const GLfloat vec3[] = {x,y,z};
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1,vec3);
    }
    void setMat4f(const std::string &name, glm::mat4 value) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),1,GL_FALSE,  glm::value_ptr(value));
    }
};


#endif // AZR_ENGINE_SHADER_H
