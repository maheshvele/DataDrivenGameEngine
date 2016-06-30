#include "pch.h"
#include "Event.h"

namespace Library
{
	template <typename T>
	std::shared_ptr<SList<EventSubscriber*>> Event<T>::sSubscribers = std::make_shared<SList<EventSubscriber*>>();

	template <typename T>
	RTTI_DEFINITIONS(Event<T>)

	//Default Constructor
	template <typename T>
	Event<T>::Event() :
		EventPublisher(sSubscribers)
	{
	}

	//Destructor
	template <typename T>
	Event<T>::~Event()
	{
	}

	//Constructor that takes a reference to a message object
	template <typename T>
	Event<T>::Event(const T& message) :
		mMessage(message), EventPublisher(sSubscribers)
	{		
	}

	//Add a subscriber to our subscriber list
	template <typename T>
	void Event<T>::Subscribe(EventSubscriber* address)
	{
		if (sSubscribers != nullptr)
		{
			sSubscribers->PushBack(address);
		}
		else
		{
			throw std::exception("No Events of ths type exist");
		}
	}

	//Remove a subscriber from our list
	template <typename T>
	void Event<T>::Unsubscribe(EventSubscriber* address)
	{
		if (sSubscribers != nullptr)
		{
			sSubscribers->Remove(address);
		}
	}

	//Unsubscribe all subscribers to this event
	template <typename T>
	void Event<T>::UnsubscribeAll()
	{
		if (sSubscribers != nullptr)
		{
			sSubscribers->Clear();
		}
	}

	//Get our current message object
	template <typename T>
	const T& Event<T>::Message() const
	{
		return mMessage;
	}

}