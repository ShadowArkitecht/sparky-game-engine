#ifndef __SPARKY_RESOURCE_HOLDER_HPP__
#define __SPARKY_RESOURCE_HOLDER_HPP__

/*
====================
CPP Includes
====================
*/
#include <map>						// Storage type for resources.
#include <utility>					// Using for std::forward parameters.
/*
====================
Class Includes
====================
*/
#include <sparky\utils\string.hpp>	// Key values for resources.
#include <sparky\core\ref.hpp>		// All objects in the template should inherit from ref.
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
		std::map<String, T*> m_resources;	// The resources of the holder are stored within a map.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Resource Holder object.
		///
		/// The default construction of the Resource Holder only 
		/// sets the member variables to default values.
		///
		////////////////////////////////////////////////////////////
		explicit ResourceHolder(void);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the Resource Holder object.
		///
		/// The destruction of the Resource Holder will release the 
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
		/// \brief Retrieves a resource (by name) from the Resource Holder.
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
		/// When a resource is added to the Resource Holder object, it checks
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
		/// \brief Constructs a resource with variadic parameters with an 
		///		   associated key.
		///
		/// When a resource is going to be added to the Resource Holder object,
		/// it checks to make sure that no objects have the same key. If the
		/// key is not found, a new resource is constructed with the variadic
		/// parameters, retained an then added to the resource map.
		///
		/// \param name		The designated key of the resource.
		/// \param args     The arguments to construct the resource with.
		///
		////////////////////////////////////////////////////////////
		template <typename... Args>
		void add(const String& name, Args&&... args);

		////////////////////////////////////////////////////////////
		/// \brief Removes a resource from the Resource Holder object.
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
/// that the engine is as effecient as possible during runtime.
/// The Resource Holder can store all assets used by the application
/// before starting by adding them when the application is first
/// started.
///
/// Objects within the Resource Holder must inherit from sparky::Ref
/// to comply with Sparky's memory management scheme.
/// Below is pseudo-code example:
///
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
///
////////////////////////////////////////////////////////////