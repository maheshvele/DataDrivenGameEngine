#pragma once
#include "Action.h"
#include "Sector.h"

namespace Library
{
	class ActionCreateEntity : public Action
	{
		RTTI_DECLARATIONS(ActionCreateEntity, Action)
	public:
		/**
		Default constructor
		*/
		ActionCreateEntity();

		/**
		Named constructor
		*/
		ActionCreateEntity(const std::string& name);

		/**
		Destructor
		*/
		~ActionCreateEntity();

		/**
		The update function of ActionCreateEntity serves to create a new entity.
		It uses the CreateEntity funciton of the sector that currently contains it
		to create a new entity with the correct InstanceName. If no className is provided,
		it defaults to using the vanilla entity class.

		@param curState the current worldstate to reference during update
		*/
		virtual void Update(const WorldState& curState);

		/**
		Getter for our class name

		@return the name of our prototype
		*/
		std::string GetClass();


		/**
		Setter for our name

		@param newName the name to set our prototype name to
		*/
		void SetClass(const std::string& name);

		/**
		Getter for our instance name (the name of the action instance we plan to create)

		@return our instance name
		*/
		std::string GetInstanceName();

		/**
		Setter for our instance name (the name of the action instance we plan to create)

		@param newName the new instance name
		*/
		void SetInstanceName(const std::string& name);


	private:
		/**
		The classname to be provided to the factory
		*/
		std::string mClassName;

		/**
		The instance name to be provided to the factory
		*/
		std::string mInstanceName;

	};
}