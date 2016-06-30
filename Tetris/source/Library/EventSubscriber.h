#pragma once
#include <memory>

namespace Library
{
	/**
	Abstract base class used for items that need to communicate with an event publisher
	*/

	//Forward declaration for EventPublisher
	class EventPublisher;

	class EventSubscriber
	{
	public:
		/**
		Default constructor
		*/
		EventSubscriber() = default;

		/**
		Destructor
		*/
		virtual ~EventSubscriber() = default;

		/**
		Pure virtual method that acccepts the address of an EventPublisher. Concrete handlers will use the lightweight RTTI interface to verify the actual event type

		@param publisher the address of a publisher
		*/
		virtual void Notify(EventPublisher* publisher) = 0;
	};
}