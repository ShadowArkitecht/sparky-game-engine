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
CPP Includes
====================
*/
#include <iostream>					// Temporary error message printing.
/*
====================
Class Includes
====================
*/
#include <sparky\core\window.hpp>	// Class definition.
/*
====================
Additional Includes
====================
*/
#include <GLEW\glew.h>				// Access to the OpenGL GLEW library.

namespace sparky
{
	/*
	====================
	Static Fields
	====================
	*/
	Window* Window::m_pMain = nullptr;

	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Window::Window(void)
		: m_pWindow(nullptr), m_GLcontext(), m_title(), m_position(), m_size(), m_running(false)
	{
	}

	////////////////////////////////////////////////////////////
	Window::Window(const String& title, const Vector2i& position, const Vector2i& size, const ContextSettings& context)
		: m_pWindow(nullptr), m_GLcontext(), m_title(), m_position(), m_size(), m_running(false)
	{
		if (!this->create(title, position, size, context))
		{
			return;
		}
	}

	////////////////////////////////////////////////////////////
	Window::~Window(void)
	{
		if (m_GLcontext)
		{
			SDL_GL_DeleteContext(m_GLcontext);
		}

		if (m_pWindow)
		{
			SDL_DestroyWindow(m_pWindow);
			m_pWindow = nullptr;
		}
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	Window& Window::getMain(void)
	{
		return *m_pMain;
	}

	////////////////////////////////////////////////////////////
	const String& Window::getTitle(void) const
	{
		return m_title;
	}

	////////////////////////////////////////////////////////////
	void Window::setTitle(const String& title)
	{
		SDL_SetWindowTitle(m_pWindow, title.getCString());
		m_title = title;
	}

	////////////////////////////////////////////////////////////
	const Vector2i& Window::getPosition(void) const
	{
		return m_position;
	}

	////////////////////////////////////////////////////////////
	void Window::setPosition(const Vector2i& position)
	{
		SDL_SetWindowPosition(m_pWindow, position.x, position.y);
		m_position = position;
	}

	////////////////////////////////////////////////////////////
	const Vector2i& Window::getSize(void) const
	{
		return m_size;
	}

	////////////////////////////////////////////////////////////
	void Window::setSize(const Vector2i& size)
	{
		SDL_SetWindowSize(m_pWindow, size.x, size.y);
		m_size = size;
	}

	////////////////////////////////////////////////////////////
	bool Window::isRunning(void) const
	{
		return m_running;
	}

	////////////////////////////////////////////////////////////
	void Window::setRunning(const bool running)
	{
		m_running = running;
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	bool Window::create(const String& title, const Vector2i& position, const Vector2i& size, const ContextSettings& context)
	{
		m_title = title;
		m_position = position;
		m_size = size;

		// Initialise the Window.
		m_pWindow = SDL_CreateWindow(title.getCString(), position.x, position.y, size.x, size.y, SDL_WINDOW_OPENGL);

		// Error check the Window.
		if (!m_pWindow)
		{
			std::cout << "SDL_Window has failed to initialise:" << SDL_GetError() << std::endl;
			return false;
		}

		// Provide OpenGL context for the Window.
		m_GLcontext = SDL_GL_CreateContext(m_pWindow);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, context.majorVersion);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, context.minorVersion);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		m_running = true;

		// Set the main Window object for the application.
		if (!m_pMain)
		{
			m_pMain = this;
		}

		return true;
	}

	////////////////////////////////////////////////////////////
	void Window::clear(void) const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	////////////////////////////////////////////////////////////
	void Window::swap(void) const
	{
		SDL_GL_SwapWindow(m_pWindow);
	}

}//namespace sparky