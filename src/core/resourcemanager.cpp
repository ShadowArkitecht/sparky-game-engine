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
#include <sparky\core\resourcemanager.hpp>	// Class definition.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	ResourceManager::ResourceManager(void)
		: Singleton<ResourceManager>(), m_shaders()
	{
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void ResourceManager::addShader(const String& name, IShaderComponent* pShader)
	{
		m_shaders.add(name, pShader);
	}

	////////////////////////////////////////////////////////////
	void ResourceManager::removeShader(const String& name)
	{
		m_shaders.remove(name);
	}

}//namespace sparky