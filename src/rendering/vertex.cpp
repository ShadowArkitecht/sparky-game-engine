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

#include <sparky\rendering\vertex.hpp> // Class definition.

namespace sparky
{
	////////////////////////////////////////////////////////////
	Vertex_t::Vertex_t(void)
		: position(), normal(), uv()
	{
	}

	////////////////////////////////////////////////////////////
	Vertex_t::Vertex_t(const Vector3f& position, const Vector2f& uv)
		: position(position), normal(), uv(uv)
	{
	}

	////////////////////////////////////////////////////////////
	Vertex_t::Vertex_t(const Vector3f& position, const Vector3f& normal, const Vector2f& uv)
		: position(position), normal(normal), uv(uv)
	{
	}
}