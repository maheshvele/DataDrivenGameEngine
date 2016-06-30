#include "pch.h"
#include "Reaction.h"

namespace Library
{
	RTTI_DEFINITIONS(Reaction)

	//Default constructor
	Reaction::Reaction() :
		ActionList()
	{
	}

	//Constructor with a name
	Reaction::Reaction(const std::string& name) :
		ActionList(name)
	{
	}

	//Destructor
	Reaction::~Reaction()
	{
	}

	//Empty update
	void Reaction::Update(const WorldState& curState)
	{
	}
}