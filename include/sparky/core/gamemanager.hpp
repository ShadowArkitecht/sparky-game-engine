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
	class FinalShader;
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
		std::vector<Scene*>			   m_scenes;			// The scenes within the application.
		AmbientShader*				   m_pAmbient;			// The global ambient colour of all geometry.
		FinalShader*				   m_pShader;			// The shader that actually renders the scene.
		MeshData*					   m_pQuad;				// The complete scene is render onto this quad.

		std::vector<DirectionalLight*> m_directionalLights; // The directional lights within this frame.
		std::vector<PointLight*>	   m_pointLights;		// The point lights within this frame.
		DirectionalLight*			   m_pActiveDirectional;// The current directional light being used.
		PointLight*					   m_pActivePoint;		// The current point light being used.

		GBuffer						   m_buffer;			// The deferred rendering pipeline uses this GBuffer.

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
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the currently active directional light.
		///
		/// The active light refers to the light that the shaders are
		/// next going to use to apply lighting to geometry.
		///
		/// \retval DirectionalLight	The currently active directional light.
		///
		////////////////////////////////////////////////////////////
		DirectionalLight* getActiveDirectional(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the currently active point light.
		///
		/// The active light refers to the light that the shaders are
		/// next going to use to apply lighting to geometry.
		///
		/// \retval PointLight	The currently active point light.
		///
		////////////////////////////////////////////////////////////
		PointLight* getActivePoint(void) const;

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
		/// \brief Pushes a scene to the top of the stack.
		///
		/// When a scene is pushed to the stack, the scene at the top
		/// will be the one to render and update. This allows for a
		/// dynamic amount of scenes to be rendered and updated.
		///
		/// \param pScene	The scene to push to the stack.
		///
		////////////////////////////////////////////////////////////
		void pushScene(Scene* pScene);

		////////////////////////////////////////////////////////////
		/// \brief Pops a scene from the top of the stack.
		///
		/// When a scene is popped from the stack, it is removed and the
		/// scene beneath will now render and update. The scene can be
		/// optionally destroyed upon removal.
		///
		/// \param remove	Whether the scene will be destroyed upon popping.
		///
		////////////////////////////////////////////////////////////
		void popScene(const bool remove = false);

		////////////////////////////////////////////////////////////
		/// \brief Adds a directional light to the engine.
		///
		/// Lights are added each frame so that multi-pass lighting can
		/// be achieved to get a arbitrary number of lights.
		///
		/// \param pLight	The directional light to add to the application.
		///
		////////////////////////////////////////////////////////////
		void addDirectionalLight(DirectionalLight* pLight);

		////////////////////////////////////////////////////////////
		/// \brief Adds a point light to the engine.
		///
		/// Lights are added each frame so that multi-pass lighting can
		/// be achieved to get a arbitrary number of lights.
		///
		/// \param pLight	The point light to add to the application.
		///
		////////////////////////////////////////////////////////////
		void addPointLight(PointLight* pLight);

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
/// additional behaviour.
///
////////////////////////////////////////////////////////////