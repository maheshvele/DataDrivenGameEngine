#include "pch.h"
#include "EventQueue.h"

namespace Library
{
	//Default constructor
	EventQueue::EventQueue() :
		mQueue()
	{
	}

	//Destructor
	EventQueue::~EventQueue()
	{
	}

	//Add a new event publisher to our queue
	void EventQueue::Enqueue(std::shared_ptr<EventPublisher> publisher, const GameTime& curTime, const double& delay)
	{
		(*publisher).SetTime(curTime.TotalGameTime(), delay);
		mQueue.PushBack(publisher);
	}

	//Send an event to its subscribers immediately
	void EventQueue::Send(std::shared_ptr<EventPublisher> publisher)
	{
		(*publisher).Deliver();
		mQueue.Remove(publisher);
	}

	//Go through our queue and publish any expired events
	void EventQueue::Update(const GameTime& curTime)
	{
		SList<std::shared_ptr<EventPublisher>>::Iterator i = mQueue.begin();
		while(i != mQueue.end())
		{
			if ((**i).IsExpired(curTime.TotalGameTime()))
			{
				(**i).Deliver();
				mQueue.Remove(*i);
				i = mQueue.begin();
			}
			else
			{
				i++;
			}
		}
	}

	void EventQueue::Clear(const GameTime& curTime)
	{
		Update(curTime);
		mQueue.Clear();
	}

	//Check if queue is empty
	bool EventQueue::IsEmpty() const
	{
		return mQueue.IsEmpty();
	}

	//Check how many items are in the queue
	std::uint32_t EventQueue::Count() const
	{		
		return mQueue.Size();
	}

}