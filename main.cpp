#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>
#include <GLEW\glew.h>

#include <sparky\utils\debug.hpp>
#include <sparky\core\window.hpp>
#include <sparky\core\pool.hpp>
#include <sparky\utils\config.hpp>
#include <sparky\generation\chunk.hpp>

#include <sparky\rendering\program.hpp>
#include <sparky\rendering\uniform.hpp>

using namespace sparky;

int main(int argc, char** argv)
{
	SDL_SetMainReady();
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		DebugLog::error("SDL has failed to initialize.", SDL_GetError());
	}

	ConfigFile file;
	file.open("data/config.scfg");

	Window window;
	window.create(file);

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	
	if (error != GLEW_OK)
	{
		DebugLog::error("Failed to initalise GLEW.", glewGetErrorString(error));
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Program p;

	p.attachShader(new GLSLObject("shaders/basic_vertex.glsl", eShaderType::VERTEX_SHADER));
	p.attachShader(new GLSLObject("shaders/basic_fragment.glsl", eShaderType::FRAGMENT_SHADER));

	p.link();

	Uniform u(&p);

	Matrix4f s = Matrix4f::scale(Vector3f(1.0f, 1.0f, 1.0f));
	Matrix4f r = Matrix4f::rotation(Vector3f(0.0f, 0.0f, 0.0f));
	Matrix4f t = Matrix4f::translation(Vector3f(0.0f, 0.0f, 0.0f));

	Matrix4f view = Matrix4f::translation(Vector3f(0.0f, 0.0f, 10.0f)) * Matrix4f::perspective(Vector3f::forward(), Vector3f::up());
	Matrix4f proj = Matrix4f::projection(45.0f, 640.0f / 480.0f, 1.0f, 1000.0f);

	Chunk* pChunk = new Chunk();

	pChunk->getVoxel(0, 0, 0).setActive(false);

	pChunk->greedy();

	pChunk->addRef();

	while (window.isRunning())
	{
		r = r * Matrix4f::pitchRotation(3.0f * 0.0016f);

		Matrix4f mvp = (s * r * t) * view * proj;

		window.clear();

		p.bind();

		u.setParameter("u_mvp", mvp);

		pChunk->render();

		p.unbind();

		window.swap();

		sparky::Event e;
		while (window.onEvent(e))
		{
			if (e.type == SDL_QUIT)
			{
				window.setRunning(false);
			}
		}

		sparky::PoolManager::getInstance().flush();
	}

	SDL_Quit();

	return 0;
}