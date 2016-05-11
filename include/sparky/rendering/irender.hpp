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

#ifndef __SPARKY_IRENDER_COMPONENT_HPP__
#define __SPARKY_IRENDER_COMPONENT_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\core\ref.hpp>	// IRenderComponent is a dynamically allocated object.

namespace sparky
{
	class IRenderComponent : public Ref
	{
	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor for IRenderComponent object. Calls the
		///		   the Ref object parent constructor.
		////////////////////////////////////////////////////////////
		explicit IRenderComponent(void);

		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the IRenderComponent object.
		////////////////////////////////////////////////////////////
		virtual ~IRenderComponent(void) = default;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Abstract method for rendering the component.
		///
		/// Components can be added to the GameObject class that will
		/// need different type of behaviour, depending on the needed
		/// rendering.
		///
		////////////////////////////////////////////////////////////
		virtual void render(void) = 0;
	};
}

#endif//__SPARKY_IRENDER_COMPONENT_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::IRenderComponent
/// \ingroup rendering
///
/// sparky::IRenderComponent is the base class for all renderable
/// components that can be added to GameObject instances. It allows
/// for modular rendering behaviour as each child will override the
/// pure virtual render method. For a code example please refer to
/// sparky::MeshRenderer.
///
////////////////////////////////////////////////////////////