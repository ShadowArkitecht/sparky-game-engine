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
#include <sparky\input\eventmanager.hpp>	// Class definition.
#include <sparky\input\ievent.hpp>			// Updating the events.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	EventManager::EventManager(void)
		: Singleton<EventManager>(), m_events()
	{
	}

	////////////////////////////////////////////////////////////
	EventManager::~EventManager(void)
	{
		this->clear();
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void EventManager::addPoll(IEventComponent* pEvent)
	{
		pEvent->addRef();
		m_events.push_back(pEvent);
	}

	////////////////////////////////////////////////////////////
	void EventManager::removePoll(IEventComponent* pEvent)
	{
		if (!m_events.empty())
		{
			auto itr = std::find(std::begin(m_events), std::end(m_events), pEvent);

			if (itr != m_events.end())
			{
				m_events.erase(itr);
				Ref::release(pEvent);
			}
		}
	}

	////////////////////////////////////////////////////////////
	void EventManager::poll(void)
	{
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			for (const auto& e : m_events)
			{
				e->update(ev);
			}
		}
	}

	////////////////////////////////////////////////////////////
	void EventManager::clear(void)
	{
		if (!m_events.empty())
		{
			std::vector<IEventComponent*> releases;
			releases.swap(m_events);

			for (auto& r : releases)
			{
				Ref::release(r);
			}

			releases.clear();
		}
	}

}//namespace sparky