//
// Created by Echo on 2023/11/18.
//

#ifndef COSMOS_MODEL_H
#define COSMOS_MODEL_H

#include "Global/Typedefs.h"
#include "Platform/OpenGL/Shader.h"
#include "Platform/OpenGL/Texture.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "assimp/scene.h"
#include <string>

#include <vector>
class VertexBufferObject;
class ElementBufferObject;
class VertexArrayObject;
class Texture;


struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoord;
  glm::vec3 Tangent;
  glm::vec3 Bitangent;
};

class Mesh {
public:
  Mesh(const std::vector<Vertex>& vertices,
    const std::vector<uint32> &indices, const std::vector<Texture>& texture);
  ~Mesh();
  void Draw(Shader& shader);

private:
  VertexArrayObject* m_VAO;
  VertexBufferObject* m_VBO;
  ElementBufferObject* m_EBO;

  std::vector<Vertex> m_vertices;
  std::vector<uint32> m_indices;
  std::vector<Texture> m_textures;

  void SetupMesh();
};

class Model {
public:
  void Draw(Shader& shader);

private:
  std::string m_path;
  std::string m_directory;
  std::vector<Mesh> m_meshes;
  std::vector<Texture> m_textures_loaded;
  uint32 m_mesh_count;

  void LoadModel(const std::string& path);
  void ProcessNode(aiNode* node, const aiScene* scene);
  Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType type_name);
};

#endif // COSMOS_MODEL_H
