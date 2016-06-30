#pragma once
#include "Action.h"

namespace Library
{
	class ActionDestroyEntity final : public Action
	{
		RTTI_DECLARATIONS(ActionDestroyEntity, Action)

	public:

		/**
		*Class constructor that initializes all member variables
		*/
		ActionDestroyEntity();

		/**
		*Destructor that deallocates all memory allocated by this class
		*/
		~ActionDestroyEntity() override = default;

		/**
		*Destroys the entity this action is attached to.
		*
		*@param curState = the current worldstate to reference during update
		*@exception thrown if we do not have a valid entity parent, or if our target Entity is not set
		*/
		void Update(const Library::WorldState& curState) override;

		/**
		*Getter for the entity we want to destroy
		*
		*@return the name of our target entity
		*/
		const std::string& GetEntityName();

		/**
		*Setter for the entity we want to destroy
		*
		*@param entity = the name of our target entity
		*/
		void SetEntityName(const std::string& entity);


	private:
		std::string mEntity;
	};
}