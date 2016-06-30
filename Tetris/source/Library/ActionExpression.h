#pragma once
#include "Action.h"

namespace Library
{
	class ActionExpression : public Action
	{
		RTTI_DECLARATIONS(ActionExpression, Action)

	public :
		/**
		Default constructor
		*/
		ActionExpression();

		/**
		Destructor
		*/
		~ActionExpression();

		/**
		Constructor with a name

		@param name the name to initialize with
		*/
		ActionExpression(const std::string& name);

		/**
		Constructor with a name and a target name

		@param name the name to initialize with
		@param target scope with contains the lvalue our expression is assigned to
		*/
		//ActionExpression(const std::string& name, Scope* target);

		/**
		Getter for our expression

		@return the string value that we're going to evaulate
		*/
		SList<std::string> GetExpression();

		/**
		Setter for our expression

		@param the new expression for us to hold
		*/
		void SetExpression(const SList<std::string>& expression);

		/**
		Getter for target

		@return the current target address
		*/
		Datum* GetTarget();

		/**
		Setter for target

		@param the address of the new target
		*/
		void SetTarget(Datum* target);

		/**
		Update function calls our calculate function on our expression

		@param curState the current state of the world
		*/
		void Update(const WorldState& curstate) override;


	private:

		/**
		Function that claculates expressions that are in postfix format. Result is stored in our target.
		*/
		void CalculatePostfix();

		/**
		Hashmap of legal operators
		*/
		Hashmap<std::string, bool> mLegalOperators;

		/**
		The string which holds the expression we're going to evaluate
		*/
		SList<std::string> mExpression;

		/**
		Datum to fill out with result
		*/
		Datum* mTarget;
	};

}