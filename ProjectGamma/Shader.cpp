#include "Shader.h"
#include <string>
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

void Shader::loadVertex(const std::string shaderPath)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    vertexShaderID_ = glCreateShader(GL_VERTEX_SHADER);

    std::string ShaderCode;
    std::ifstream ShaderStream(shaderPath, std::ios::in);
    if (ShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << ShaderStream.rdbuf();
        ShaderCode = sstr.str();
        //std::cout << VertexShaderCode << "\n";
        ShaderStream.close();
    }

    printf("Компиляция шейдера: %s\n", shaderPath.c_str());
    const char* SourcePointer = ShaderCode.c_str();
    std::cout << SourcePointer << std::endl;
    glShaderSource(vertexShaderID_, 1, &SourcePointer, NULL);
    glCompileShader(vertexShaderID_);

    glGetShaderiv(vertexShaderID_, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertexShaderID_, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(vertexShaderID_, InfoLogLength, NULL, &ShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &ShaderErrorMessage[0]);
    }
}

void Shader::loadFragment(const std::string shaderPath)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    fragmentShaderID_ = glCreateShader(GL_FRAGMENT_SHADER);

    std::string ShaderCode;
    std::ifstream ShaderStream(shaderPath, std::ios::in);
    if (ShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << ShaderStream.rdbuf();
        ShaderCode = sstr.str();
        //std::cout << VertexShaderCode << "\n";
        ShaderStream.close();
    }

    printf("Компиляция шейдера: %s\n", shaderPath.c_str());
    const char* SourcePointer = ShaderCode.c_str();
    std::cout << SourcePointer << std::endl;
    glShaderSource(fragmentShaderID_, 1, &SourcePointer, NULL);
    glCompileShader(fragmentShaderID_);

    glGetShaderiv(fragmentShaderID_, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragmentShaderID_, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(fragmentShaderID_, InfoLogLength, NULL, &ShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &ShaderErrorMessage[0]);
    }
}

void Shader::loadGeometry(const std::string shaderPath)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    geometryShaderID_ = glCreateShader(GL_GEOMETRY_SHADER);

    std::string ShaderCode;
    std::ifstream ShaderStream(shaderPath, std::ios::in);
    if (ShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << ShaderStream.rdbuf();
        ShaderCode = sstr.str();
        //std::cout << VertexShaderCode << "\n";
        ShaderStream.close();
    }

    printf("Компиляция шейдера: %s\n", shaderPath.c_str());
    const char* SourcePointer = ShaderCode.c_str();
    std::cout << SourcePointer << std::endl;
    glShaderSource(geometryShaderID_, 1, &SourcePointer, NULL);
    glCompileShader(geometryShaderID_);

    glGetShaderiv(geometryShaderID_, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(geometryShaderID_, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(geometryShaderID_, InfoLogLength, NULL, &ShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &ShaderErrorMessage[0]);
    }
}

void Shader::linkProgram()
{
    program_ = glCreateProgram();

    GLint Result = GL_FALSE;
    int InfoLogLength;

    fprintf(stdout, "Создаем шейдерную программу и привязываем шейдеры к нейn");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vertexShaderID_);
    glAttachShader(ProgramID, fragmentShaderID_);
    if (geometryShaderID_ >= 0)
        glAttachShader(ProgramID, geometryShaderID_);
    glLinkProgram(ProgramID);

    // Проверяем шейдерную программу
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
    }

    glDeleteShader(vertexShaderID_);
    glDeleteShader(fragmentShaderID_);
    if (geometryShaderID_ >= 0)
        glDeleteShader(geometryShaderID_);

    program_ = ProgramID;

    vertexShaderID_ = -1;
    fragmentShaderID_ = -1;
    geometryShaderID_ = -1;
}

GLuint Shader::getProgram()
{
    return program_;
}

void Shader::releaseProgram()
{
    glDeleteProgram(program_);
    program_ = -1;
}

void Shader::setUniform(const std::string name, bool value)
{
    if (uniformOffset_.find(name) == uniformOffset_.end()) {

        uniformOffset_[name] = glGetUniformLocation(program_, name.c_str());
    }
    GLuint loc = /*glGetUniformLocation(program_, name)*/uniformOffset_[name];

    glUniform1i(loc, value);
}

void Shader::setUniform(const std::string name, int value)
{
    if (uniformOffset_.find(name) == uniformOffset_.end()) {

        uniformOffset_[name] = glGetUniformLocation(program_, name.c_str());
    }
    GLuint loc = /*glGetUniformLocation(program_, name)*/uniformOffset_[name];

    glUniform1i(loc, value);
}

void Shader::setUniform(const std::string name, float value)
{
    if (uniformOffset_.find(name) == uniformOffset_.end()) {

        uniformOffset_[name] = glGetUniformLocation(program_, name.c_str());
    }
    GLuint loc = /*glGetUniformLocation(program_, name)*/uniformOffset_[name];

    glUniform1f(loc, value);
}

void Shader::setUniform(const std::string name, glm::vec3& value)
{
    if (uniformOffset_.find(name) == uniformOffset_.end()) {

        uniformOffset_[name] = glGetUniformLocation(program_, name.c_str());
    }
    GLuint loc = /*glGetUniformLocation(program_, name)*/uniformOffset_[name];

    glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::setUniform(const std::string name, glm::vec2& value)
{
    if (uniformOffset_.find(name) == uniformOffset_.end()) {

        uniformOffset_[name] = glGetUniformLocation(program_, name.c_str());
    }
    GLuint loc = /*glGetUniformLocation(program_, name)*/uniformOffset_[name];

    glUniform2f(loc, value.x, value.y);
}

void Shader::setUniform(const std::string name, glm::vec4& value)
{
    if (uniformOffset_.find(name) == uniformOffset_.end()) {

        uniformOffset_[name] = glGetUniformLocation(program_, name.c_str());
    }
    GLuint loc = /*glGetUniformLocation(program_, name)*/uniformOffset_[name];

    glUniform4f(loc, value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const std::string name, glm::mat3& value)
{
    if (uniformOffset_.find(name) == uniformOffset_.end()) {

        uniformOffset_[name] = glGetUniformLocation(program_, name.c_str());
    }
    GLuint loc = /*glGetUniformLocation(program_, name)*/uniformOffset_[name];

    glUniformMatrix3fv(loc, 1, 0, glm::value_ptr(value));
}

void Shader::setUniform(const std::string name, glm::mat4& value)
{
    if (uniformOffset_.find(name) == uniformOffset_.end()) {

        uniformOffset_[name] = glGetUniformLocation(program_, name.c_str());
    }
    GLint loc = /*glGetUniformLocation(program_, name)*/uniformOffset_[name];
    //if (loc < 0) std::cout << name << " not found in shader " << program_ << std::endl;
    glUniformMatrix4fv(loc, 1, 0, glm::value_ptr(value));
}

void Shader::setTexture3D(const std::string name, GLuint value)
{
    if (textureUniformOffset_.find(name) == textureUniformOffset_.end()) {

        TextureUniform uniform;
        uniform.offset = glGetUniformLocation(program_, name.c_str());
        uniform.textureIndex = textureCount;
        textureCount++;

        textureUniformOffset_[name] = uniform;
    }

    TextureUniform uniform = textureUniformOffset_[name];
    
    glActiveTexture(GL_TEXTURE0 + uniform.textureIndex);
    glBindTexture(GL_TEXTURE_3D, value);
    glUniform1i(uniform.offset, uniform.textureIndex);
    glActiveTexture(0);
}

void Shader::setTexture2D(const std::string name, GLuint value)
{
    if (textureUniformOffset_.find(name) == textureUniformOffset_.end()) {

        TextureUniform uniform;
        uniform.offset = glGetUniformLocation(program_, name.c_str());
        uniform.textureIndex = textureCount;
        textureCount++;

        textureUniformOffset_[name] = uniform;
    }

    TextureUniform uniform = textureUniformOffset_[name];

    glActiveTexture(GL_TEXTURE0 + uniform.textureIndex);
    glBindTexture(GL_TEXTURE_2D, value);
    glUniform1i(uniform.offset, uniform.textureIndex);
    glActiveTexture(0);
}

GLuint Texture(glm::vec4 color)
{
    GLuint texID_;
    glGenTextures(1, &texID_);
    glBindTexture(GL_TEXTURE_2D, texID_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    unsigned char image[] = {color.r * 255, color.g * 255, color.b * 255, color.a * 255};

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + int((float)sizeof(image) /width/height/3), width, height, 0, GL_RGB + int((float)sizeof(image) / width / height / 3), GL_UNSIGNED_BYTE, image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texID_;
}

GLuint Texture(std::string filePath)
{
    GLuint texID_;
    glGenTextures(1, &texID_);
    glBindTexture(GL_TEXTURE_2D, texID_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    int width, height;
    unsigned char* image = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    if (sizeof(image) == 0) {
        printf("File didnt open");
    }
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + int((float)sizeof(image) /width/height/3), width, height, 0, GL_RGB + int((float)sizeof(image) / width / height / 3), GL_UNSIGNED_BYTE, image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texID_;
}