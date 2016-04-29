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
#include <sparky\rendering\texture.hpp>	// Class definition.
#include <sparky\utils\string.hpp>		// Loading the texture from a file directory.
#include <sparky\utils\debug.hpp>		// Printing any potential issues.
/*
====================
Additional Includes
====================
*/
#include <SDL_image\SDL_image.h>		// Loading the texture using the SDL2 library.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Texture::Texture(const String& filename, const SPARKY_TEXTURE_DESC& desc)
		: Ref(), m_ID(0), m_dimensions(), m_pTexels(nullptr)
	{
		SDL_Surface* pSurface = IMG_Load(filename.getCString());

		if (!pSurface)
		{
			DebugLog::warning("Failed to load texture:", filename, IMG_GetError());
			return;
		}

		m_dimensions.x = pSurface->w;
		m_dimensions.y = pSurface->h;

		m_pTexels = pSurface->pixels;

		glGenTextures(1, &m_ID);
		glBindTexture(desc.target, m_ID);

		glTexParameteri(desc.target, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(desc.filter));
		glTexParameteri(desc.target, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(desc.filter));
		glTexParameteri(desc.target, GL_TEXTURE_WRAP_S,	    static_cast<GLint>(desc.mode));
		glTexParameteri(desc.target, GL_TEXTURE_WRAP_T,	    static_cast<GLint>(desc.mode));

		glTexImage2D(desc.target, 0, GL_RGBA, m_dimensions.x, m_dimensions.y, 0, desc.internalFormat, GL_UNSIGNED_BYTE, m_pTexels);
		glGenerateMipmap(desc.target);

		glBindTexture(desc.target, NULL);

		SDL_FreeSurface(pSurface);
	}

	////////////////////////////////////////////////////////////
	Texture::~Texture(void)
	{
		if (m_ID)
		{
			glDeleteTextures(1, &m_ID);
			m_ID = NULL;
		}
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	GLuint Texture::getID(void) const
	{
		return m_ID;
	}

	////////////////////////////////////////////////////////////
	const Vector2u& Texture::getDimensions(void) const
	{
		return m_dimensions;
	}

	////////////////////////////////////////////////////////////
	void* Texture::getTexels(void) const
	{
		return m_pTexels;
	}

	////////////////////////////////////////////////////////////
	void Texture::bind(const GLuint location/*= 0*/) const
	{
		glActiveTexture(GL_TEXTURE0 + location);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	////////////////////////////////////////////////////////////
	void Texture::unbind(void) const
	{
		glBindTexture(GL_TEXTURE_2D, NULL);
	}

}//namespace sparky