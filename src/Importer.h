#pragma once
#include "..\xhl.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include "ImportData.h"


// string objPath = "D:\\XHL\\JC\\OpenGL\\Mesh\\";
struct Meshes {
    string name;
    unsigned int vID;
    unsigned int vOffset;
    unsigned int matID;
};
struct Material {
    string diff;
    string spec;
    string norm;
};

vector<string> textures;// 存放fbx里的所有贴图, (准备状态) .
vector<vec3> pos;
vector<Material> mats; // 存放FBX 里的所有材质 , (材质所对应的贴图 )
vector<Meshes> Meshes_OK;
vector<Vertex> vertices;
vector<unsigned int> indices;
// -- 属性的长度 --
int prop[] = { 3 ,3,2 };
int propSize = sizeof(prop) / sizeof(prop[0]);


void Import(const std::string& pFile)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if (!scene)
    {
        print(importer.GetErrorString());
    }
    //print("导入成功!");

    aiNode* rootNode = scene->mRootNode;
    for (int i = 0; i < rootNode->mNumChildren; i++)
    {
        aiNode* node = rootNode->mChildren[i];

        pos.push_back(vec3(node->mTransformation.a4,
            node->mTransformation.b4,
            node->mTransformation.c4));

    }

    // 获取 aiMeshes
    int aiMeshes = scene->mNumMeshes;




    int SumVertices = 0; // 解决多个物体 的indices 都是从0开始
    int SumIndices = 0;
    for (int i = 0; i < aiMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[i];
        //print(mesh->mName.C_Str());
        print(mesh->mName.C_Str() << ": \n" << "顶点数量 = " << mesh->mNumVertices);
        // 顶点数据
        for (int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            vertex.Pos = aiVec3(mesh->mVertices[i]);  // 填充 Pos
            vertex.Normal = aiVec3(mesh->mNormals[i]);  // 填充 Normal
            vertex.UV = aiVec2(mesh->mTextureCoords[0][i]); // 填充UV
            vertices.push_back(vertex);
        }


        //面ID
        int faces = mesh->mNumFaces;

        print("indices 数量=" << faces * 3);
        print("indices 偏移量=" << SumIndices);
        print("材质ID = " << mesh->mMaterialIndex);

        Meshes temp_m;
        temp_m.vID = faces * 3;
        temp_m.vOffset = SumIndices;
        temp_m.matID = mesh->mMaterialIndex;
        temp_m.name = mesh->mName.C_Str();
        Meshes_OK.push_back(temp_m);

        for (int i = 0; i < faces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j] + SumVertices);
            }
        }
        print("==========================");
        SumVertices += mesh->mNumVertices;
        SumIndices += faces * 3;

    }


    print("----------");
    cout << "vertices 数量:" << vertices.size() << endl;
    cout << "indices 数量:" << indices.size() << endl;


    


    // 获取贴图
    aiString texPath;
    int numMat = scene->mNumMaterials;
    aiTextureType texType[] = { aiTextureType_DIFFUSE ,aiTextureType_SPECULAR,aiTextureType_HEIGHT };
    string texTypeStr[] = { "颜色","高光","法线" };
    string defultTex[] = { "white.jpg","black.jpg","normal.jpg" };
    string* p;
    for (int i = 0; i < numMat; i++)
    {
        aiMaterial* mat = scene->mMaterials[i];
        printf("第%i个材质:\n", i);
        Material tempMat; // 临时的 mat 结构体
        p = &tempMat.diff;

        for (int j = 0; j < len(texType); j++)
        {

            texPath = "";
            mat->GetTexture(texType[j], 0, &texPath);
            string tex = texPath.C_Str();
            if (tex.size() > 0) {
                (*p++) =  tex;
                print(texTypeStr[j] << "贴图:" <<  tex);
                textures.push_back( tex);
            }
            else {
                (*p++) = defultTex[j];
                print(texTypeStr[j] << "贴图:" << defultTex[j]);
            }
        }
        mats.push_back(tempMat);
        print("");


    }

    // vector 去重复
    vector<string>::iterator it;
    sort(textures.begin(), textures.end());
    it = unique(textures.begin(), textures.end());
    if (it != textures.end())	textures.erase(it, textures.end());

    for (int i = 0; i < len(defultTex); i++)
    {
        textures.insert(textures.begin(), defultTex[len(defultTex) - i - 1]);
    }

    print("待导入区贴图数: " << textures.size());
    for (int i = 0; i < textures.size(); i++)
    {
        print(textures[i]);
    }

    // return indices;
}
