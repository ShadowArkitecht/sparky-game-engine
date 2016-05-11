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

#ifndef __SPARKY_GAME_OBJECT_HPP__
#define __SPARKY_GAME_OBJECT_HPP__

/*
====================
CPP Includes
====================
*/
#include <vector>						// Container for renderable components
/*
====================
Class Includes
====================
*/
#include <sparky\core\ref.hpp>			// GameObject is a dynamically allocated object.
#include <sparky\math\transform.hpp>	// GameObject has a position, rotation and scale in 3D space.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class IRenderComponent;
	class IShaderComponent;

	class GameObject : public Ref
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		Transform m_transform;							///< The translation, rotation and scale of this GameObject.
		std::vector<IRenderComponent*> m_renderables;	///< All of the renderables attached to this GameObject.

	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor for the GameObject.
		///
		/// When a GameObject is constructed with this constructor, its
		/// transform within 3D space is set to the Transform's default
		/// constructor.
		///
		////////////////////////////////////////////////////////////
		explicit GameObject(void);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a GameObject with an explicit position.
		///
		/// The GameObject is constructed with a defined position within
		/// the world. The rotation and scale of the object remain the 
		/// Transform classes default values.
		///
		/// \param position		The position of the GameObject.
		///
		////////////////////////////////////////////////////////////
		explicit GameObject(const Vector3f& position);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a GameObject with an explicit position and rotation.
		///
		/// The GameObject is constructed with a defined position and rotation
		/// within the world. The scale value remains the Transform's default
		/// value.
		///
		/// \param position		The position of the GameObject.
		/// \param rotation		The rotation of the GameObject.
		///
		////////////////////////////////////////////////////////////
		explicit GameObject(const Vector3f& position, const Quaternionf& rotation);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a GameObject with an explicit position, rotation and scale.
		///
		/// The GameObject is constructed with a defined position, rotation
		/// and scale within the World.
		///
		/// \param position		The position of the GameObject.
		/// \param rotation		The rotation of the GameObject.
		/// \param scale		The scale of the GameObject.
		///
		////////////////////////////////////////////////////////////
		explicit GameObject(const Vector3f& position, const Quaternionf& rotation, const Vector3f& scale);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the GameObject class, releases all of the
		///        IRenderComponent's being retained.
		////////////////////////////////////////////////////////////
		~GameObject(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the current Transform of this GameObject.
		///
		/// As the Transform is returned as a reference object, the GameObject's
		/// Transform can be edited outside the scope of this class.
		///
		/// \retval Transform&	The Transform of the GameObject.
		///
		////////////////////////////////////////////////////////////
		Transform& getTransform(void);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Attached a renderable component to the GameObject.
		///
		/// \param pRenderable	The renderable component to add.
		///
		////////////////////////////////////////////////////////////
		void addComponent(IRenderComponent* pRenderable);

		////////////////////////////////////////////////////////////
		/// \brief Renders the GameObject.
		///
		/// When the GameObject is rendered, the shader is updated with
		/// this objects Transform, and all of the IRenderComponent's attached
		/// to the GameObject are rendered.
		///
		/// \param pShader	The shader to be updated.
		///
		////////////////////////////////////////////////////////////
		void render(IShaderComponent* pShader);
	};
}

#endif//__SPARKY_GAME_OBJECT_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::GameObject
/// \ingroup core
///
/// sparky::GameObject is the "Entity" class within the Entity
/// Component System design paradigm that the engine utilises. 
/// Components can be added to the GameObject quickly and the
/// object will implicitly know the behaviour of each component.
///
/// Currently the GameObject is only used for rendering models or
/// meshes within the application. Below is a code example.
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