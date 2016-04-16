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

#ifndef __SPARKY_SINGLETON_HPP__
#define __SPARKY_SINGLETON_HPP__

namespace sparky
{
	template <typename T>
	class Singleton
	{
	protected:
		////////////////////////////////////////////////////////////
		/// \brief Default construction of a Singleton instance.
		///
		/// A singleton is a common design pattern which utilises
		/// the construction of a single instance throughout the 
		/// programs lifetime. They can be used to provide convenient
		/// access to objects and methods, regardless of scope. The 
		/// constructor is protected so that it cannot be accessed
		/// outside the parent or child's scope.
		///
		////////////////////////////////////////////////////////////
		explicit Singleton(void) = default;

		////////////////////////////////////////////////////////////
		/// \brief Deletes the copy constructor of a Singleton.
		///
		/// This will prevent the user from constructing any additional
		/// singleton's from the information of another, which will
		/// provide undefined behaviour in the application.
		///
		////////////////////////////////////////////////////////////
		explicit Singleton(const Singleton<T>& other) = delete;

	public:
		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the Singleton instance.
		///
		/// The Parent class retains no information or dynamically 
		/// allocated memory so does not need to destruct any objects.
		/// The destruction of objects will be overriden in it's
		/// subsequent child classes.
		///
		////////////////////////////////////////////////////////////
		virtual ~Singleton(void) = default;

		////////////////////////////////////////////////////////////
		/// \brief Gets the instance of the Singleton.
		///
		/// This provides access to the functionality of the Singleton
		/// object. As the Singleton can only be constructed within
		/// its own scope, you cannot access its methods without 
		/// utilising the static instance of the class. 
		///
		////////////////////////////////////////////////////////////
		static T& getInstance(void);
	};

	////////////////////////////////////////////////////////////
	template <typename T>
	T& Singleton<T>::getInstance(void)
	{
		static T instance;
		return instance;
	}
}

#endif//__SPARKY_SINGLETON_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Singleton<T>
/// \ingroup utils
///
/// sparky::Singleton<T> is a templated base class which 
/// provides the basic implementation of a Singleton design
/// pattern. 
///
/// All other Singleton's within the engine which provide additional 
/// behaviour will inherit from this object. The user can also 
/// create additional Singletons by inheriting from this base class.
///
/// Although you would never use this base class as-is. Below
/// is a basic example of it's uses.
///
/// \code
/// // Store an int Singleton in a local variable.
/// Singleton<int> s = Singleton<int>::getInstance();
///
////////////////////////////////////////////////////////////