#include "pch.h"
#include "ReactionAttributed.h"
#include "World.h"

namespace Library
{
	RTTI_DEFINITIONS(ReactionAttributed)

	//Default constructor
	ReactionAttributed::ReactionAttributed() :
		Reaction()
	{
		//Prescribed attribute for subtype
		InternalAttribute(Subtype, 1, Datum::STRING, nullptr)

		//Prescribed attribute for args
		InternalAttribute(Arguments, 1, Datum::TABLE, nullptr)

		Populate();

		//Subscribe to the appropriate event type
		Event<EventMessageAttributed>::Subscribe(this);
	}

	//Constructor with name
	ReactionAttributed::ReactionAttributed(const std::string& name) :
		Reaction(name)
	{
		//Prescribed attribute for subtype
		InternalAttribute(Subtype, 1, Datum::STRING, nullptr)

		//Prescribed attribute for args
		InternalAttribute(Arguments, 1, Datum::TABLE, nullptr)

		Populate();

		//Subscribe to the appropriate event type
		Event<EventMessageAttributed>::Subscribe(this);
	}

	//Constructor with both name and type
	ReactionAttributed::ReactionAttributed(const std::string& name, std::string* type) :
		Reaction(name)
	{
		//Prescribed attribute for subtype
		InternalAttribute(Subtype, 1, Datum::STRING, type)

		//Prescribed attribute for args
		InternalAttribute(Arguments, 1, Datum::TABLE, nullptr)

		Populate();

		//Subscribe to the appropriate event type
		Event<EventMessageAttributed>::Subscribe(this);
	}

	//Constructor with a name and multiple subtypes
	ReactionAttributed::ReactionAttributed(const std::string& name, std::string** types, std::uint32_t size) :
		Reaction(name)
	{
		//Prescribed attribute for subtype
		InternalAttribute(Subtype, size, Datum::STRING, types)

		//Prescribed attribute for args
		InternalAttribute(Arguments, 1, Datum::TABLE, nullptr)

		Populate();

		//Subscribe to the appropriate event type
		Event<EventMessageAttributed>::Subscribe(this);
	}

	//Destructor
	ReactionAttributed::~ReactionAttributed()
	{
		//Unubscribe to the appropriate event type
		Event<EventMessageAttributed>::Unsubscribe(this);
	}

	//What to do when we get pinged by an event
	void ReactionAttributed::Notify(EventPublisher* publisher)
	{
		Event<EventMessageAttributed>* e = publisher->As<Event<EventMessageAttributed>>();
		if (e != nullptr)
		{
			Datum* subtypes = Find("Subtype");
			const std::string messageType = e->Message().GetSubtype();
			for (std::uint32_t i = 0; i < subtypes->Size(); i++)
			{
				//Check to see if the message is of the correct type
				if (subtypes->Get<std::string>(i) == messageType)
				{
					//Copy the arguments scope
					*(Find("Arguments")->Get<Scope*>()) = *((e->Message().Find("Arguments"))->Get<Scope*>());

					//Execute our actions
					ActionList::Update(e->Message().GetWorld()->GetWorldState());
					return;
				}
			}
		}
	}

	//Getter for one of our subtypes
	const std::string& ReactionAttributed::GetSubtype(std::uint32_t index) const
	{
		Datum* subtypes = Find("Subtype");

		//Ensure that we don't access an out of bounds index
		if (index > subtypes->Size())
		{
			throw std::exception("Attempt to access ReactionAttributed subtype out of bounds");
		}

		return Find("Subtype")->Get<std::string>(index);
	}

	//Add new subtypes
	void ReactionAttributed::AddSubtype(const std::string& type)
	{
		Datum* subtypes = Find("Subtype");
		subtypes->Set(type, subtypes->Size());
	}

	//Setter for subtype
	void ReactionAttributed::SetSubtype(const std::string& type, std::uint32_t index)
	{
		Datum* subtypes = Find("Subtype");
		subtypes->Set(type, index);
	}

}