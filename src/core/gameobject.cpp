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

/*
====================
Class Includes
====================
*/
#include <sparky\core\gameobject.hpp>	// Class definition.
#include <sparky\rendering\irender.hpp>	// The renderable component need to render.
#include <sparky\rendering\ishader.hpp>	// The shader will need to be updated with the GameObject transform.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	GameObject::GameObject(void)
		: Ref(), m_transform()
	{
	}

	////////////////////////////////////////////////////////////
	GameObject::GameObject(const Vector3f& position)
		: Ref(), m_transform(position, Quaternionf::identity())
	{
	}

	////////////////////////////////////////////////////////////
	GameObject::GameObject(const Vector3f& position, const Quaternionf& rotation)
		: Ref(), m_transform(position, rotation)
	{
	}

	////////////////////////////////////////////////////////////
	GameObject::GameObject(const Vector3f& position, const Quaternionf& rotation, const Vector3f& scale)
		: Ref(), m_transform(position, scale, rotation)
	{
	}

	////////////////////////////////////////////////////////////
	GameObject::~GameObject(void)
	{
		for (auto& renderable : m_renderables)
		{
			Ref::release(renderable);
		}
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	Transform& GameObject::getTransform(void)
	{
		return m_transform;
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void GameObject::addComponent(IRenderComponent* pRenderable)
	{
		if (pRenderable)
		{
			pRenderable->addRef();
			m_renderables.push_back(pRenderable);
		}
	}

	////////////////////////////////////////////////////////////
	void GameObject::render(IShaderComponent* pShader)
	{
		pShader->update(m_transform);

		for (const auto& renderable : m_renderables)
		{
			renderable->render();
		}
	}

}//namespace sparky