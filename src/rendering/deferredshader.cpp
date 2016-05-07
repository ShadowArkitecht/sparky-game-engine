#include <sparky\rendering\deferredshader.hpp>
#include <sparky\math\transform.hpp>
#include <sparky\core\camera.hpp>

namespace sparky
{
	DeferredShader::DeferredShader(void)
		: IShaderComponent("shaders/deferred_vertex.glsl", "shaders/deferred_fragment.glsl")
	{
	}
	
	void DeferredShader::update(const Transform& transform)
	{
		Matrix4f mvp = transform.getTransformation() * Camera::getMain().getViewProjection();

		m_uniform.setParameter("u_mvp", mvp);
		m_uniform.setParameter("u_model", transform.getTransformation());

		m_uniform.setParameter("u_texture", 0);
	}

}//namespace sparky