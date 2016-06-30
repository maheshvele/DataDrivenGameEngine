#pragma once
#include "Action.h"

namespace Library
{
	class ActionList : public Action
	{

		RTTI_DECLARATIONS(ActionList, Action)

	public:

		/**
		Default constructor
		*/
		ActionList();

		/**
		Constructor with name

		@param the initial name
		*/
		ActionList(const std::string& newName);

		/**
		Get the scope containing our internal actions

		@return the scope containing our actions
		*/
		Scope* Actions();

		/**
		Destructor
		*/
		virtual ~ActionList();

		/**
		Instantiate a new action of a given class name and instance name and adopt it into our actions subscope.
		Used to create internal sub-actions during parsing

		@param className the name of the class to generate via the factory
		@param instanceName the name used to fill the 'name' field of the new item
		*/
		Scope* CreateAction(const std::string& className, const std::string& instancename);

		/**
		Invokes the update method for each action contained within this object

		@param curState the current worldstate to reference during update
		*/
		virtual void Update(const WorldState& curState);
	};
}