#include "pch.h"
#include "ActionEvent.h"
#include "World.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionEvent)

	//Deffault constructor
	ActionEvent::ActionEvent() :
		Action()
	{
		//Prescribed attribute for subtype
		InternalAttribute(Subtype, 1, Datum::STRING, nullptr)

		//Prescribed attribute for subtype
		InternalAttribute(Delay, 1, Datum::FLOAT, nullptr)

		//Prescribed attribute for args
		InternalAttribute(Arguments, 1, Datum::TABLE, nullptr)

		Populate();
	}

	//Name constructor
	ActionEvent::ActionEvent(const std::string& name) :
		Action(name)
	{
		//Prescribed attribute for subtype
		InternalAttribute(Subtype, 1, Datum::STRING, nullptr)

		//Prescribed attribute for subtype
		InternalAttribute(Delay, 1, Datum::FLOAT, nullptr)

		//Prescribed attribute for args
		InternalAttribute(Arguments, 1, Datum::TABLE, nullptr)
		Populate();
	}

	//Name and type constructor
	ActionEvent::ActionEvent(const std::string& name, std::string* type) :
		Action(name)
	{
		//Prescribed attribute for subtype
		InternalAttribute(Subtype, 1, Datum::STRING, type)

		//Prescribed attribute for subtype
		InternalAttribute(Delay, 1, Datum::FLOAT, nullptr)

		//Prescribed attribute for args
		InternalAttribute(Arguments, 1, Datum::TABLE, nullptr)
		Populate();
	}

	//Name and many types constructor
	ActionEvent::ActionEvent(const std::string& name, std::string* types, std::uint32_t num) :
		Action(name)
	{
		//Prescribed attribute for subtype
		InternalAttribute(Subtype, num, Datum::STRING, types)

		//Prescribed attribute for subtype
		InternalAttribute(Delay, 1, Datum::FLOAT, nullptr)

		//Prescribed attribute for args
		InternalAttribute(Arguments, 1, Datum::TABLE, nullptr)
		Populate();
	}

	//Destructor
	ActionEvent::~ActionEvent()
	{
	}

	//Create event w/attributed message and enqueue it in our update
	void ActionEvent::Update(const WorldState& curState)
	{
		//Cache the current world
		World* cachedWorld = curState.GetWorld();

		//Ensure that we have the queue set at this point. If not, grab it from the world
		if (mCurQueue == nullptr)
		{
			mCurQueue = cachedWorld->GetQueue();
		}

		//Create message (subtype / args)
		EventMessageAttributed message;

		//Fill out message
		message.SetSubtype(GetSubtype());
		message.SetWorld(cachedWorld);
	
		//Copy the arguments
		*(message.Find("Arguments")->Get<Scope*>()) = *(Find("Arguments")->Get<Scope*>());

		//Create event
		std::shared_ptr<Event<EventMessageAttributed>> event = std::make_shared<Event<EventMessageAttributed>>(message);

		//Enqueue the event
		mCurQueue->Enqueue(event, curState.GetGameTime(), GetDelay());
	}

	//Getter for current subtype
	const std::string& ActionEvent::GetSubtype(std::uint32_t index) const
	{
		Datum* subtypes = Find("Subtype");

		//Ensure that we don't access an out of bounds index
		if (index > subtypes->Size())
		{
			throw std::exception("Attempt to access ActionEvent subtype out of bounds");
		}

		return subtypes->Get<std::string>(index);
	}

	//Getter for  delay
	float ActionEvent::GetDelay() const
	{
		return Find("Delay")->Get<float>();
	}

	//Setter for delay
	void ActionEvent::SetDelay(const float& delay)
	{
		(*this)["Delay"].Set(delay);
	}

	//Getter for queue
	EventQueue* ActionEvent::GetQueue() const
	{
		return mCurQueue;
	}

	//Setter for queue
	void ActionEvent::SetQueue(EventQueue* queue)
	{
		mCurQueue = queue;
	}

	//Add a new argument to the arguments list
	void ActionEvent::AddArgument(const Datum& arg, const std::string& name)
	{
		Datum& newArg = GetArguments()->Append(name);		
		newArg = arg;
	}

	//Getter for args
	Scope* ActionEvent::GetArguments()
	{
		return Find("Arguments")->Get<Scope*>();
	}

	//Setter for subtype
	void ActionEvent::SetSubtype(const std::string& type, std::uint32_t index)
	{
		Datum* subtypes = Find("Subtype");
		subtypes->Set(type, index);
	}

}