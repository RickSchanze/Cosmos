//
// Created by Echo on 2023/11/18.
//

#include "Resource/Model.h"

#include "Core/Log/Logger.h"
#include "Platform/OpenGL/ElementBufferObject.h"
#include "Platform/OpenGL/Texture.h"
#include "Platform/OpenGL/VertexArrayObject.h"
#include "Platform/OpenGL/VertexBufferObject.h"
#include "Resource/Image.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32> &indices, const std::vector<Texture> &texture)
    : m_vertices(vertices), m_textures(texture), m_indices(indices) {}

Mesh::~Mesh() {
 // TODO: 处理资源的删除
}
void Mesh::Draw(Shader &shader) {
  uint32 diffuse_num = 1;
  uint32 specular_num = 1;
  uint32 normal_num = 1;
  for (uint32 i = 0; i < m_textures.size(); i++) {
    m_textures[i].Activate();
    std::string number;
    std::string str = m_textures[i].GetTextureTypeString();
    switch (m_textures[i].GetType()) {
    case TextureType::Diffuse:
      number = std::to_string(diffuse_num++);
      break;
    case TextureType::Specular:
      number = std::to_string(specular_num++);
      break;
    case TextureType::Normal:
      number = std::to_string(normal_num++);
      break;
    case TextureType::Height:
      break;
    case TextureType::Custom:
      break;
    }
    shader.SetInt(("material." + str + number).c_str(), i);
    m_textures[i].Bind();
  }

  glActiveTexture(GL_TEXTURE0);

  m_VAO->Bind();
  glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
  m_VAO->Unbind();
}

void Mesh::SetupMesh() {
  m_VAO = new VertexArrayObject();
  m_VBO = new VertexBufferObject(DataLayoutOfVbo::Position, DataLayoutOfVbo::Normal, DataLayoutOfVbo::TexCoord);
  m_EBO = new ElementBufferObject();
  m_VAO->Bind();
  m_VBO->Bind();
  m_VBO->SetData(&m_vertices[0], m_vertices.size() * sizeof(Vertex));
  m_EBO->Bind();
  m_EBO->BindData(&m_indices[0], m_indices.size() * sizeof(uint32));
  m_VAO->AttributeVBOVertex(*m_VBO);
  m_VAO->Unbind();
}

void Model::Draw(Shader &shader) {
  for (uint32 i = 0; i < m_mesh_count; i++) {
    m_meshes[i].Draw(shader);
  }
}

void Model::LoadModel(const std::string &path) {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    LOG_ERROR("Error when import model:{}", importer.GetErrorString());
    return;
  }
  m_path = path;
  m_directory = path.substr(0, path.find_last_of('/'));
  ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
  for (uint32 i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    m_meshes.emplace_back(ProcessMesh(mesh, scene));
  }
  for (uint32 i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene);
  }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
  using std::vector;
  // data to fill
  vector<Vertex> vertices;
  vector<unsigned int> indices;
  vector<Texture> textures;

  // walk through each of the mesh's vertices
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so
                      // we transfer the data to this placeholder glm::vec3 first.
    // positions
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.Position = vector;
    // normals
    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.Normal = vector;
    }
    // texture coordinates
    if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
    {
      glm::vec2 vec;
      // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
      // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.TexCoord = vec;
      // tangent
      vector.x = mesh->mTangents[i].x;
      vector.y = mesh->mTangents[i].y;
      vector.z = mesh->mTangents[i].z;
      vertex.Tangent = vector;
      // bitangent
      vector.x = mesh->mBitangents[i].x;
      vector.y = mesh->mBitangents[i].y;
      vector.z = mesh->mBitangents[i].z;
      vertex.Bitangent = vector;
    } else
      vertex.TexCoord = glm::vec2(0.0f, 0.0f);

    vertices.push_back(vertex);
  }
  // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    // retrieve all indices of the face and store them in the indices vector
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }
  // process materials
  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
  // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
  // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
  // Same applies to other texture as the following list summarizes:
  // diffuse: texture_diffuseN
  // specular: texture_specularN
  // normal: texture_normalN

  // 1. diffuse maps
  vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
  textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
  // 2. specular maps
  vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
  textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  // 3. normal maps
  std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, TextureType::Normal);
  textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
  // 4. height maps
  std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, TextureType::Height);
  textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

  // return a mesh object created from the extracted mesh data
  return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType type_name) {
  using std::vector;
  vector<Texture> textures;
  for (uint32 i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);
    bool skip = false;
    for (uint32 j = 0; j < m_textures_loaded.size(); j++) {
      if (std::strcmp(m_textures_loaded[j].GetFilePath().c_str(), str.C_Str()) == 0) {
        textures.emplace_back(m_textures_loaded[j]);
        skip = true;
        break;
      }
    }
    if (!skip) {
      const Resource::Image* image = new Resource::Image(str.C_Str());
      Texture texture(image, type_name);
      textures.emplace_back(texture);
      m_textures_loaded.push_back(texture);
    }
  }
  return textures;
}
