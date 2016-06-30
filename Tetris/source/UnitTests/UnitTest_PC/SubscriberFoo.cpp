#include "SubscriberFoo.h"

namespace Library
{
	SubscriberFoo::SubscriberFoo() :
		mNumActivations(0)
	{
	}

	SubscriberFoo::~SubscriberFoo()
	{
	}

	int SubscriberFoo::GetActivations()
	{
		return mNumActivations;
	}

	int SubscriberFoo::GetLastActivation()
	{
		return mLastActivation;
	}

	void SubscriberFoo::Notify(EventPublisher* publisher)
	{
		Event<int>* ev = publisher->As<Event<int>>();

		if (ev != nullptr)
		{
			mNumActivations++;
			mLastActivation = ev->Message();
		}
	}

}