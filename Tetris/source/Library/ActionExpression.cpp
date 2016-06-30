#include "pch.h"
#include "ActionExpression.h"
#include "Sector.h"
#include <sstream>

namespace Library
{
	RTTI_DEFINITIONS(ActionExpression)

	//Default constructor
	ActionExpression::ActionExpression() :
		Action(""), mLegalOperators(10), mTarget(nullptr), mExpression()
	{
		/**
		Current legal operators		
		*/
		mLegalOperators.Insert(std::pair<std::string, bool>("+", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("-", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("*", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("/", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("%", true));

		//Comparison stuff
		mLegalOperators.Insert(std::pair<std::string, bool>("==", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("!=", true));
		mLegalOperators.Insert(std::pair<std::string, bool>(">=", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("<=", true));
		mLegalOperators.Insert(std::pair<std::string, bool>(">", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("<", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("!", true));
	}

	//Constructor with a name
	ActionExpression::ActionExpression(const std::string& name) :
		Action(name), mLegalOperators(10), mTarget(nullptr), mExpression()
	{
		/**
		Current legal operators
		*/
		mLegalOperators.Insert(std::pair<std::string, bool>("+", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("-", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("*", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("/", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("%", true));

		//Comparison stuff
		mLegalOperators.Insert(std::pair<std::string, bool>("==", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("!=", true));
		mLegalOperators.Insert(std::pair<std::string, bool>(">=", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("<=", true));
		mLegalOperators.Insert(std::pair<std::string, bool>(">", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("<", true));
		mLegalOperators.Insert(std::pair<std::string, bool>("!", true));
	}

	//Destructor
	ActionExpression::~ActionExpression()
	{
	}

	//Getter for expression
	SList<std::string> ActionExpression::GetExpression()
	{
		return  mExpression;
	}

	//Setter for expression
	void ActionExpression::SetExpression(const SList<std::string>& expression)
	{
		mExpression = expression;
	}

	//Getter for target
	Datum* ActionExpression::GetTarget()
	{
		return mTarget;
	}

	//Setter for target
	void ActionExpression::SetTarget(Datum* target)
	{
		mTarget = target;
	}


	//Update simply calls our postfix calculation
	void ActionExpression::Update(const WorldState& curstate)
	{
		CalculatePostfix();
	}

	//Using our member expression, figure out what it evaluates to
	void ActionExpression::CalculatePostfix()
	{
		//Make sure we have a target
		if (mTarget == nullptr || (mTarget->GetType() != Datum::INTEGER && mTarget->GetType() != Datum::FLOAT) || mTarget->IsExternal())
		{
			return;
		}

		//Stack used with postfix calculations
		SList<std::string> stack;

		//Check each token
		//for (std::string& item : mExpression)
		for (SList<std::string>::Iterator i = mExpression.begin(); i != mExpression.end(); ++i)
		{		
			std::string item = *i;
			std::string s;
			std::string s2;

			//Check to see if the item is an operator
			if (mLegalOperators.Find(item) == mLegalOperators.end())
			{
				//Any token that is not an operator and contains characters other than 0-9 and '.' (for floats) can be treated as an item we need to find
				//Despite the fact that these characters can technically appear anywhere, we only need to check the fist character.
					//This is because we  are considering variables with non-alpha characters at the start illegal in this grammar
				//We find such items similar to how we dealt with the '.' syntax in the parser
				if (item[0] < '0' || item[0] > '9')//Compare ascii values
				{
					Datum* variable;
					//Check to see if we have a period at  all in the string
					//If not, we are referring to a variable defined above the entity containing this action in the sector scope
					if (item.find('.') == std::string::npos)
					{
						variable = Search(item);
					}
					else
					{
						//Set up a stringstream to parse the data
						std::istringstream iss(item);

						getline(iss, s, '.');
						getline(iss, s2);

						if (s == "this")
						{
							variable = GetContainer()->Search(s2);
						}
						else
						{
							Scope* curSector = GetContainer();
							while (curSector->As<Sector>() == nullptr)
							{
								curSector = curSector->GetParent();
								if (curSector == nullptr)
								{
									throw std::exception("No containing sector found");
								}
							}

							if (curSector->As<Sector>()->Entities()->Find(s) != nullptr)//Check to see if the datum we're looking for is a part of another entity in this sector
							{
								variable = curSector->As<Sector>()->Entities()->Find(s)->Get<Scope*>()->Search(s2);
							}
							else
							{
								throw std::exception("Container specified as lvalue in expression could not be found");
							}
						}

					}
					if (variable != nullptr)
					{
						//Make sure the data types are matching
						if (variable->GetType() != GetTarget()->GetType())
						{
							throw std::exception("Variable type mismatch in expression");
						}
						else
						{
							if (variable->GetType() == Datum::INTEGER)
							{
								stack.PushFront(std::to_string(variable->Get<int>()));
								continue;
							}
							else
							{
								stack.PushFront(std::to_string(variable->Get<float>()));
								continue;
							}
						}
					}
					else//If variable wasn't set at this point, something is wrong
					{
						throw std::exception("Container specified  as rvalue in expression could not be found");
					}
				}


				//Numbers constants are pushed onto the stack immediately
				stack.PushFront(item);
			}
			else//When we hit an operation, grab the top two numbers and operate with them.
			{
				//If there are not two numbers to operate with, throw an exception
				if (item != "!" && stack.Size() < 2)
				{
					throw std::exception("Bad expression: Not too few operands");
				}
				else//Otherwise evaluate the expression and push the result onto the stack
				{
					//Figure out if we're dealing with ints or floats based on the datum type
					if (mTarget->GetType() == Datum::INTEGER)
					{
						//Check not operator. Different than the rest, as it only takes on input
						if (item == "!")
						{
							int operand1 = atoi(stack.Front().c_str());
							stack.PopFront();
							if (operand1 == 0)
							{
								stack.PushFront("1");
							}
							else
							{
								stack.PushFront("0");
							}
						}
						else
						{
							int operand1 = atoi(stack.Front().c_str());
							stack.PopFront();
							int operand2 = atoi(stack.Front().c_str());
							stack.PopFront();

							if (item == "+")//Addition
							{
								stack.PushFront(std::to_string(operand2 + operand1));
							}
							else if (item == "-")//Subtraction
							{
								stack.PushFront(std::to_string(operand2 - operand1));
							}
							else if (item == "*")//Multiplication
							{
								stack.PushFront(std::to_string(operand2 * operand1));
							}
							else if (item == "/")//Division
							{
								stack.PushFront(std::to_string(operand2 / operand1));
							}
							else if (item == "%")//Mod
							{
								stack.PushFront(std::to_string(operand2 % operand1));
							}
							else if (item == "==")//Equality
							{
								stack.PushFront(std::to_string((int)(operand2 == operand1)));
							}
							else if(item == "!=")//Not equal
							{
								stack.PushFront(std::to_string((int)(operand2 != operand1)));
							}
							else if (item == ">=")///Greater than or equal
							{
								stack.PushFront(std::to_string((int)(operand2 >= operand1)));
							}
							else if (item == "<=")//Less than or equal
							{
								stack.PushFront(std::to_string((int)(operand2 <= operand1)));
							}
							else if (item == ">")//Greater than
							{
								stack.PushFront(std::to_string((int)(operand2 > operand1)));
							}
							else if (item == "<")//Less than
							{
								stack.PushFront(std::to_string((int)(operand2 < operand1)));
							}							
						}
					}
					else//Deal with  floats
					{
						//Check not operator. Different than the rest, as it only takes on input
						if (item == "!")
						{
							float operand1 = std::stof(stack.Front());
							stack.PopFront();
							if (operand1 == 0)
							{
								stack.PushFront("1");
							}
							else
							{
								stack.PushFront("0");
							}
						}
						else
						{
							float operand1 = std::stof(stack.Front());
							stack.PopFront();
							float operand2 = std::stof(stack.Front());
							stack.PopFront();

							if (item == "+")//Addition
							{
								stack.PushFront(std::to_string(operand2 + operand1));
							}
							else if (item == "-")//Subtraction
							{
								stack.PushFront(std::to_string(operand2 - operand1));
							}
							else if (item == "*")//Multiplication
							{
								stack.PushFront(std::to_string(operand2 * operand1));
							}
							else if (item == "/")//Division
							{
								stack.PushFront(std::to_string(operand2 / operand1));
							}
							else if (item == "%")//Mod
							{
								stack.PushFront(std::to_string(fmod(operand2, operand1)));
							}
							else if (item == "==")//Equality
							{
								stack.PushFront(std::to_string((int)(operand2 == operand1)));
							}
							else if (item == "!=")//Not equal
							{
								stack.PushFront(std::to_string((int)(operand2 != operand1)));
							}
							else if (item == ">=")///Greater than or equal
							{
								stack.PushFront(std::to_string((int)(operand2 >= operand1)));
							}
							else if (item == "<=")//Less than or equal
							{
								stack.PushFront(std::to_string((int)(operand2 <= operand1)));
							}
							else if (item == ">")//Greater than
							{
								stack.PushFront(std::to_string((int)(operand2 > operand1)));
							}
							else if (item == "<")//Less than
							{
								stack.PushFront(std::to_string((int)(operand2 < operand1)));
							}
						}
					}
				}
			}
		}

		//When there are no more tokens left, if there is more than one item in the stack throw exception
		if (stack.Size() > 1)
		{
			throw std::exception("Bad expression: Not too many operands");
		}

		//Otherwise, set that item to be our result
		if (mTarget->GetType() == Datum::INTEGER)//Set an int
		{
			mTarget->Set(atoi(stack.Front().c_str()));
		}
		else//Set a float
		{
			mTarget->Set(std::stof(stack.Front()));
		}
	}


}