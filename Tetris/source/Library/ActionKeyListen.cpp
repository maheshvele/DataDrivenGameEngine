#include "pch.h"
#include "ActionKeyListen.h"
#include "InputManager.h"

using namespace Library;

namespace Library
{
	RTTI_DEFINITIONS(ActionKeyListen)

	/**
	*Class constructor that initializes all member variables
	*/
	ActionKeyListen::ActionKeyListen() : Action(""), mKey()
	{
		ExternalAttribute(Key, Datum::STRING, 1, &mKey);
		Populate();
	}

	/**
	*Adds a key to the input manager
	*
	*@param curState the current worldstate to reference during update
	*@exception thrown if the user does not specify a Key prescribed attribute
	*/
	void ActionKeyListen::Update(const WorldState& curState)
	{
		if (mKey == "")
		{
			throw std::exception("Key datum must be initialized in XML!");
		}

		InputManager::Instance()->AddKey(mKey, 1);
	}

	/**
	*Getter for our prototype name
	*
	*@return the name of our prototype
	*/
	const std::string& ActionKeyListen::GetKey()
	{
		return mKey;
	}

	/**
	*Setter for our prototype name
	*
	*@param newName the name to set our prototype name to
	*/
	void ActionKeyListen::SetKey(const std::string& key)
	{
		mKey = key;
	}

}