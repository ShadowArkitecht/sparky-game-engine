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

#ifndef __SPARKY_RESOURCE_MANAGER_HPP__
#define __SPARKY_RESOURCE_MANAGER_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\utils\singleton.hpp>		// Resource Manager is a singleton object.
#include <sparky\core\resourceholder.hpp>	// Retains a number of different resources.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class IShaderComponent;

	class ResourceManager final : public Singleton<ResourceManager>
	{
		friend class Singleton<ResourceManager>;

	private:
		/*
		====================
		Member Variables
		====================
		*/
		ResourceHolder<IShaderComponent> m_shaders;		// The storage of all shaders.

	private:
		/*
		====================
		Private Ctor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor for the ResourceManager singleton.
		////////////////////////////////////////////////////////////
		explicit ResourceManager(void);

	public:
		/*
		====================
		Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the ResourceManager singleton.
		////////////////////////////////////////////////////////////
		~ResourceManager(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves a shader from the resources lists.
		///
		/// Searches the ResourceHolder of shaders for the shader with
		/// the specified name. If the shader is not found, an error 
		/// message is produced and nullptr is returned.
		///
		/// \param name		The name of the shader to retrieve.
		///
		////////////////////////////////////////////////////////////
		template <typename T = IShaderComponent>
		T* getShader(const String& name) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Adds a shader to the resource lists.
		///
		/// Adds a shader to the resource lists. If a shader has already
		/// been added that has an identical name, then the shader is not
		/// added to the list and a warning message is produced.
		///
		/// \param name		The keyword name associated with this shader.
		/// \param pShader	The shader to add to the resource list.
		///
		////////////////////////////////////////////////////////////
		void addShader(const String& name, IShaderComponent* pShader);

		////////////////////////////////////////////////////////////
		/// \brief Removes a shader from the resource lists.
		///
		/// Removes a shader by name from the resource lists. If the shader
		/// is not found, a warning message is printed and the lists are 
		/// left untouched.
		///
		////////////////////////////////////////////////////////////
		void removeShader(const String& name);
	};

	////////////////////////////////////////////////////////////
	template <typename T>
	T* ResourceManager::getShader(const String& name) const
	{
		return dynamic_cast<T*>(m_shaders.get(name));
	}

}//namespace sparky

#endif//__SPARKY_RESOURCE_MANAGER_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::ResourceManager
/// \ingroup core
///
/// sparky::ResourceManager is a singleton class which retains
/// commonly used assets and shaders used throughout the engine
/// for quick retrieval and use. When the Resource Manager is 
/// utilised, external sources only have to be loaded into the 
/// engine once, which saves additional time and memory.
///
/// Which becomes especially helpful when utilising different 
/// shaders in different files, the shaders can be used without
/// the use of additional functionality or parameters. Below is
/// a code example.
///
/// \code
/// // Add a Basic shader to the Resource Manager.
/// sparky::ResourceManager::getInstance().addShader("basic", new sparky::FinalShader());
///
/// // Get a local reference of the shader for use.
/// sparky::FinalShader* pShader = sparky::ResourceManager::getInstance().getShader<FinalShader>("basic");
///
/// // Bind the shader for use.
/// pShader->bind();
///
////////////////////////////////////////////////////////////