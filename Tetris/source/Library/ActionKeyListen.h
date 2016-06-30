#pragma once
#include "Action.h"

namespace Library
{
	class ActionKeyListen : public Action
	{
		RTTI_DECLARATIONS(ActionKeyListen, Action)

	public:

		/**
		*Class constructor that initializes all member variables
		*/
		ActionKeyListen();

		/**
		*Destructor that deallocates all memory allocated by this class
		*/
		~ActionKeyListen() override = default;

		/**
		*Adds a key to the input manager
		*
		*@param curState the current worldstate to reference during update
		*@exception thrown if the user does not specify a Key prescribed attribute
		*/
		void Update(const Library::WorldState& curState) override;

		/**
		*Getter for our key name
		*
		*@return the name of our key
		*/
		const std::string& GetKey();

		/**
		*Setter for our key name
		*
		*@param key =  the name to set our key name to
		*/
		void SetKey(const std::string& key);


	private:
		std::string mKey;

	};

}