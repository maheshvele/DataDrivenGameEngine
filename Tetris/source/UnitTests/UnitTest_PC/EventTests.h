#include <cxxtest/TestSuite.h>
#include "EventQueue.cpp"
#include "Event.h"
#include "SubscriberFoo.h"

using namespace Library;

class EventTestSuite : public CxxTest::TestSuite
{
public:

	void setUp()
	{
#ifdef _DEBUG
		//Create a snapshot of the current debug heap
		//Used to check for memory leaks
		_CrtMemCheckpoint(&startSnapshot);
#endif
	}

	void tearDown()
	{
#ifdef _DEBUG
		//Compare the memory state at the end to our snapshot at the beginning
		_CrtMemState endSnapshpt, difference;
		_CrtMemCheckpoint(&endSnapshpt);
		if (_CrtMemDifference(&difference, &startSnapshot, &endSnapshpt))
		{
			_CrtMemDumpStatistics(&difference);
		}
#endif
	}

	//Ensure that instnatiation works
	void TestInstantiation(void)
	{
		EventQueue q;		
		TS_ASSERT(q.IsEmpty());
		TS_ASSERT_EQUALS(q.Count(), 0);

		int i = 10;
		Event<int> e(i);
		TS_ASSERT_EQUALS(e.Message(), 10);		
	}

	//Test the queue functions of EventQueue: Enqueue/Clear/IsEmpty/Count
	void TestQueueFunctions(void)
	{
		EventQueue q;
		std::shared_ptr<Event<int>> spe1 = std::make_shared<Event<int>>();
		std::shared_ptr<Event<int>> spe2 = std::make_shared<Event<int>>();
		GameTime gt;


		TS_ASSERT_EQUALS(q.Count(), 0);
		TS_ASSERT(q.IsEmpty());
		q.Enqueue(spe1, gt);
		TS_ASSERT_EQUALS(q.Count(), 1);
		q.Enqueue(spe2, gt);
		TS_ASSERT_EQUALS(q.Count(), 2);
		TS_ASSERT_EQUALS(q.IsEmpty(), false);
		q.Clear(gt);
		TS_ASSERT(q.IsEmpty());
		TS_ASSERT_EQUALS(q.Count(), 0);
	}

	//Test the time related functions fomr EventPublisher
	void TestTimeFunctions(void)
	{
		Event<int> e;

		//Should set both enqueueTime and delay to zero
		e.SetTime(0.0);
		TS_ASSERT_EQUALS(e.TimeEnqueued(), 0.0);
		TS_ASSERT_EQUALS(e.Delay(), 0.0);

		//Delay should now by 2.5
		e.SetTime(0.0, 2.5);
		TS_ASSERT_EQUALS(e.Delay(), 2.5);

		//Three cases exists for IsExpired: 
		
		//1. The time has not yet passed start + delay. The event has not yet expired
		TS_ASSERT(!e.IsExpired(0.1));
		
		//2. The time is equal to start + delay. The event has not yet expired
		TS_ASSERT(!e.IsExpired(2.5));

		//3. The time has passed start + delay. The event has expired
		TS_ASSERT(e.IsExpired(2.6));
	}

	//Test EventPublisher and Event subscription stuff
	void TestSubscription(void)
	{
		std::shared_ptr<SubscriberFoo> sf1 = std::make_shared<SubscriberFoo>();
		std::shared_ptr<SubscriberFoo> sf2 = std::make_shared<SubscriberFoo>();
		Event<int> e1(10);
		Event<int> e2(20);
		Event<double> ed(20.2);

		TS_ASSERT_THROWS_NOTHING(e1.Subscribe(sf1.get()));

		e1.Deliver();//Should update the single subscriber (sf) to have number of activations set to 1 and last message set to 10
		TS_ASSERT_EQUALS(sf1->GetActivations(), 1);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), e1.Message());

		e2.Deliver();//Since e1 and e2 are of the same type, this should update sf again 
		TS_ASSERT_EQUALS(sf1->GetActivations(), 2);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), e2.Message());

		ed.Deliver();//ed has messages of type double, so it should refer to its own static subscriber list. It should not affect sf
		TS_ASSERT_DIFFERS(sf1->GetActivations(), 3);
		TS_ASSERT_EQUALS(sf1->GetActivations(), 2);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), e2.Message());

		e1.Unsubscribe(sf1.get());//After unsubscribing sf, it should no longer be pinged by the message deliveries from e1 and e2
		e1.Deliver();
		e2.Deliver();
		TS_ASSERT_EQUALS(sf1->GetActivations(), 2);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), e2.Message());

		//Test multiple subscribers
		e1.Subscribe(sf2.get());
		e2.Subscribe(sf1.get());
		e1.Deliver();
		e2.Deliver();
		TS_ASSERT_EQUALS(sf1->GetActivations(), 4);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), e2.Message());
		TS_ASSERT_EQUALS(sf2->GetActivations(), 2);
		TS_ASSERT_EQUALS(sf2->GetLastActivation(), e2.Message());
		
		e1.UnsubscribeAll();//Neither subscriber should be affected at this point. They should retain the values from the last deliver
		e1.Deliver();
		e2.Deliver();
		TS_ASSERT_EQUALS(sf1->GetActivations(), 4);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), e2.Message());
		TS_ASSERT_EQUALS(sf2->GetActivations(), 2);
		TS_ASSERT_EQUALS(sf2->GetLastActivation(), e2.Message());
	}

	//Test events in the event queue
	void TestEventQueue(void)
	{
		std::shared_ptr<SubscriberFoo> sf1 = std::make_shared<SubscriberFoo>();
		std::shared_ptr<SubscriberFoo> sf2 = std::make_shared<SubscriberFoo>();
		std::shared_ptr<Event<int>> e1 = std::make_shared<Event<int>>(10);
		std::shared_ptr<Event<int>> e2 = std::make_shared<Event<int>>(20);

		EventQueue q;
		GameTime time;

		//Set the subscribers
		e1->Subscribe(sf1.get());
		e1->Subscribe(sf2.get());

		//Enqueue both events

		//e1 will go off with a delay of 10
		q.Enqueue(e1, time, 10);

		//e2 will go off with a delay of 20
		q.Enqueue(e2, time, 20);

		TS_ASSERT(!q.IsEmpty());
		TS_ASSERT_EQUALS(q.Count(), 2);

		//Check the time values of the events
		TS_ASSERT_EQUALS(e1->TimeEnqueued(), time.TotalGameTime());
		TS_ASSERT_EQUALS(e1->Delay(), 10);

		TS_ASSERT_EQUALS(e2->TimeEnqueued(), time.TotalGameTime());
		TS_ASSERT_EQUALS(e2->Delay(), 20);

		//Update q with time set before either delay is passed
		//Nothing should update, and our q should remain the same
		q.Update(time);
		TS_ASSERT(!q.IsEmpty());
		TS_ASSERT_EQUALS(q.Count(), 2);

		//Update the time so that e1 goes off, but e2 doesn't
		time.SetTotalGameTime(11);
		q.Update(time);
		TS_ASSERT(!q.IsEmpty());
		TS_ASSERT_EQUALS(q.Count(), 1);
		TS_ASSERT_EQUALS(sf1->GetActivations(), 1);
		TS_ASSERT_EQUALS(sf2->GetActivations(), 1);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), 10);
		TS_ASSERT_EQUALS(sf2->GetLastActivation(), 10);

		//Set off e2 next
		time.SetTotalGameTime(21);
		q.Update(time);
		TS_ASSERT(q.IsEmpty());
		TS_ASSERT_EQUALS(sf1->GetActivations(), 2);
		TS_ASSERT_EQUALS(sf2->GetActivations(), 2);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), 20);
		TS_ASSERT_EQUALS(sf2->GetLastActivation(), 20);

		//Next, enque both of the events again and then set them off on the next tick with no delay
		q.Enqueue(e1, time);
		q.Enqueue(e2, time);
		time.SetTotalGameTime(22);
		q.Update(time);
		TS_ASSERT_EQUALS(sf1->GetActivations(), 4);
		TS_ASSERT_EQUALS(sf2->GetActivations(), 4);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), 20);
		TS_ASSERT_EQUALS(sf2->GetLastActivation(), 20);

		//Next, have the q call send. Once when the event is in our queue, and once when it isn't
		q.Enqueue(e1, time);
		q.Send(e2);
		TS_ASSERT_EQUALS(sf1->GetActivations(), 5);
		TS_ASSERT_EQUALS(sf2->GetActivations(), 5);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), 20);
		TS_ASSERT_EQUALS(sf2->GetLastActivation(), 20);

		TS_ASSERT_EQUALS(q.Count(), 1);
		q.Send(e1);
		TS_ASSERT_EQUALS(sf1->GetActivations(), 6);
		TS_ASSERT_EQUALS(sf2->GetActivations(), 6);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), 10);
		TS_ASSERT_EQUALS(sf2->GetLastActivation(), 10);
		TS_ASSERT(q.IsEmpty());

		//Clear has two cases to test
		//Clear when the items in our queue have not expired. This should simply empty the queue
		q.Enqueue(e1, time, 10);
		q.Enqueue(e2, time, 10);
		q.Clear(time);
		//Nothing should have changed in the subscribers and the queue should be empty
		TS_ASSERT_EQUALS(sf1->GetActivations(), 6);
		TS_ASSERT_EQUALS(sf2->GetActivations(), 6);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), 10);
		TS_ASSERT_EQUALS(sf2->GetLastActivation(), 10);
		TS_ASSERT(q.IsEmpty());

		//Clear when the items in our queue have expired. This should deliver them before emptying the queue
		q.Enqueue(e1, time);
		q.Enqueue(e2, time);
		time.SetTotalGameTime(50);
		q.Clear(time);
		//Nothing should have changed in the subscribers and the queue should be empty
		TS_ASSERT_EQUALS(sf1->GetActivations(), 8);
		TS_ASSERT_EQUALS(sf2->GetActivations(), 8);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), 20);
		TS_ASSERT_EQUALS(sf2->GetLastActivation(), 20);
		TS_ASSERT(q.IsEmpty());

		e1->UnsubscribeAll();

		//Make sure events with no subscribers don't do anything when they're updated in the queue
		q.Enqueue(e1, time);
		q.Enqueue(e2, time);
		time.SetTotalGameTime(60);
		q.Update(time);
		TS_ASSERT_EQUALS(sf1->GetActivations(), 8);
		TS_ASSERT_EQUALS(sf2->GetActivations(), 8);
		TS_ASSERT_EQUALS(sf1->GetLastActivation(), 20);
		TS_ASSERT_EQUALS(sf2->GetLastActivation(), 20);
		TS_ASSERT(q.IsEmpty());
	}

private:
	_CrtMemState startSnapshot;
};