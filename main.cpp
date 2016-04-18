#include <sparky\utils\debug.hpp>
#include <sparky\core\window.hpp>
#include <sparky\core\pool.hpp>
#include <sparky\utils\config.hpp>
#include <sparky\rendering\meshdata.hpp>

using namespace sparky;

int main(int argc, char** argv)
{
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

	MeshData* pMesh = new MeshData();

	Vertex_t v1(Vector3f(-0.5f, -0.5f, 0.0f), Vector2f(0.0f, 0.0f));
	Vertex_t v2(Vector3f( 0.5f, -0.5f, 0.0f), Vector2f(1.0f, 0.0f));
	Vertex_t v3(Vector3f( 0.5f,  0.5f, 0.0f), Vector2f(1.0f, 1.0f));
	Vertex_t v4(Vector3f(-0.5f,  0.5f, 0.0f), Vector2f(0.0f, 1.0f));

	pMesh->addFace(v1, v2, v3, v4, 0);

	pMesh->generate();

	pMesh->addRef();

	while (window.isRunning())
	{
		window.clear();

		pMesh->render();

		window.swap();

		sparky::PoolManager::getInstance().flush();
	}

	SDL_Quit();

	return 0;
}