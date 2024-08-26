#include "EventSystem.h"

void EventSystem::AddObserver(const id_t& id, Observer* observer, EventHandler eventHandler)
{
	Dispatcher dispatcher;
	dispatcher.observer = observer;
	dispatcher.eventhandler = eventHandler;

	m_dispatchers[id].push_back(dispatcher);
}

void EventSystem::RemoveObserver(Observer* observer)
{
	for (auto& element : m_dispatchers)
	{
		auto dispatchers = element.second;
		std::erase_if(dispatchers, [observer](auto& dispatcher) { return dispatcher.observer == observer; });
	}
}

void EventSystem::Notify(const Event& event)
{
	auto iter = m_dispatchers.find(event.id);
	if (iter != m_dispatchers.end())
	{
		auto dispatchers = iter->second; // get list of dispatchers
		for (auto& dispatcher : dispatchers)
		{
			dispatcher.eventhandler(event);
		}
	}
}
