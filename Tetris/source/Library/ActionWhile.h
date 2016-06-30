#pragma once
#include "ActionList.h"
#include "ActionExpression.h"

namespace Library
{
	class ActionWhile final : public ActionList
	{
		RTTI_DECLARATIONS(ActionWhile, ActionList)

	public:
		/**
		Constructor with a name; without a name,
		behaves like default constructor with
		name of empty string.

		@param name the name to initialize with
		*/
		ActionWhile(const std::string& name = "");

		/**
		Destructor
		*/
		~ActionWhile() = default;

		/**
		Update function calls our calculate function on our expression

		@param curState the current state of the world
		*/
		void Update(const WorldState& curstate) override;

		Datum* mConditionDatum;

	private:
		ActionWhile(const ActionWhile& rhs) = delete;
		ActionWhile& operator=(const ActionWhile& rhs) = delete;

		ActionExpression* mActionExpression;
	};
}