#pragma once
#include "Attributed.h"
#include "WorldState.h"
#include "Factory.h"

namespace Library
{
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed)
	public:

		/**
		Default constructor
		*/
		Action();

		/**
		Constructor with a name
		*/
		Action(const std::string& newName);

		/**
		Virtual Destructor
		*/
		virtual ~Action();

		/**
		Pure virtual function used to define behavior of derived classes

		@param curState the current worldstate to reference during update
		*/
		virtual void Update(const WorldState& curState) = 0;

		/**
		Getter for the current entity whose actionlist we are a part of

		@return the address of the scope that contains us (prescribed attribute of an entity)
		*/
		virtual Scope* GetContainer();

		/**
		Function used to adopt us into a given entity's Action list

		@param newEntity the entity we want to become a part of 
		*/
		virtual void SetEntity(Scope* newEntity);

		/**
		Getter for our current name

		@return our name value
		*/
		virtual std::string& Name();

	private:
		/**
		Member variable that stores the name of this object
		*/
		std::string mName;

	};	

	/**
	The following macro defines a concrete factory for a given concrete action
	*/
#define ConcreteActionFactory(ConcreteActionT) ConcreteFactory(Action, ConcreteActionT);
}