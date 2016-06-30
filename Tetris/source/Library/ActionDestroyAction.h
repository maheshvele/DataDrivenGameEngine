#pragma once
#include "Action.h"

namespace Library
{
	class ActionDestroyAction : public Action
	{
		RTTI_DECLARATIONS(ActionDestroyAction, Action)
	public:

		/**
		Default constructor
		*/
		ActionDestroyAction();

		/**
		Constructor with a name
		*/
		ActionDestroyAction(const std::string& newName);

		/**
		Virtual Destructor
		*/
		virtual ~ActionDestroyAction();

		/**
		The update function of actionDestroyAction searches for a scope with the name stored in mTargetName, orphans it, and deletes it.


		@param curState the current worldstate to reference during update
		*/
		virtual void Update(const WorldState& curState);

		/**
		Getter for our target name (the name of the action instance we plan to destroy)

		@return our instance name
		*/
		std::string GetTargetName();

		/**
		Setter for our target name (the name of the action instance we plan to destroy)

		@param newName the new instance name
		*/
		void SetTargetName(const std::string& newName);


	private:
		/**
		The name of the action that is in the same scope as this action that we wish to destroy
		*/
		//std::string mTarget;
	};
}