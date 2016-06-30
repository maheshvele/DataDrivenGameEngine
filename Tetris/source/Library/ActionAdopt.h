#pragma once
#include "Action.h"
#include "Sector.h"

namespace Library
{
	class ActionAdopt : public Action
	{
		RTTI_DECLARATIONS(ActionAdopt, Action)
	public:
		/**
		Default constructor
		*/
		ActionAdopt();

		/**
		Named cosntructor
		*/
		ActionAdopt(const std::string& name);

		/**
		Destructor
		*/
		~ActionAdopt();

		/**
		The update function of ActionAdopt calls the setSector method of
		the entity that contains this action on the provided target sector.
		This should produce the behavior of orphaning the entity and moving it
		into a new sector

		@param curState the current worldstate to reference during update
		*/
		virtual void Update(const WorldState& curState);

		/**
		Getter for the target sector that we're going to be adopted into
		*/
		std::string GetTargetSector() const;

		/**
		Setter for the sector that we're going to be adopted into
		*/
		void SetTargetSector(const std::string& string);

	};
}