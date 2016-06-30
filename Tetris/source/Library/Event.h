#pragma once
#include "EventPublisher.h"
#include <memory>

namespace Library
{
	template <typename T>
	class Event : public EventPublisher
	{
		RTTI_DECLARATIONS(Event<T>, EventPublisher)

	public:
		/**
		Default constructor
		*/
		Event();

		/**
		Destructor
		*/
		~Event();

		/**
		Constructor takes a const reference to a message object (the templated T)

		@param message the message object to publish (const reference)
		*/
		Event(const T& message);

		/**
		Given the address of an EventSubscriber, add it to the list of subscribers for this type

		@param address the EventSubscriber to add to the lsit
		*/
		static void Subscribe(EventSubscriber* address);

		/**
		Given the address of an eventSubscriber, remove it from the list of subscribers for this event type

		@param address the EventSubscriber to remove from the list
		*/
		static void Unsubscribe(EventSubscriber* address);

		/**
		Unsubscribe all subscribers to this event type
		*/
		static void UnsubscribeAll();

		/**
		Return message object
		*/
		const T& Message() const;

	private:

		/**
		Static list for this instance
		*/
		static std::shared_ptr<SList<EventSubscriber*>> sSubscribers;

		/**
		Current message for this event
		*/
		T mMessage;
		
	};

}

#include "Event.inl"
