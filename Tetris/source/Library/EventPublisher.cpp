#include "pch.h"
#include "EventPublisher.h"

namespace Library
{

	RTTI_DEFINITIONS(EventPublisher)

	//Default constructor
	EventPublisher::EventPublisher() :
		mDelay(0)
	{
	}

	//Destructor
	EventPublisher::~EventPublisher()
	{
	}

	//Constructor with subscriber list
	EventPublisher::EventPublisher(std::shared_ptr<SList<EventSubscriber*>>& list) :
		mDelay(0)
	{
		mSubscribers = list;
	}

	//Set the current time and delay for our event
	void EventPublisher::SetTime(const double& enqueueTime, const double& delay)
	{
		mEnqueueTime = enqueueTime;
		mDelay = delay;
	}

	//Getter for mEnqueueTime
	double EventPublisher::TimeEnqueued() const
	{
		return mEnqueueTime;
	}

	//Getter for mDelay
	double EventPublisher::Delay() const
	{
		return mDelay;
	}

	//See if the event is passed its expiration time
	bool EventPublisher::IsExpired(const double& time) const
	{
		if (time > mEnqueueTime + mDelay)
		{
			return true;
		}
		return false;
	}

	//Notify all subscribers of us
	void EventPublisher::Deliver()
	{
		for (auto& item : (*mSubscribers))
		{
			item->Notify(this);
		}
	}
}