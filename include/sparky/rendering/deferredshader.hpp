#ifndef __SPARKY_DEFERRED_SHADER_HPP__
#define __SPARKY_DEFERRED_SHADER_HPP__

#include <sparky\rendering\ishader.hpp>

namespace sparky
{
	class DeferredShader final : public IShaderComponent
	{
	public:
		explicit DeferredShader(void);
		~DeferredShader(void) = default;

		void update(const Transform& transform) override;
	};

}//namespace sparky

#endif//__SPARKY_DEFERRED_SHADER_HPP__