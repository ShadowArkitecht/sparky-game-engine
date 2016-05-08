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

#ifndef __SPARKY_SCENE_HPP__
#define __SPARKY_SCENE_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\core\ref.hpp>	// Scene will be a dynamically allocated object.

namespace sparky
{
	class Scene : public Ref
	{
	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor for the Scene object class.
		////////////////////////////////////////////////////////////
		explicit Scene(void);

		////////////////////////////////////////////////////////////
		/// \brief Destructor for the Scene object class.
		////////////////////////////////////////////////////////////
		virtual ~Scene(void) = default;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Pure virtual update method for scenes.
		///
		/// The update method will be overwritten by child classes.
		/// The update will be called every frame and should contain all
		/// the logic and processing of the current Scene.
		///
		////////////////////////////////////////////////////////////
		virtual void update(void) = 0;

		////////////////////////////////////////////////////////////
		/// \brief Pure virtual render method for scenes.
		///
		/// The render method will be overwritten by child classes.
		/// The rendering will be called every frame and should only contain
		/// the information to render specific objects.
		///
		////////////////////////////////////////////////////////////
		virtual void render(void) = 0;
	};

}//namespace sparky

#endif//__SPARKY_SCENE_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Scene
/// \ingroup core
///
/// sparky::Scene is an abstract class in which all scenes will
/// inherit from in an application. A scene refers to a level
/// in a game, the scenes can be pushed and popped from the Game
/// Manager stack so that more functionality can easily be added
/// or removed.
///
/// Below is a code example where a child class for Game has
/// theoretically been created.
///
/// Usage example:
/// \code
/// // Create a new Game object.
/// Game* pGame = new Game();
///
/// // Add the game as the first level in the application.
/// sparky::GameManager::getInstance().pushScene(pGame);
/// \endcode
///
////////////////////////////////////////////////////////////