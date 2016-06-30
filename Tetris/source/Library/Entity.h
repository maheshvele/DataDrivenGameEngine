#pragma once
#include "Action.h"
#include "Factory.h"

namespace Library
{

	class Entity : public Attributed
	{

		RTTI_DECLARATIONS(Entity, Attributed)

	public:
		/**
		Default Constructor is deleted to ensure a name is provided
		*/
		Entity();

		/**
		Constructor with a name

		@param the name to initialize with
		*/
		explicit Entity(const std::string& initialName);


		/**
		Virtual Destructor. Marked for delete to prevent use
		*/
		virtual ~Entity();

		/**
		Copy constructor

		@param rhs the entity to copy
		*/
		Entity(const Entity& rhs) = delete;

		/**
		Assignment operator. Marked for delete to prevent use

		@param rhs the entity to copy
		*/
		Entity& operator=(const Entity& rhs) = delete;

		/**
		Return a string with the name of the entity, stored by an external attribute

		@return the name attribute of this entity
		*/
		const std::string& Name() const;

		/**
		Get the address of the sector which contains this object

		@return the address of the sector which contains this object
		*/
		Scope* GetSector() const;

		/**
		Takes the address of a Sector and adopts the entity into that sector

		@param newSector the sector we want to become a part of
		*/
		virtual void SetSector(Scope* newSector);

		/**
		Get the address of our child scope that contains our actions

		@return the address of the scope that contains our actions
		*/
		Scope* Actions() const;

		/**
		Instantiate a new action of a given class name and instance name and adopt it into the action sscope

		@param className the name of the class to generate via the factory
		@param instanceName the name used to fill the 'name' field of the new item
		*/
		Scope* CreateAction(const std::string& className, const std::string& instanceName);

		/**
		Takes a WorldState reference and updates all of the actions in our action list

		@param curWorldState the current state of the world
		*/
		virtual void Update(WorldState& curWorldState);

	private:
		/**
		Store the name of the entity
		*/
		std::string mName;
	};
}