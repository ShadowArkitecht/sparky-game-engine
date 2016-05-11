///////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Sparky Engine
// 2016 - Benjamin Carter (benjamin.mark.carter@hotmail.com)
// 
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgement
//    in the product documentation would be appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
====================
Class Includes
====================
*/
#include <sparky\rendering\model.hpp>	// Class definition.
#include <sparky\utils\debug.hpp>		// Prints an error message to the screen if the model path is in-correct.

/*
====================
Additional Includes
====================
*/
#include <assimp\Importer.hpp>		// Assimp: initially loads in the model and provides error checking.
#include <assimp\scene.h>			// Assimp: A scene pointer which contains all information about the imported model.
#include <assimp\postprocess.h>

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Model::Model(const String& filename)
		: IMeshComponent(), m_meshes()
	{
		Assimp::Importer importer;
		const aiScene* pScene = importer.ReadFile(filename.getCString(), aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!pScene || pScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
		{
			DebugLog::error(filename.getCString(), "has failed to import:", importer.GetErrorString());
			return;
		}

		this->loadNode(pScene->mRootNode, pScene);

		m_generated = true;
	}

	////////////////////////////////////////////////////////////
	Model::~Model(void)
	{
		for (auto& mesh : m_meshes)
		{
			Ref::release(mesh);
		}

		m_meshes.clear();
	}

	/*
	====================
	Private Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void Model::loadNode(aiNode* pNode, const aiScene* pScene)
	{
		for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
		{
			m_meshes.push_back(this->loadMesh(pScene->mMeshes[pNode->mMeshes[i]], pScene));
		}

		for (unsigned int i = 0; i < pNode->mNumChildren; i++)
		{
			this->loadNode(pNode->mChildren[i], pScene);
		}
	}

	////////////////////////////////////////////////////////////
	MeshData* Model::loadMesh(aiMesh* pMesh, const aiScene* pScene)
	{
		MeshData* pSparkyMesh = new MeshData();

		for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
		{
			Vertex_t vertex;

			vertex.position.x = pMesh->mVertices[i].x;
			vertex.position.y = pMesh->mVertices[i].y;
			vertex.position.z = pMesh->mVertices[i].z;

			//if (pMesh->HasNormals())
			//{
			//	vertex.normal.x = pMesh->mNormals[i].x;
			//	vertex.normal.y = pMesh->mNormals[i].y;
			//	vertex.normal.z = pMesh->mNormals[i].z;
			//}

			if (pMesh->mTextureCoords[0])
			{
				vertex.uv.x = pMesh->mTextureCoords[0][i].x;
				vertex.uv.y = pMesh->mTextureCoords[0][i].y;
			}
			else
			{
				vertex.uv = Vector2f::zero();
			}

			pSparkyMesh->addVertex(vertex);
		}

		for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
		{
			aiFace face = pMesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				pSparkyMesh->addIndex(face.mIndices[j]);
			}
		}

		pSparkyMesh->addRef();

		//if (!pMesh->HasNormals())
		//{
		//	pSparkyMesh->generate(true);
		//}

		pSparkyMesh->generate(true);
		return pSparkyMesh;
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void Model::render(void)
	{
		for (const auto& mesh : m_meshes)
		{
			mesh->render();
		}
	}

}//namespace sparky