#ifndef __SPARKY_MODEL_HPP__
#define __SPARKY_MODEL_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\rendering\meshdata.hpp>	// Model inherits from IMeshComponent and contains an array of Meshes
#include <sparky\utils\string.hpp>			// For getting the file location of the Model

/*
====================
Forward Declarations
====================
*/
struct aiNode;
struct aiMesh;
struct aiScene;

namespace sparky
{
	class Model final : public IMeshComponent
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::vector<MeshData*> m_meshes;	// All of the meshes that the model is constructed of.

	private:
		/*
		====================
		Private Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Recursively loads the Nodes within the Assimp scene.
		///
		/// Load node recursively loads each individual node and it's 
		/// children for processing. The process involves calling itself and
		/// load Mesh to load all of the meshes in the specified file.
		///
		/// \param pNode	The Assimp node to process.
		/// \param pScene   The scene that all these nodes are contained within.
		///
		////////////////////////////////////////////////////////////
		void loadNode(aiNode* pNode, const aiScene* pScene);

		////////////////////////////////////////////////////////////
		/// \brief Converts an Assimp mesh to a Sparky Mesh.
		///
		/// This method will convert a mesh from the Assimp format
		/// to a format that sparky can understand and render correctly. 
		///
		/// \param pMesh	The Assimp mesh to be converted.
		/// \param pScene	The scene the Assimp meshes are contained within.
		///
		/// \retval MeshData*	The converted Sparky Mesh.
		///
		////////////////////////////////////////////////////////////
		MeshData* loadMesh(aiMesh* pMesh, const aiScene* pScene);

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Construction of a Model object with a object file name.
		///
		/// The constructor will create an Assimp importer and recursively
		/// load all the meshes and objects contained within the file being
		/// parsed in. If the loading fails an error message is presented
		/// to the console window and the application will exit.
		///
		/// \param filename	The file location of the model to load in.
		///
		////////////////////////////////////////////////////////////
		explicit Model(const String& filename);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the Model object.
		///
		/// The constructor will release all of the meshes stored by
		/// the Model object and clears the container.
		///
		////////////////////////////////////////////////////////////
		~Model(void);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Renders all of the current meshes within the Model object.
		////////////////////////////////////////////////////////////
		void render(void) override;
	};

}//namespace sparky

#endif//__SPARKY_MODEL_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Model
/// ingroup rendering
///
/// sparky::Model is a wrapper class for loading external Model
/// formats and process them for use within the engine. The class
/// utilises the Assimp library to load a large variety of different
/// Model formats such as .obj and .fbx. 
///
/// sparky::Model can recursively load and process multiple meshes 
/// within an external file and render them correctly. The implementation
/// is based on http://www.learnopengl.com/#!Model-Loading/Model. Below is 
/// a code example.
///
/// \code
/// // Create a model and load it in.
/// sparky::Model* pModel = new sparky::Model("assets/model.obj");
///
/// // Render the mesh in the render loop.
/// pModel->render();
///
////////////////////////////////////////////////////////////