#pragma once
#include "Attributed.h"
#include "WorldState.h"
#include "Entity.h"
#include "Factory.h"

namespace Library
{
	class Sector : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)

	public:
		/**
		Default constructor is delted to ensure a name is provided
		*/
		Sector();

		/**
		Constructor with a name

		@param the name to initialize with
		*/
		explicit Sector(const std::string& initialName);

		/**
		Disallow copies of sectors
		*/
		Sector(const Sector& rhs) = delete;

		/**
		Disallow copies of sectors
		*/
		Sector& operator=(const Sector& rhs) = delete;

		/**
		Destructor
		*/
		virtual ~Sector();

		/**
		Return a string with the name of the sector

		@return a string with the name of the sector
		*/
		const std::string& Name() const;

		/**
		Get the Scope* that stores the entities contained in the sector

		@return the address of the scope that contains the entities in the sector
		*/
		Scope* Entities() const;

		/**
		Take an entity class name and its instance name, and uses the entity factory to make a new object of the given type
		Then adopts the entity into the sector (using Entity::SetSector) and returns the address of the new entity

		@param className the name of the class to create a new version of via the factory
		@param instanceName the name of the instance to create a new version of via the factory
		@return the addresss of the new entity
		*/
		Scope* CreateEntity(const std::string& className, const std::string& instanceName) const;

		/**
		Take the address of a world object and adopt the sector within that cotainer

		@newWorld the address of the world to adopt ourselves into
		*/
		void SetWorld(Scope* newWorld);

		/**
		Get the address of the current world that was assigned via SetWorld

		@return the address of the current world that was assigned via setworld
		*/
		Scope* GetWorld() const;

		/**
		Take a WorldState referenfce and call an update on contained entities based on that

		@param curState the current state of the world
		*/
		virtual void Update(WorldState& curState);

	private:
		/**
		Store the name of the sector
		*/
		std::string mName;
	};
}