#include "pch.h"
#include "EventMessageAttributed.h"

namespace Library
{
	//Default constructor
	EventMessageAttributed::EventMessageAttributed() :
		Attributed(DEFAULT_SIZE), mSubtype(""), mWorld()
	{
		//Prescribed attribute for arguments list
		InternalAttribute(Arguments, 1, Datum::TABLE, nullptr)
		Populate();
	}

	//Destructor
	EventMessageAttributed::~EventMessageAttributed()
	{
	}

	//Getter for subtype
	const std::string& EventMessageAttributed::GetSubtype() const
	{
		return mSubtype;
	}

	//Setter for subtype
	void EventMessageAttributed::SetSubtype(const std::string& type)
	{
		mSubtype = type;
	}

	//Getter for world
	World* EventMessageAttributed::GetWorld() const
	{
		return mWorld;
	}
	
	//Setter for world
	void EventMessageAttributed::SetWorld(World* world)
	{
		mWorld = world;
	}

	//Getter for arguments (const)
	Scope* EventMessageAttributed::GetArguments() const
	{
		return Find("Arguments")->Get<Scope*>();
	}

}