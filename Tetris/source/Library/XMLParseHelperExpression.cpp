#include "pch.h"
#include "XMLParseHelperExpression.h"

namespace Library
{
	//String constants
	const std::string XMLParseHelperExpression::actionString = "action";
	const std::string XMLParseHelperExpression::classString = "class";
	const std::string XMLParseHelperExpression::targetString = "target";
	const std::string XMLParseHelperExpression::nameString = "name";
	
	//Constructor
	XMLParseHelperExpression::XMLParseHelperExpression()
	{
		//Fill out our hashmap with legal operators
		mLegalOperators.Insert(std::pair<std::string, int>("+", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("-", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("*", 1));
		mLegalOperators.Insert(std::pair<std::string, int>("/", 1));
		mLegalOperators.Insert(std::pair<std::string, int>("(", 2));
		mLegalOperators.Insert(std::pair<std::string, int>(")", 2));

		//Comparison stuff
		mLegalOperators.Insert(std::pair<std::string, int>("==", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("!=", 0));
		mLegalOperators.Insert(std::pair<std::string, int>(">=", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("<=", 0));
		mLegalOperators.Insert(std::pair<std::string, int>(">", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("<", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("!", 0));
	}

	//Destructor
	XMLParseHelperExpression::~XMLParseHelperExpression()
	{
		mLegalOperators.Insert(std::pair<std::string, int>("+", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("-", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("*", 1));
		mLegalOperators.Insert(std::pair<std::string, int>("/", 1));
		mLegalOperators.Insert(std::pair<std::string, int>("(", 2));
		mLegalOperators.Insert(std::pair<std::string, int>(")", 2));

		//Comparison stuff
		mLegalOperators.Insert(std::pair<std::string, int>("==", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("!=", 0));
		mLegalOperators.Insert(std::pair<std::string, int>(">=", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("<=", 0));
		mLegalOperators.Insert(std::pair<std::string, int>(">", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("<", 0));
		mLegalOperators.Insert(std::pair<std::string, int>("!", 0));
	}

	//Handle start elements
	bool XMLParseHelperExpression::StartElementHandler(XmlParseMaster::SharedData* data, std::string name, Hashmap<std::string, std::string>& attributes)
	{
		/**
		Requirements for starting a new expression action:
		1. Shared data must be SharedDataWorld
		2. Name of element must be 'action'
		3. Must contain a 'class' attribute
		4. Must contain a 'target' attribute
		5. Must contain a 'name' attribute
		6. Class type must be 'ActionExpression'
		*/

		SharedDataWorld* reinterpereted = data->As<SharedDataWorld>();
		if (reinterpereted != nullptr && name == actionString && attributes.ContainsKey(classString) && attributes.ContainsKey(nameString))
		{
			if (attributes.Find(classString)->second == "ActionExpression")
			{
				//Ensure that we have either an actionList or an entity that is going to contain this new actionExpression
				Scope* actionList = reinterpereted->GetAction();
				Scope* entity = reinterpereted->GetEntity();
				if (actionList != nullptr && actionList->Is("ActionList"))
				{
					//Create a new actionExpression with the factory from the actionlist
					ActionExpression* newAction = actionList->As<ActionList>()->CreateAction("ActionExpression", attributes.Find(nameString)->second)->As<ActionExpression>();
					reinterpereted->SetAction(newAction);
				}
				else if (entity != nullptr)
				{
					//Create a new actionExpression with the factory from the entity
					ActionExpression* newAction = entity->As<Entity>()->CreateAction("ActionExpression", attributes.Find(nameString)->second)->As<ActionExpression>();
					reinterpereted->SetAction(newAction);
				}
				else
				{
					return false;
				}
				reinterpereted->IncrementDepth();
				return true;
			}
		}
		return false;
	}

	//Handle end elements
	bool XMLParseHelperExpression::EndElementHandler(XmlParseMaster::SharedData* data, std::string name)
	{
		/**
		To end an action expression parse we must have a current action in the shared data that was created in the start action
		*/
		SharedDataWorld* reinterpereted = data->As<SharedDataWorld>();
		Scope* curAction = reinterpereted->GetAction();
		if (reinterpereted != nullptr && name == actionString && curAction != nullptr)
		{
			if (!curAction->Is("ActionExpression"))
			{
				return false;
			}

			reinterpereted->DecrementDepth();

			Scope* curContainer = curAction->As<ActionExpression>()->GetContainer();

			//If we're in an actionList, set the current action to that
			if (curContainer->Is("ActionList"))
			{
				reinterpereted->SetAction(curContainer->As<Action>());
				return true;
			}

			//Otherwise (in the case that we're contained within an entity) just set it back to null
			reinterpereted->SetAction(nullptr);
			
			return true;
		}
		return false;
	}

	//Handle character data
	bool XMLParseHelperExpression::CharDataHandler(XmlParseMaster::SharedData* data, std::string charData, std::uint32_t length)
	{
		SharedDataWorld* reinterpereted = data->As<SharedDataWorld>();
		Scope* curAction = reinterpereted->GetAction();
		if (reinterpereted != nullptr && curAction != nullptr)
		{
			ActionExpression* ae = curAction->As<ActionExpression>();
			if (ae == nullptr)
			{
				return false;
			}

			/*
			Format for infix expressions

			lhs = operand1 operator1 operand2 operator2 ... operandN operatorN operandN+1

			*/

			//Read the char data into a string
			std::string stringData;

			for (std::uint32_t i = 0; i < length; i++)
			{
				stringData.push_back(charData[i]);
			}

			//Split the character data into tokens
			//The pieces of the expression are only seperated by whitespace
			SList<std::string> tokens;
			std::istringstream iss(stringData);
			std::string s;
			std::string s2;

			while (getline(iss, s, ' '))
			{
				tokens.PushBack(s);
			}

			//Get the table container refered to using the '.' syntax
			//If the table in question is 'this', then it is referring to a datum in the same scope as the action
			//Otherwise, we only allow for accessing other items in the same sector scope
			//If there is no '.' in the first token, we assume that the item in question is a datum declared in scope of the raw sector the entity containing this action is in
			//We check the raw sector case first

			Scope* container;

			if (tokens.Front().find('.') == std::string::npos)//Check if ther is no '.' character in the first token
			{
				if (reinterpereted->GetSector()->Find(tokens.Front()) != nullptr)//Check to see if the datum we're looking for is sitting in the raw sector
				{
					container = reinterpereted->GetSector();
					ae->SetTarget(container->Find(tokens.Front()));
				}
				else
				{
					throw std::exception("Container specified as  lvalue in expression could not be found");
				}
			}
			else
			{
				//Reset the stringtream so we can parse the before and after the '.'
				iss.str(tokens.Front());
				iss.clear();

				getline(iss, s, '.');
				getline(iss, s2);


				if (s == "this")
				{
					container = ae->GetContainer();

					//In the context of an ActionList, we need to go up the chain until we hit an entity
					/*while (container->Is("ActionList"))
					{
						container = ae->GetContainer();
					}*/
				}
				else
				{
					if (reinterpereted->GetSector()->Entities()->Find(s) != nullptr)//Check to see if the datum we're looking for is a part of another entity in this sector
					{
						container = reinterpereted->GetSector()->Entities()->Find(s)->Get<Scope*>();
					}
					else
					{
						throw std::exception("Container specified as lvalue in expression could not be found");
					}
				}


				if (container == nullptr)
				{
					throw std::exception("Container specified as lvalue in expression could not be found");
				}

				//Check that the first token refers to an lvalue that exists in the appropriate scope. Set it if it exists
				ae->SetTarget(container->Search(s2));
			}


			//If the target doesn't exist, things are bad
			if (ae->GetTarget() == nullptr)
			{
				throw std::exception("Expression target does not exist");
			}

			tokens.PopFront();

			//Check that the next token is the assignment operator "="
			if (tokens.Front() != "=")
			{
				throw std::exception("Expression missing assignment operator");
			}
			tokens.PopFront();			

			//Pass off the tokens to shunting yard
			ae->SetExpression(ShuntingYard(tokens));

			return true;
		}
		return false;
	}

	//Clone
	XMLParseHelperExpression* XMLParseHelperExpression::Clone()
	{
		return new XMLParseHelperExpression();
	}

	//Convert infix to postfix using shunting yard
	SList<std::string> XMLParseHelperExpression::ShuntingYard(const SList<std::string>& expressionTokens)
	{

		//Stack used with conversion algorithm
		SList<std::string> stack;

		//Stores return value
		SList<std::string> output;

		for (std::string& item : expressionTokens)
		{
			if (!mLegalOperators.ContainsKey(item))//If the item is not an operator, it must be a number and is there for immediately pushed onto the stack
			{
				output.PushBack(item);
			}
			else if(item == "(")//Check for open parentheses
			{
				stack.PushFront(item);
			}
			else if (item == ")")//Check for close parentheses
			{
				while (stack.Front() != "(")//Add operators to the output until we find the other parentheses
				{
					output.PushBack(stack.Front());
					stack.PopFront();
					if (stack.Size() == 0)//There's a problem if we couldn't find the other parentheses at all
					{
						throw std::exception("Expression formed with uneven number of parentheses");
					}
				}
				stack.PopFront();//Get rid of the open parentheses
			}
			else//Otherwise, we're a normal operator. 
			{
				if (stack.Size() == 0)//We go into the stack if its empty.
				{
					stack.PushFront(item);
				}
				else//Otherwise we have to compare precedence
				{
					//Make sure our operators are actually legal
					if (!mLegalOperators.ContainsKey(stack.Front()) || !mLegalOperators.ContainsKey(item))
					{
						throw std::exception("Unknown operator put into expression");
					}

					int stackPrecedence = mLegalOperators.Find(stack.Front())->second;
					int itemPrecedence = mLegalOperators.Find(item)->second;

					if (itemPrecedence > stackPrecedence)//If the new item has greater precedence, it is put onto the stack
					{
						stack.PushFront(item);
					}
					else//If the item has less precedence or the same precedence, we put the current operator into the output and then push this item into the stack
					{
						output.PushBack(stack.Front());
						stack.PushFront(item);
					}

				}
			}
		}
		//Push the remaining operators on the stack into the output
		while (stack.Size() > 0)
		{
			output.PushBack(stack.Front());
			stack.PopFront();
		}		

		return output;

	}

}