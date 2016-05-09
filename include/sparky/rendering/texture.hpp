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

#ifndef __SPARKY_TEXTURE_HPP__
#define __SPARKY_TEXTURE_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\core\ref.hpp>		// Texture is a dynamically allocated object.
#include <sparky\math\vector2.hpp>	// Stores the dimensions of the Texture.
/*
====================
Additional Includes
====================
*/
#include <GLEW\glew.h>				// Binding and generating textures.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class String;

	/*
	====================
	Enumerations
	====================
	*/
	enum class eTextureFilter
	{
		LINEAR = GL_LINEAR,
		NEAREST = GL_NEAREST
	};

	enum class eTextureWrapMode
	{
		CLAMP = GL_CLAMP,
		REPEAT = GL_REPEAT,
		EDGE_CLAMP = GL_CLAMP_TO_EDGE,
		BORDER_BLAMP = GL_CLAMP_TO_BORDER,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT
	};

	struct SPARKY_TEXTURE_DESC
	{
		/*
		====================
		Member Variables
		====================
		*/
		GLenum           target;			///< The target of the Texture (i.e GL_TEXTURE_2D).
		GLint            internalFormat;	///< The internal bit format.
		eTextureFilter   filter;			///< The rendering filter.
		eTextureWrapMode mode;				///< The mode the texture will apply to meshes.

		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor for the Texture description.
		///
		/// The constructor will set the member variables to commonly
		/// use values. The values can easily be changed by the user
		/// for alternate behaviour.
		/// 
		////////////////////////////////////////////////////////////
		explicit SPARKY_TEXTURE_DESC(void)
			: target(GL_TEXTURE_2D), internalFormat(GL_RGBA), filter(eTextureFilter::LINEAR), mode(eTextureWrapMode::CLAMP)
		{
		}
	};

	class Texture final : public Ref
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		GLuint	 m_ID;			///< The ID handle of the Texture.
		Vector2u m_dimensions;	///< The size (in pixels) of the Texture.
		void*	 m_pTexels;		///< The individual pixels of the Texture.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructor for a Texture object with a filename and texture
		///		   Settings.
		///
		/// This constructor loads in a texture from a file directory and sets
		/// the parameters and behaviour of the texture with the settings of the 
		/// description. If the texture fails to load, a warning message will be
		/// printed to the console window.
		///
		/// \param filename		The file directory and name of the texture.
		/// \param desc			A description of the Texture, its formats and rendering technique.
		///
		////////////////////////////////////////////////////////////
		explicit Texture(const String& filename, const SPARKY_TEXTURE_DESC& desc);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the Texture object. De-allocates the ID
		///        of the Texture.
		////////////////////////////////////////////////////////////
		~Texture(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the ID handle of the Texture object.
		///
		/// Similar to other OpenGL functionality, the information and
		/// behaviour of the texture is about to an unsigned int ID. 
		///
		/// \retval GLuint	The Texture ID handle.
		///
		////////////////////////////////////////////////////////////
		GLuint getID(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the dimensions (in pixels) of the Texture.
		///
		/// \retval Vector2u&	The pixel dimensions of the Texture.
		///
		////////////////////////////////////////////////////////////
		const Vector2u& getDimensions(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Gets the individual pixels of the Texture object.
		///
		/// \retval void*	The individual pixels of the Texture.
		///
		////////////////////////////////////////////////////////////
		void* getTexels(void) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Binds the current Texture object for use.
		///
		/// When the Texture object is bound, the next object to render
		/// will utilise the rendering of this specific Texture object.
		/// This is achieved by binding the Texture's ID handle for use.
		///
		/// \param location		The location to bind the texture to. Default is 0.
		///
		////////////////////////////////////////////////////////////
		void bind(const GLuint location = 0) const;

		////////////////////////////////////////////////////////////
		/// \brief Unbinds the current Texture object.
		///
		/// When the Texture object is unbound, the objects in the scene
		/// will no longer make use of this Textures rendering methods.
		///
		////////////////////////////////////////////////////////////
		void unbind(void) const;
	};

}//namespace sparky

#endif//__SPARKY_TEXTURE_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Texture
/// \ingroup rendering
///
/// sparky::Texture is a wrapper class for loading and binding
/// textures for display within the engine. The textures can easily
/// be bound to different locations with convenience methods with
/// a suitable description struct for catering to special circumstances.
/// Below is a code example.
///
/// Usage example:
/// \code
/// // Create a Texture description and "zero it out".
/// sparky::TEXTURE_DESC desc;
/// memset(&desc, 0, sizeof(sparky::TEXTURE_DESC));
///
/// // Set the variables of this texture.
///	desc.target			= GL_TEXTURE_2D;
/// desc.internalFormat	= GL_RGB;
/// desc.filter			= eTextureFilter::NEAREST;
/// desc.mode			= eTextureWrapMode::REPEAT;
///
/// // Load a texture with the description.
/// sparky* pTexture = new Texture("assets/image.tga", desc);
///
/// // Bind the texture for use.
/// pTexture->bind();
/// \endcode
///
////////////////////////////////////////////////////////////