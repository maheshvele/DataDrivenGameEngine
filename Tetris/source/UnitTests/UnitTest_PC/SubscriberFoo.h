#pragma once
#include "Event.h"

namespace Library
{
	class SubscriberFoo : public EventSubscriber
	{
	public:
		//Constructor
		SubscriberFoo();

		//Destructor
		virtual ~SubscriberFoo();

		//Getter for mNumActivations
		int GetActivations();

		//Getter for mLastActivation
		int GetLastActivation();

		//Increments mNumActivations if the RTTI type of the given publisher is Event<int>
		//Also store its message
		virtual void Notify(EventPublisher* publisher);

	private:
		int mNumActivations;
		int mLastActivation;
	};
}