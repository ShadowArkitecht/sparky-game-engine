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

#ifndef __SPARKY_GAME_MANAGER_HPP__
#define __SPARKY_GAME_MANAGER_HPP__

/*
====================
CPP Includes
====================
*/
#include <vector>						// Container for different scenes.
/*
====================
Member Variables
====================
*/
#include <sparky\utils\singleton.hpp>	// Game Manager is a singleton object.
#include <sparky\rendering\gbuffer.hpp> // The deferred rendering pipeline GBuffer

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class Scene;
	class AmbientShader;
	class DirectionalShader;
	class PointShader;
	class MeshData;
	class DirectionalLight;
	class PointLight;

	class GameManager final : public Singleton<GameManager>
	{
		friend class Singleton<GameManager>;

	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::vector<Scene*>			   m_scenes;			///< The scenes within the application.
		AmbientShader*				   m_pAmbient;			///< The global ambient colour of all geometry.
		DirectionalShader*			   m_pDirectional;		///< The shader that actually renders the directional lights.
		PointShader*				   m_pPoint;			///< The shader that renders the point lights.
		MeshData*					   m_pQuad;				///< The complete scene is render onto this quad.
															  
		std::vector<DirectionalLight*> m_directionalLights; ///< The directional lights within this frame.
		std::vector<PointLight*>	   m_pointLights;		///< The point lights within this frame.
															  
		GBuffer						   m_buffer;			///< The deferred rendering pipeline uses this GBuffer.

	private:
		/*
		====================
		Ctor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructor for the GameManager singleton.
		///
		/// The constructor will initialise all of the member variables
		/// to default values.
		///
		////////////////////////////////////////////////////////////
		GameManager(void);

	public:
		/*
		====================
		Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Destructor of the GameManager singleton object.
		///
		/// The destructor will de-allocate all of the scenes currently
		/// being stored and release their resources.
		///
		////////////////////////////////////////////////////////////
		~GameManager(void);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Initialises all of the libraries (bar SDL) that
		///        will be used within the application.
		////////////////////////////////////////////////////////////
		void init(void);

		////////////////////////////////////////////////////////////
		/// \brief Adds a DirectionalLight to the engine.
		///
		/// Lights are added each frame so that multi-pass lighting can
		/// be achieved to get a arbitrary number of lights.
		///
		/// \param pLight	The DirectionalLight to add to the application.
		///
		////////////////////////////////////////////////////////////
		void addLight(DirectionalLight* pLight);

		////////////////////////////////////////////////////////////
		/// \brief Adds a PointLight to the engine.
		///
		/// Lights are added each frame so that multi-pass lighting can
		/// be achieved to get a arbitrary number of lights.
		///
		/// \param pLight	The PointLight to add to the application.
		///
		////////////////////////////////////////////////////////////
		void addLight(PointLight* pLight);

		////////////////////////////////////////////////////////////
		/// \brief Pushes a Scene to the top of the stack.
		///
		/// When a Scene is pushed to the stack, the Scene at the top
		/// will be the one to render and update. This allows for a
		/// dynamic amount of scenes to be rendered and updated.
		///
		/// \param pScene	The Scene to push to the stack.
		///
		////////////////////////////////////////////////////////////
		void pushScene(Scene* pScene);

		////////////////////////////////////////////////////////////
		/// \brief Pops a Scene from the top of the stack.
		///
		/// When a Scene is popped from the stack, it is removed and the
		/// Scene beneath will now render and update. The Scene can be
		/// optionally destroyed upon removal.
		///
		/// \param remove	Whether the Scene will be destroyed upon popping.
		///
		////////////////////////////////////////////////////////////
		void popScene(const bool remove = false);

		////////////////////////////////////////////////////////////
		/// \brief Renders and updates the scene at the top of the stack.
		////////////////////////////////////////////////////////////
		void run(void);

	};

}//namespace sparky

#endif//__SPARKY_GAME_MANAGER_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::GameManager
/// \ingroup core
///
/// sparky::GameManager is one of the most important classes within
/// the application. It is the culmination of all of the different
/// aspects of the engine, all executing within it's scope. It is responsible
/// for rendering and updating scenes, flushing the release pool, handling
/// the events and deferring the rendering.
///
/// Scenes can be added and removed from the Game Manager for
/// additional behaviour. Below is a code example.
///
/// Example Usage:
/// \code 
/// // Theoretical scene called Game that's inherits from sparky::Scene
/// Game* pGame = new Game();
/// 
/// // Add the Game to the GameManager singleton.
/// GameManager::getInstance().pushScene(pGame);
/// \endcode
///
////////////////////////////////////////////////////////////