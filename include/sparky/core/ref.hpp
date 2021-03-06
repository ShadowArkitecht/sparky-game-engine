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

#ifndef __SPARKY_REF_HPP__
#define __SPARKY_REF_HPP__

namespace sparky
{
	class Ref
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		unsigned int m_references;	///< The number of references that this object has currently obtained. Starts at 1 by default.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		///	\brief Constructs a Ref object instance. 
		///
		///	This default constructor initialises the Ref and sets
		/// the reference count to one. Upon construction the object
		/// is added to the PoolManager. At the end of the current frame
		/// the pool is emptied and cleared and all Ref objects within the
		/// list have their references decremented. If the count is 
		/// equal to 0, the Ref object is deleted.
		/// 
		////////////////////////////////////////////////////////////
		explicit Ref(void);

		////////////////////////////////////////////////////////////
		///	\brief Destructs a Ref object instance. 
		///
		///	The Ref only provides a default destructor as the objects
		/// inheriting from this object will define their destruction,
		/// Ref itself contains no dynamically allocated memory.
		/// 
		////////////////////////////////////////////////////////////
		virtual ~Ref(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Gets the current reference count of the Ref.
		///
		/// The reference count refers to the amount of times that this
		/// current Ref has been referenced by other classes, this is
		/// to ensure that objects can be shared between many instances
		/// without any one instance being responsible for the Ref
		/// desctruction. This means that less memory has to be utilised 
		/// within the application.
		///
		/// \retval references	The amount of references to the Ref.
		///
		////////////////////////////////////////////////////////////
		unsigned int getRefCount(void) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Adds a reference count to the Ref.
		///
		/// Whenever an Ref is referenced within another class
		/// and needs to live throughout that instances lifetime, the
		/// Ref in questions reference should be incremented in 
		/// order to prevent automatic de-allocation.
		///
		////////////////////////////////////////////////////////////
		void addRef(void);

		////////////////////////////////////////////////////////////
		/// \brief Removes a reference count from the Ref.
		///
		/// When a call no longer needs to retain a reference to the
		/// Ref, the reference counter should be decremented.
		///
		////////////////////////////////////////////////////////////
		void removeRef(void);

		////////////////////////////////////////////////////////////
		/// \brief Error-checking and referencing decrementing of Ref objects.
		///
		/// A convenience method for checking whether the current reference 
		/// is valid. if the Ref is value, the Ref reference count is decremented
		/// and upon reaching 0 references, the Ref is automatically
		/// de-allocated and set to null.
		///
		/// \param ref	The Ref to decrement and de-allocate.
		///
		////////////////////////////////////////////////////////////
		template <typename T> 
		static void release(T& ref);
	};

	////////////////////////////////////////////////////////////
	template <typename T>
	void Ref::release(T& ref)
	{
		if (ref)
		{
			ref->removeRef();

			if (ref->getRefCount() == 0)
			{
				delete ref;
				ref = nullptr;
			}
		}
	}

}//namespace sparky

#endif//__SPARKY_REF_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Ref
/// \ingroup core
///
/// sparky::Ref is a referenced counted class which all
/// dynamically allocated resources within the engine will
/// inherit from. This is Sparky's inbuilt methodology for 
/// providing basic Garbage Collection. 
///
/// sparky::Ref is commonly not used by itself, it is typically
/// inherited from and provides its uses for subsequent child
/// classes. However the user can use the base Ref class
/// if they so choose. Below is an example on how to use the
/// functionality of the Ref class.
///
/// Usage example:
/// \code
/// // Create an Ref and retain it.
/// sparky::Ref* pObject = new sparky::Ref();
/// pObject->addRef();
///
/// // Use the object.
/// // PoolManager is flushed
/// PoolManager::getInstance().flush();
/// // Release upon end-of-use. The counter will be decremented and 
/// // the object will be subsequently destroyed.
/// Ref::release(pObject);
/// \endcode
///
////////////////////////////////////////////////////////////