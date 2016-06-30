#pragma once
#include "Event.h"
#include "GameTime.h"
#include <memory>

namespace Library
{
	class EventQueue
	{

	public:
		/**
		Default constructor
		*/
		EventQueue();

		/**
		Destructor
		*/
		~EventQueue();

		/**
		Given the address of an event publisher, current time, and an optional delay time, either enqueue the event or deliver it immediately

		@param publisher a shared pointer of an event publisher to enqueue or deliver
		@param curTime the current time
		@param delay the optional delay time. Defaults to zero
		*/
		void Enqueue(std::shared_ptr<EventPublisher> publisher, const GameTime& curTime, const double& delay = 0);

		/**
		Given the adderss of an event publisher, send the event immediately

		@param publisher the address of an event publisher to send immediately
		*/
		void Send(std::shared_ptr<EventPublisher> publisher);

		/**
		Given the current time, publish any queued events that have expired

		@param curTime the current time
		*/
		void Update(const GameTime& curTime);

		/**
		Clear the event queue, sending any expired events

		@param curTime the current time
		*/
		void Clear(const GameTime& curTime);

		/**
		Return a boolean indicating the emptiness of the queue

		@return true if the queue is empty. False otherwise
		*/
		bool IsEmpty() const;

		/**
		Return the number of events in the queue

		@return the number of events in the queue
		*/
		std::uint32_t Count() const;

	private:
		SList<std::shared_ptr<EventPublisher>> mQueue;
	
	};
}