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


#ifndef __SPARKY_WINDOW_HPP__
#define __SPARKY_WINDOW_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\utils\string.hpp>  // Used to store the name of Window.
#include <sparky\math\vector2.hpp>	// Vector2 functionality. Used for position and size of Window.
#include <sparky\utils\context.hpp> // Additional context information for the Window and OpenGL flags.
/*
====================
Additional Includes
====================
*/
#include <SDL\SDL.h>				// Provides access to SDL library.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class ConfigFile;

	class Window final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		static Window* m_pMain;		// Static Reference to the Camera.
		SDL_Window*	   m_pWindow;	// The SDL Window context.
		SDL_GLContext  m_GLcontext;	// The context between SDL and OpenGL.
		String   	   m_title;		// The title of the Window.
		Vector2i       m_position;	// The position of the Window on the screen.
		Vector2i       m_size;		// The size/dimensions of the Window.
		bool		   m_running;	// Whether the Window is currently running.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		///	\brief Constructs a Window object instance. 
		///
		///	This constructor does not actually construct the window,
		/// it sets all of the Window member variables to default
		/// values. To construct a Window using this constructor, the
		/// create method must be subsequently called.
		///
		////////////////////////////////////////////////////////////
		explicit Window(void);

		////////////////////////////////////////////////////////////
		///	\brief Constructs a Window object instance. 
		///
		///	This constructor subsequently calls the create method and
		/// creates a window with the specified parameters, the window
		/// can be optionally constructed into full-screen mode. The context
		/// for the window can be provided for additional OpenGL behaviour.
		/// 
		///	\param title	The title of the Window object (which appears in the Windows taskbar).
		///	\param position	The position that the Window will appear on the Desktop.
		///	\param size		The dimensions of the Window.
		/// \param context	The context that will be applied to the OpenGL functionality of the Window.
		///
		////////////////////////////////////////////////////////////
		explicit Window(const String& title, const Vector2i& position, const Vector2i& size, const ContextSettings& context = ContextSettings());

		////////////////////////////////////////////////////////////
		///	\brief Constructs a Window object instance. 
		///
		///	This constructor subsequently calls the create method and
		/// creates a window with the specified parameters, which are
		/// retrieved from the configuration file.
		/// 
		///	\param config	The configuration file the settings are read from.
		///
		////////////////////////////////////////////////////////////
		explicit Window(const ConfigFile& config);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of a Window object instance.
		///
		///	The destructor will free the resources being used by the SDL
		/// GL context and destroy the SDL_Window itself.
		///
		////////////////////////////////////////////////////////////
		~Window(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Gets the main Window object of the current application.
		/// 
		///	When the Window is first created, if no window has been 
		/// created before this instance, it is set to be the main Window
		/// object. This method allows for global access to the Window,
		/// which is useful for several elements such as positioning HUD
		/// in screen-space.
		///
		/// \retval main	The main Window object of the current application.
		///
		////////////////////////////////////////////////////////////
		static Window& getMain(void);

		////////////////////////////////////////////////////////////
		/// \brief Gets the title of the Window object.
		///
		/// The title refers to the name of the Window itself, the name
		/// of the Window is first set when the camera is constructed.
		///
		/// \retval title	Gets the current title of the Window object.
		///
		////////////////////////////////////////////////////////////
		const String& getTitle(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Set the title of the Window object.
		///
		/// The title refers to the name of the Window itself, the name
		/// of the Window can be changed at run-time by utilising this
		/// method. 
		///
		/// \param title	The new title of the Window object.
		///
		////////////////////////////////////////////////////////////
		void setTitle(const String& title);

		////////////////////////////////////////////////////////////
		/// \brief Gets the position of the Window object.
		///
		/// The position refers to the position of the Window object on
		/// the desktop. The position is first set when the object is 
		/// constructed.
		///
		/// \retval position	The current position of the Window object.
		///
		////////////////////////////////////////////////////////////
		const Vector2i& getPosition(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the position of the Window object.
		///
		/// The position refers to the position of the Window object on
		/// the desktop. Altering this value will change the position of the
		/// Window object. 
		///
		/// \param position		The new position of the Window object.
		///
		////////////////////////////////////////////////////////////
		void setPosition(const Vector2i& position);

		////////////////////////////////////////////////////////////
		/// \brief Gets the size of the Window object. 
		///
		/// The size refers to the dimensions of the Window object. The size
		/// is first defined when the Window is initially created. If the window
		/// is currently full size, the size is superfluous.
		///
		/// \retval	size	The current dimensions of the Window object.
		///
		////////////////////////////////////////////////////////////
		const Vector2i& getSize(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the size of the Window object.
		///
		/// The size refers to the dimensions of the Window object. The size
		/// is first defined when the Window is initially created. If the window
		/// is currently full size, the size is superfluous. If the Window is
		/// not full size, this will change the dimensions of the Window.
		///
		/// \param size		The new size of the Window object.
		///
		////////////////////////////////////////////////////////////
		void setSize(const Vector2i& size);

		////////////////////////////////////////////////////////////
		/// \brief Checks to see if the Window object is currently running.
		///
		/// When the Window object is created and initialised successfully, 
		/// the Window is automatically set to running, when the window is 
		/// closed, the running variable is set to false.
		///
		/// \retval	running		Whether the Window object is currently running.
		///
		////////////////////////////////////////////////////////////
		bool isRunning(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the running state of the Window object.
		/// 
		/// When the Window object is running, it will continue to run, if the
		/// running state is set to false, the application will stop and the 
		/// window will be deleted.
		///
		/// \param running	The new state of the Window object.
		///
		////////////////////////////////////////////////////////////
		void setRunning(const bool running);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Creates a Window object.
		///
		/// If a Window is constructed with the variable constructor, this
		/// subsequent method must be called in order to create a Window.
		/// This method provides additional error checking to make sure all
		/// elements of the window initialise correctly. If any of the steps
		/// fail, the method will return false and an error message will be
		/// presented to the console window.
		///
		/// \param title	The title of the Window object.
		/// \param position The position of the Window object on the desktop.
		/// \param size		The size/dimensions of the Window object.
		/// \param context	Additional contextual information about the Window object.
		///
		/// \retval bool	Returns true if the Window object initialise successfully.
		///
		////////////////////////////////////////////////////////////
		bool create(const String& title, const Vector2i& position, const Vector2i& size, const ContextSettings& context = ContextSettings());

		////////////////////////////////////////////////////////////
		/// \brief Creates a Window object.
		///
		/// If a Window is constructed with the config constructor, this
		/// subsequent method must be called in order to create a Window.
		/// This method provides additional error checking to make sure all
		/// elements of the window initialise correctly. If any of the steps
		/// fail, the method will return false and an error message will be
		/// presented to the console window.
		///
		/// \param config	The configuration file which contains the window settings.
		///
		/// \retval bool	Returns true if the Window object initialise successfully.
		///
		////////////////////////////////////////////////////////////
		bool create(const ConfigFile& config);

		////////////////////////////////////////////////////////////
		/// \brief Clears the current Window object.
		///
		/// This method is called at the beginning of every frame, it calls
		/// OpenGL functionality to clear the currently rendered scene.
		///
		////////////////////////////////////////////////////////////
		void clear(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Swaps the window buffers.
		///
		/// When a scene renders, it renders to the back-buffer. What the user
		/// is currently seeing is the previously rendering scene, when this 
		/// method is called, the back buffer is swapped with the front 
		/// buffer so that the next frame can be rendered.
		///
		////////////////////////////////////////////////////////////
		void swap(void) const;
	};

}//namespace sparky

#endif//__SPARKY_WINDOW_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Window
///	\ingroup core
///
/// sparky::Window is one of the main important classes of the
/// Sparky Engine. It defines an SDL window that can be painted
/// and rendered upon by subsequent classes in the graphics
/// module.
///
/// sparky::Window is only responsible for the rendering of
/// objects, it does not includes any event management or input.
/// Window should be one of the first elements initialised in any
/// sparky application. 
/// Below is a typical example of how the Window can be used for
/// a rendering loop (although some of this functionality may be
/// handled internally).
///
/// \code 
/// // Create a new Window.
/// sparky::Window window;
/// window.create("Sparky!", Vector2i(), Vector2i(640, 480));
///
/// // Basic Main window loop.
/// while (window.isRunning())
/// {
///		window.clear()
///		// Rendering of objects should go here.
///		window.swap();
/// }
///
////////////////////////////////////////////////////////////