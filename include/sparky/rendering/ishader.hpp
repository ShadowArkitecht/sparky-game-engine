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

#ifndef __SPARKY_ISHADER_COMPONENT_HPP__
#define __SPARKY_ISHADER_COMPONENT_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\core\ref.hpp>			// IShaderComponent is a dynamically allocated object.
#include <sparky\rendering\program.hpp>	// Program for attaching and linking shaders.
#include <sparky\rendering\uniform.hpp> // Uniform for setting uniform variables in shaders.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class Transform;
	class String;

	class IShaderComponent : public Ref
	{
	protected:
		/*
		====================
		Member Variables	
		====================
		*/
		Program m_program;	// The Program contains the shader functionality.
		Uniform m_uniform;  // Binds uniform variables within the shader.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the IShaderComponent object.
		////////////////////////////////////////////////////////////
		explicit IShaderComponent(void);

		////////////////////////////////////////////////////////////
		/// \brief Convenience constructor for child objects that only
		//         contain a vertex and fragment shader.
		////////////////////////////////////////////////////////////
		explicit IShaderComponent(const String& vertexShader, const String& fragmentShader);

		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the IShaderComponent object.
		////////////////////////////////////////////////////////////
		virtual ~IShaderComponent(void) = default;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// brief Binds the Program attached to the IShaderComponent object.
		////////////////////////////////////////////////////////////
		void bind(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Unbinds the Program attached to the IShaderComponent object.
		////////////////////////////////////////////////////////////
		void unbind(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Abstract method for updating the IShaderComponent object.
		///
		/// This method is overwritten by each subsequent shader of the 
		/// sparky engine. Update updates the uniforms contained within the
		/// Program's shaders.
		///
		/// \param transform	The transform of the object being rendered.
		///
		////////////////////////////////////////////////////////////
		virtual void update(const Transform& transform) const = 0;
	};

}//namespace sparky

#endif//__SPARKY_ISHADER_COMPONENT_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::IShaderComponent
/// \ingroup rendering
///
/// sparky::IShaderComponent is the abstract base class object
/// for all shaders used within the Sparky Engine. It provides
/// basic functionality for binding and unbinding shaders and
/// an abstract method for updating the uniforms of a shader.
/// For a code example refer to any child object of this shader.
///
////////////////////////////////////////////////////////////