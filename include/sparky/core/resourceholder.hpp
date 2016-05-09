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

#ifndef __SPARKY_RESOURCE_HOLDER_HPP__
#define __SPARKY_RESOURCE_HOLDER_HPP__

/*
====================
CPP Includes
====================
*/
#include <map>						// Storage type for resources.
/*
====================
Class Includes
====================
*/
#include <sparky\utils\string.hpp>	// Key values for resources.
#include <sparky\core\ref.hpp>		// All objects in the template should inherit from ref.
#include <sparky\rendering\ishader.hpp>
#include <sparky\utils\debug.hpp>	// For printing messages if the resources is already stored.

namespace sparky
{
	template <typename T>
	class ResourceHolder
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::map<String, T*> m_resources;	///< The resources of the holder are stored within a map.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the ResourceHolder object.
		///
		/// The default construction of the ResourceHolder only 
		/// sets the member variables to default values.
		///
		////////////////////////////////////////////////////////////
		explicit ResourceHolder(void);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the ResourceHolder object.
		///
		/// The destruction of the ResourceHolder will release the 
		/// resources being retained by the Holder object.
		///
		////////////////////////////////////////////////////////////
		virtual ~ResourceHolder(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves a resource (by name) from the ResourceHolder.
		///
		/// The map is search by name from the current resources and
		/// retrieves the value which matches the parameter name. If the
		/// resource is not found, a warning message is printed to the console
		/// window and the method will return a null pointer.
		///
		/// \param name		The name of the resource to retrieve.
		///
		/// \retval T		The resource associated with the name. If the 
		///					resource is not found, null pointer is returned.
		///
		////////////////////////////////////////////////////////////
		T* get(const String& name) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Adds a resource to the map with an associated String key.
		///
		/// When a resource is added to the ResourceHolder object, it checks
		/// to make sure that no objects have the same key. If the key is not
		/// found the resource parameter is retained and added as a pair to the
		/// resource map.
		///
		/// \param name			The desginated key of the resource.
		/// \param pResource	The resource to add to the map.
		///
		////////////////////////////////////////////////////////////
		void add(const String& name, T* pResource);

		////////////////////////////////////////////////////////////
		/// \brief Removes a resource from the ResourceHolder object.
		///
		/// When an object is removed, the map is searched to make sure
		/// that this object is in the Holder. If it is the object is
		/// erased from storage and released. When all other objects
		/// are no longer referencing this resource, the object will be
		/// de-allocated.
		///
		/// \param name		The key of the resource to remove.
		///
		////////////////////////////////////////////////////////////
		void remove(const String& name);
	};

	#include <sparky\core\resourceholder.inl>

}//namespace sparky

#endif//__SPARKY_RESOURCE_HOLDER_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::ResourceHolder
/// \ingroup core 
///
/// sparky::ResourceHolder is a parent class resource storage
/// object. It is used to store assets that will be commonly
/// used throughout the application, such as Shaders and Textures.
///
/// The Resource Holder prevents duplication of objects, so 
/// that the engine is as efficient as possible during runtime.
/// The ResourceHolder can store all assets used by the application
/// before starting by adding them when the application is first
/// started.
///
/// Objects within the ResourceHolder must inherit from sparky::Ref
/// to comply with Sparky's memory management scheme. Below is pseudo-code example.
///
/// Usage example:
/// \code
/// // Create a sample user type. (Must inherit from Ref).
/// struct Type : public Ref
/// {
///		int x;
/// }
///
/// // Create a resource holder to hold the different types.
/// sparky::ResourceHolder<Type> holder;
///
/// // Add a type to the holder
/// holder.add("Type", new Type());
///
/// // Retrieve a object from the holder and print it to the console.
/// std::cout << holder.get("Type").x << std::endl;
/// \endcode
///
////////////////////////////////////////////////////////////