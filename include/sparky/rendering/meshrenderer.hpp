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

#ifndef __SPARKY_MESH_RENDERER_HPP__
#define __SPARKY_MESH_RENDERER_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\rendering\irender.hpp>	// MeshRenderer is a type of renderable component.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class IMeshComponent;
	class Texture;

	class MeshRenderer : public IRenderComponent
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		IMeshComponent* m_pMesh;	///< The Mesh of the renderable component.
		Texture*		m_pTexture;	///< The Texture of the mesh object.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructs a MeshRenderer object with a Mesh and Texture.
		///
		/// The MeshRenderer is a convenience class for rendering a Mesh and
		/// applying a texture to it. It is a renderable component so it can
		/// be attached to the GameObject for rendering.
		///
		/// \param pMesh	The Mesh of the renderer.
		/// \param pTexture	The Texture to be applied to the Mesh.
		///
		////////////////////////////////////////////////////////////
		explicit MeshRenderer(IMeshComponent* pMesh, Texture* pTexture);

		////////////////////////////////////////////////////////////
		/// \brief Default destructor of the MeshRenderer object.
		///
		/// The destructor will release the resources being retained by the 
		/// class. The Mesh and Texture of the object will be dereferenced.
		///
		////////////////////////////////////////////////////////////
		~MeshRenderer(void);

		////////////////////////////////////////////////////////////
		/// \brief Overriden render method for the MeshRenderer.
		///
		/// The render method will bind the texture passed in, in the 
		/// constructor and render the mesh.
		///
		////////////////////////////////////////////////////////////
		void render(void) override;
	};

}//namespace sparky

#endif//__SPARKY_MESH_RENDERER_HPP__

////////////////////////////////////////////////////////////
/// \brief sparky::MeshRenderer
/// \ingroup rendering
///
/// sparky::MeshRenderer is a renderable component of the application.
/// It can be used to conveniently render a Mesh with a bound texture.
/// As sparky::MeshRenderer is a type of IRenderComponent, it follows
/// the Entity Component System design pattern of the engine and can
/// be attached to Entities/GameObjects. Below is a code example.
///
/// Usage example:
/// \code
/// // Create a new GameObject and retain it!
/// sparky::GameObject* pObject = new sparky::GameObject();
/// pObject->addRef();
///
/// // Make a new model.
/// sparky::Model* pModel = new sparky::Model("assets/model.obj");
///
/// // Create a texture description and create a texture!
/// sparky::SPARKY_TEXTURE_DESC desc;
/// memset(&desc, 0, sizeof(sparky::SPARKY_TEXTURE_DESC));
///
/// // Set the variables of this texture.
///	desc.target			= GL_TEXTURE_2D;
/// desc.internalFormat	= GL_RGB;
/// desc.filter			= eTextureFilter::NEAREST;
/// desc.mode			= eTextureWrapMode::REPEAT;
///
/// sparky* pTexture = new Texture("assets/image.tga", desc);
///
/// // Make a mesh renderer and add it to the GameObject!
/// sparky::MeshRenderer* pRenderer = new sparky::MeshRenderer(pModel, pTexture);
///
/// pObject->addComponent(pRenderer);
/// \endcode
///
////////////////////////////////////////////////////////////