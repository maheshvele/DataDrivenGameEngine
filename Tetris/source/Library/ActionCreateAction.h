#pragma once
#include "Action.h"

namespace Library
{
	class ActionCreateAction : public Action
	{
		RTTI_DECLARATIONS(ActionCreateAction, Action)
	public:

		/**
		Default constructor
		*/
		ActionCreateAction();

		/**
		Constructor with a name
		*/
		explicit ActionCreateAction(const std::string& newName);

		/**
		Virtual Destructor
		*/
		virtual ~ActionCreateAction();

		/**
		The update function of actionCreateAction makes a new action based on a loaded
		class name (mPrototype) and instance name (mInstanceName). It then creates a new
		action using the appropriate action factory and adopts it into the same container
		that contains this actionCreateAction.

		@param curState the current worldstate to reference during update
		*/
		virtual void Update(const WorldState& curState);

		/**
		Getter for our prototype name

		@return the name of our prototype
		*/
		std::string GetPrototypeName();


		/**
		Setter for our prototype name

		@param newName the name to set our prototype name to
		*/
		void SetPrototypeName(const std::string& newName);

		/**
		Getter for our instance name (the name of the action instance we plan to create)

		@return our instance name
		*/
		std::string GetCreationName();

		/**
		Setter for our instance name (the name of the action instance we plan to create)

		@param newName the new instance name
		*/
		void SetCreationName(const std::string& newName);
	};
}