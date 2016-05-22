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

#ifndef __SPARKY_IOBECT_HPP__
#define __SPARKY_IOBECT_HPP__

/*
===================
Class Includes
===================
*/
#include<sparky\core\ref.hpp>       // IObject is a dynamically allocated object.
#include<sparky\math\transform.hpp> // Transform is the position, rotation and scale of the object in the scene.

namespace sparky
{
	/*
	===================
	Sparky Forward Declarations
	===================
	*/
	class IShaderComponent;

    class IObject : public Ref
    {
    private:
        Transform m_transform;  ///< The transform (position, rotation and scale) of the IObject.

    public:
        /*
        ===================
        Ctor and Dtor
        ===================
        */
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor for the IObject object.
        ///
        /// The IObject default constructor will set the Transform to
        /// default values.
        ///
        ////////////////////////////////////////////////////////////
        explicit IObject(void);

        ////////////////////////////////////////////////////////////
        /// \brief Default Destructor for the IObject instance.
        ////////////////////////////////////////////////////////////
        virtual ~IObject(void) = default;

        /*
        ===================
        Getters and Setters
        ===================
        */
        ////////////////////////////////////////////////////////////
        /// \brief Retrieves the Transform of the current IObject.
        ///
        /// The Transform refers to the position, rotation and scale of the
        /// IObject.
        ///
        /// \retval Transform&  The Transform of the IObect.
        ///
        ////////////////////////////////////////////////////////////
        Transform& getTransform(void);

        /*
        ===================
        Methods
        ===================
        */
        ////////////////////////////////////////////////////////////
        /// \brief Abstract update method for the IObject class.
        ///
        /// The update method will need to be overwritten by child classes
        /// to provide modular behaviour.
        ///
        ////////////////////////////////////////////////////////////
        virtual void update(void) = 0;

        ////////////////////////////////////////////////////////////
        /// \brief Abstract render method for the IObject class.
        ///
        /// The render method will need to overwritten by child classes.
        /// This method should be responsible for the rendering of the IObject
        /// class.
        ///
		/// \param pShader	The shader to render the IObject with.
		///
        ////////////////////////////////////////////////////////////
        virtual void render(IShaderComponent* pShader) = 0;
    };

}//namespace sparky

#endif//__SPARKY_IOBECT_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::IObject
/// \ingroup core
///
/// sparky::IObject is the base class for any object that needs
/// access to both an update and render method (such as GameObject and World).
/// This class is commonly used within the Sparky Engine with
/// components. For a code example refer to sparky::GameObject or sparky::World.
///
////////////////////////////////////////////////////////////
