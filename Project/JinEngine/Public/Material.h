#pragma once
#include <string>
#include <unordered_map>
#include <variant>
#include "glm.hpp"
#include "Texture.h"

class RenderManager;
class ObjectManager;
class Shader;
class Texture;
class Mesh;

using GLuint = unsigned int;
using UniformValue = std::variant<
    int,
    float,
    glm::vec2,
    glm::vec3,
    glm::vec4,
    glm::mat4
>;

class Material {
    friend RenderManager;

public:
    Material(Shader* _shader) : shader(_shader), isInstancingEnabled(false){}
    virtual ~Material() = default;
    virtual bool IsCompute() const { return false; }

    void SetTexture(const std::string& uniformName, Texture* texture)
    {
        textures[uniformName] = texture;
    }

    void SetUniform(const std::string& name, UniformValue value)
    {
        uniforms[name] = value;
    }

    [[nodiscard]] bool IsInstancingSupported() const;

    void EnableInstancing(bool enable, Mesh* mesh);

protected:
    void Bind() const;

    void UnBind() const;

    virtual void SendData();

    void SendUniforms();

    Shader* shader;
    std::unordered_map<std::string, UniformValue> uniforms;
    bool isInstancingEnabled;

private:
    void SendTextures();

    [[nodiscard]] bool HasTexture() const { return !textures.empty(); }

    [[nodiscard]] bool HasTexture(Texture* texture) const;

    [[nodiscard]] bool HasShader(Shader* shader_) const;

    [[nodiscard]] Shader* GetShader() const { return shader; }


    std::unordered_map<std::string, Texture*> textures;
};

class ComputeMaterial : public Material
{
    struct ImageBind
    {
        Texture* tex;
        ImageAccess access;
        ImageFormat format;
        int level;
    };
    Texture* destinationTexture;
    std::unordered_map<std::string, ImageBind> images;
public:
    ComputeMaterial(Shader* _shader) : Material(_shader) {}
    [[nodiscard]] bool IsCompute() const override { return true; }
    void SetImage(const std::string& uniformName, Texture* texture, ImageAccess access, ImageFormat format, int level)
    {
        ImageBind img = { texture,access,format,level};
        images[uniformName] = img;
        if (uniformName == "u_Dst")
            destinationTexture = texture;
    }
    [[nodiscard]] Texture* GetDstTexture() const { return destinationTexture; }
    void EnableInstancing(bool enable, Mesh* mesh) = delete;
    void SetTexture(const std::string& uniformName, Texture* texture) = delete;
    void SendData() override;
};