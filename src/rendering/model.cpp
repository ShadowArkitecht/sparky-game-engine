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
		const aiScene* pScene = importer.ReadFile(filename.getCString(), aiProcess_Triangulate);

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

			if (pMesh->HasNormals())
			{
				vertex.normal.x = pMesh->mNormals[i].x;
				vertex.normal.y = pMesh->mNormals[i].y;
				vertex.normal.z = pMesh->mNormals[i].z;
			}

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

		if (!pMesh->HasNormals())
		{
			pSparkyMesh->generate(true);
		}

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