#pragma once
#include "ActionList.h"

namespace Library
{
	class ActionIf final : public ActionList
	{
		RTTI_DECLARATIONS(ActionIf, ActionList)

	public:
		/**
		Constructor with a name; without a name,
		behaves like default constructor with
		name of empty string.

		@param name the name to initialize with
		*/
		ActionIf(const std::string& name = "");

		/**
		Destructor
		*/
		~ActionIf() = default;

		/**
		Update function calls our calculate function on our expression

		@param curState the current state of the world
		*/
		void Update(const WorldState& curstate) override;

		Datum* mConditionDatum;

	private:
		ActionIf(const ActionIf& rhs) = delete;
		ActionIf& operator=(const ActionIf& rhs) = delete;
	};

}