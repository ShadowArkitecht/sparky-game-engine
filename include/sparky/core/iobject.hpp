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

#ifndef __SPARKY_IOBJECT_HPP__
#define __SPARKY_IOBJECT_HPP__

/*
====================
Sparky Includes
====================
*/
#include <sparky\core\ref.hpp>			// IObject is a dynamically allocated object.
#include <sparky\math\transform.hpp>	// IObject needs a translation, rotation and scale of the object.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class IShaderComponent;

	class IObject : public Ref
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		Transform m_transform;	///< The position, rotation and scale of the object in 3D space.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor of the IObject object.
		///
		/// The default constructor will call the default parameters of
		/// the Transform member variable and add the object to the release
		/// pool.
		///
		////////////////////////////////////////////////////////////
		explicit IObject(void);

		////////////////////////////////////////////////////////////
		/// \brief Default destructor of the IObject object.
		////////////////////////////////////////////////////////////
		virtual ~IObject(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the transform of the IObject object in 3D space.
		///
		/// The Transform controls this object's position, rotation and scale
		/// in 3D space. The Method returns a reference so that it can be edited
		/// outside this scope.
		///
		/// \retval Transform&	The current Transform of the IObject.
		///
		////////////////////////////////////////////////////////////
		Transform& getTransform(void);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Abstract method for updating the current IObject.
		///
		/// The update method will control any logic based elements that this
		/// class will rely upon. It must be overwritten by any child class that 
		/// inherits from this class.
		///
		////////////////////////////////////////////////////////////
		virtual void update(void) = 0;

		////////////////////////////////////////////////////////////
		/// \brief Abstract method for rendering the current IObject.
		///
		/// The rendering method will only render the current IObject at the
		/// specified Transform. The rendering method should not contain any logic
		/// based functionality.
		///
		/// \param pShader	The shader to render the IObject with.
		///
		////////////////////////////////////////////////////////////
		virtual void render(IShaderComponent* pShader) = 0;
	};

}//namespace sparky

////////////////////////////////////////////////////////////
/// \class sparky::IObject
/// \ingroup core
///
/// sparky::IObject is the pure virtual class that all objects will
/// inherit from within the application. An object refers to an element
/// which will contain both logic and rendering and is the base class for
/// the engines entity component system. For a code example refer to
/// sparky::GameObject and sparky::World.
///
////////////////////////////////////////////////////////////

#endif//__SPARKY_IOBJECT_HPP__