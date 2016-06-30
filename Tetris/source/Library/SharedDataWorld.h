#pragma once
#include "World.h"
#include "XMLParseHelperTable.h"

namespace Library
{
	class SharedDataWorld : public XMLParseHelperTable::SharedDataScope
	{
		RTTI_DECLARATIONS(SharedDataWorld, XMLParseHelperTable::SharedDataScope);
	public:
		/**
		Constructor
		*/
		SharedDataWorld();

		/**
		Constructor

		@param initialWorld the address of the World to be filled out
		*/
		SharedDataWorld(World* initialWorld);

		/**
		Denstructor
		*/
		~SharedDataWorld();

		/**
		Virtual clone function. Allocates new memory on the heap that must be deleted.

		@return a newly allocated SharedDataWorld which includes a newly allocated copy of the current World.
		*/
		virtual SharedDataWorld* Clone();

		/**
		Get the World that is currently being used

		@return the address to the current World
		*/
		World* GetWorld();

		/**
		Set the value of the current World

		@param newAddress the address of the World to be used
		*/
		void SetWorld(World* newAddress);

		/**
		Get the current sector we're parsing

		@return the address to the current sector we're parsing
		*/
		Sector* GetSector();

		/**
		Set the current sector we're parsing

		@param newSector the current sector we're parsing
		*/
		void SetSector(Scope* newSector);

		/**
		Get the current entity we're parsing

		@return the address to the current entity we're parsing
		*/
		Entity* GetEntity();

		/**
		Set the current entity we're parsing

		@param newEntity the entity we're parsing
		*/
		void SetEntity(Scope* newEntity);

		/**
		Get the current action that we're parsing

		@return the address of the current action we're parsing
		*/
		Action* GetAction();

		/**
		Set the current action we're parsing

		@param newAction the action we're parsing
		*/
		void SetAction(Action* newAction);

	private:
		/**
		World where data is stored
		*/
		World* mWorld;

		/**
		The address of the current sector we're working in
		*/
		Sector* mCurSector;

		/**
		The address of the current entity we're working in
		*/
		Entity* mCurEntity;

		/**
		The address of the current action we're working in
		*/
		Action* mCurAction;

		/**
		Flag set to confirm that data has been created from a clone
		*/
		bool mIsClone;
	};
}

/*



*/