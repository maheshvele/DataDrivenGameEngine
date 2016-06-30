#pragma once
#include "RTTI.H"
#include "EventSubscriber.h"
#include "SList.h"

namespace Library
{
	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)

	public:
		/**
		Default constructor
		*/
		EventPublisher();

		/**
		Destructor
		*/
		~EventPublisher();

		/**
		Constructor with subscriber list and deleteAfterPublishing flag

		@param list the list of subscribers to initialize our pointer with
		@param toDelete a boolean indicating the value of our deleteAfterPublishing flag
		*/
		EventPublisher(std::shared_ptr<SList<EventSubscriber*>>& list);

		/**
		Given a double for current time and an optional double for delay, assign those values for this event

		@param timeEnqueued the current time stored as a double
		@param delay optional value for delay. Defaults to zero
		*/
		void SetTime(const double& enqueueTime, const double& delay = 0);

		/**
		Return the time when this event was enqueued

		@return the time this event was enqueued
		*/
		double TimeEnqueued() const;

		/**
		Return the duration after being enqueued that this event expires

		@return the duration after being enqueued that this every expires
		*/
		double Delay() const;

		/**
		Take the current time and return true if the event has expired (expires at time enqueued + delay)

		@param time the current time
		@return true if the current time is greater than or equal to time enqueued + delay. False otherwise
		*/
		bool IsExpired(const double& time) const;

		/**
		Notify all subscribers of this event
		*/
		void Deliver();

	protected:

		/**
		Pointer to a list of subscribers who we comminicate with via deliver
		*/
		std::shared_ptr<SList<EventSubscriber*>> mSubscribers;

		/**
		The time at which we were added to the event queue
		*/
		double mEnqueueTime;

		/**
		How long to wait until delivering the event
		*/
		double mDelay;

	};
}