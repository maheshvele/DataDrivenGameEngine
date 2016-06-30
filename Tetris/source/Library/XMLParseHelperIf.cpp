#include "pch.h"
#include "XMLParseHelperIf.h"

namespace Library
{
	//String constants
	const std::string XMLParseHelperIf::actionString = "action";
	const std::string XMLParseHelperIf::classString = "class";
	const std::string XMLParseHelperIf::targetString = "target";
	const std::string XMLParseHelperIf::nameString = "name";
	const std::string XMLParseHelperIf::conditionString = "condition";

	//Constructor
	XMLParseHelperIf::XMLParseHelperIf()
	{
	}

	//Destructor
	XMLParseHelperIf::~XMLParseHelperIf()
	{
	}

	//Handle start elements
	bool XMLParseHelperIf::StartElementHandler(XmlParseMaster::SharedData* data, std::string name, Hashmap<std::string, std::string>& attributes)
	{
		/**
		Requirements for starting a new expression action:
		1. Shared data must be SharedDataWorld
		2. Name of element must be 'action'
		3. Must contain a 'class' attribute
		4. Must contain a 'target' attribute
		5. Must contain a 'name' attribute
		6. Class type must be 'ActionIf'
		7. Must contain a 'condition' attribute.
		*/

		SharedDataWorld* reinterpereted = data->As<SharedDataWorld>();
		if (reinterpereted != nullptr && name == actionString && attributes.ContainsKey(classString) && attributes.ContainsKey(nameString) && attributes.ContainsKey(conditionString))
		{
			if (attributes.Find(classString)->second == "ActionIf")
			{
				//Ensure that we have either an actionList or an entity that is going to contain this new ActionIf
				Scope* actionList = reinterpereted->GetAction();
				Scope* entity = reinterpereted->GetEntity();
				if (actionList != nullptr && actionList->Is("ActionList"))
				{
					//Create a new ActionIf with the factory from the actionlist
					ActionIf* newAction = actionList->As<ActionList>()->CreateAction("ActionIf", attributes.Find(nameString)->second)->As<ActionIf>();
					reinterpereted->SetAction(newAction);
				}
				else if (entity != nullptr)
				{
					//Create a new ActionIf with the factory from the entity
					ActionIf* newAction = entity->As<Entity>()->CreateAction("ActionIf", attributes.Find(nameString)->second)->As<ActionIf>();
					reinterpereted->SetAction(newAction);
				}
				else
				{
					return false;
				}

				if (attributes.ContainsKey("type") && attributes["type"] == "variable")
				{
					(*reinterpereted->GetAction())["Condition"] = reinterpereted->GetAction()->GetContainer()->Find(attributes[conditionString])->Get<int>(0);
					(*reinterpereted->GetAction()).As<ActionIf>()->mConditionDatum = &(*reinterpereted->GetAction())["Condition"];
				}
				else
				{
					reinterpereted->GetAction()->operator[]("Condition") = std::stoi(attributes[conditionString]);
				}

				reinterpereted->IncrementDepth();
				return true;
			}
		}
		return false;
	}

	//Handle end elements
	bool XMLParseHelperIf::EndElementHandler(XmlParseMaster::SharedData* data, std::string name)
	{
		/**
		To end an action expression parse we must have a current action in the shared data that was created in the start action
		*/
		SharedDataWorld* reinterpereted = data->As<SharedDataWorld>();
		Scope* curAction = reinterpereted->GetAction();
		if (reinterpereted != nullptr && name == actionString && curAction != nullptr)
		{
			if (!curAction->Is("ActionIf"))
			{
				return false;
			}

			reinterpereted->DecrementDepth();

			Scope* curContainer = curAction->As<ActionIf>()->GetContainer();

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

	//Clone
	XMLParseHelperIf* XMLParseHelperIf::Clone()
	{
		return new XMLParseHelperIf();
	}
}