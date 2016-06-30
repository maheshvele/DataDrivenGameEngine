#include "pch.h"
#include "XMLParseHelperUniverse.h"
#include "InputManager.h"
#include "ActionPlayAudio.h"

namespace Library
{
	//String constants
	const std::string XMLParseHelperUniverse::nameString = "name";
	const std::string XMLParseHelperUniverse::entityString = "entity";
	const std::string XMLParseHelperUniverse::sectorString = "sector";
	const std::string XMLParseHelperUniverse::worldString = "world";
	const std::string XMLParseHelperUniverse::classString = "class";
	const std::string XMLParseHelperUniverse::actionString = "action";
	const std::string XMLParseHelperUniverse::targetString = "target";
	const std::string XMLParseHelperUniverse::prototypeString = "prototype";
	const std::string XMLParseHelperUniverse::creationNameString = "creationName";
	const std::string XMLParseHelperUniverse::subtypeString = "subtype";
	const std::string XMLParseHelperUniverse::fileNameString = "fileName";
	const std::string XMLParseHelperUniverse::instanceNameString = "instanceName";
	const std::string XMLParseHelperUniverse::windowString = "window";
	const std::string XMLParseHelperUniverse::windowHeightString = "height";
	const std::string XMLParseHelperUniverse::windowWidthString = "width";

	/**
	Default constructor
	*/
	XMLParseHelperUniverse::XMLParseHelperUniverse()
	{
	}


	/**
	Destructor
	*/
	XMLParseHelperUniverse::~XMLParseHelperUniverse()
	{
	}

	/**
	Sets up the helper to parse fresh data
	*/
	void XMLParseHelperUniverse::Initialize()
	{
	}

	/**
	Handle the element start with the given name in the given hashmap

	@param name the name of the element to handle
	@param attribuets the hashmap containing the element to handle
	@return true if the element was handled, false otherwise
	*/
	bool XMLParseHelperUniverse::StartElementHandler(XmlParseMaster::SharedData* data, std::string name, Hashmap<std::string, std::string>& attributes)
	{
		if (!data)
		{
			throw std::exception("Shared data is null");
		}

		//Check  out the data as our specific shared data
		SharedDataWorld* reinterpereted = data->As<SharedDataWorld>();
		if (reinterpereted != nullptr)
		{
			//The type of element we are parsing is determined by its name
			if (name == worldString)
			{
				mStateStack.PushFront(PARSING_WORLD);
			}
			else if (name == sectorString)
			{
				mStateStack.PushFront(PARSING_SECTOR);
			}
			else if (name == entityString)
			{
				mStateStack.PushFront(PARSING_ENTITY);
			}
			else if (name == actionString)
			{
				//Ensure that we're not  stealing the parseHelperExpression's work
				if (attributes.ContainsKey(classString))
				{
					if (attributes.Find(classString)->second == "ActionExpression")
					{
						return false;
					}
				}

				mStateStack.PushFront(PARSING_ACTION);
			}
			else if (name == windowString)
			{
				mStateStack.PushFront(PARSING_WINDOW);
			}
			else
			{
				return false;
			}

			if (mStateStack.Front() == PARSING_WORLD)//Set up the data if we're a world
			{
				//The world does not necessarily  need a name the way everthing else does, as only one will likely exist and it is not contained in a hashmap anywhere
				//As such we can continue without a name attribute for the world if so desired
				if (attributes.ContainsKey(nameString))
				{
					reinterpereted->GetWorld()->SetName(attributes.Find(nameString)->second);
				}
				reinterpereted->SetScope(reinterpereted->GetWorld());
				reinterpereted->IncrementDepth();
				return true;
			}
			else if (mStateStack.Front() == PARSING_SECTOR)//Set up the data if we're a sector
			{
				//We cannot parse sectors without a world. Exit if one is not set
				if (reinterpereted->GetWorld() == nullptr)
				{
					return false;
				}

				//Sectors MUST have names to be contained by the world
				if (!attributes.ContainsKey(nameString))
				{
					return false;
				}
				Sector* newSector = reinterpereted->GetWorld()->CreateSector(attributes.Find(nameString)->second)->As<Sector>();
				reinterpereted->SetSector(newSector);
				reinterpereted->SetScope(newSector);
				reinterpereted->PushName(newSector->Name());
				reinterpereted->PushIndex(0);
				reinterpereted->IncrementDepth();
				return true;
			}
			else if (mStateStack.Front() == PARSING_ENTITY)//Set up the data if we're an entity
			{
				Sector* curSector = reinterpereted->GetSector();

				//Confirm that we're a sub-entity of a sector. We cannot have entities existing in the raw world. They must be contained in sectors
				if (curSector == nullptr)
				{
					return false;
				}

				//Entities MUST have names to be contained by a sector
				if (!attributes.ContainsKey(nameString))
				{
					return false;
				}

				//Entities also MUST supply a class type that they will be instanted from via the factory interface.
				//This is set up in such a way so that we can instantiate derived classes of entity later. The base class entity should, however, also be fine to instantiate
				if (!attributes.ContainsKey(classString))
				{
					return false;
				}

				std::string className = attributes.Find(classString)->second;
				std::string instanceName = attributes.Find(nameString)->second;
				Entity* newEntity = curSector->CreateEntity(className, instanceName)->As<Entity>();
				reinterpereted->SetEntity(newEntity);
				reinterpereted->SetScope(newEntity);
				reinterpereted->PushName(newEntity->Name());
				reinterpereted->PushIndex(0);

				reinterpereted->IncrementDepth();
				return true;
			}
			else if (mStateStack.Front() == PARSING_ACTION)//Set up the data if we're an action list
			{

				//Like everything else, actions MUST be named in this system
				if (!attributes.ContainsKey(nameString))
				{
					return false;
				}

				//Like entities, actions MUST supply a class name to be used with the factory
				if (!attributes.ContainsKey(classString))
				{
					return false;
				}


				if (attributes[classString] == "ActionKeyListen")
				{
					if (attributes.ContainsKey("Player"))
					{
						InputManager::Instance()->AddKey(attributes[nameString], std::stoi(attributes["Player"]));
						reinterpereted->PushName(attributes[classString]);
						return true;
					}
					return false;
				}

				//Deal with nested actions in an action list
				Action* curAction = reinterpereted->GetAction();
				if (curAction != nullptr)
				{
					if (curAction->Is("ActionList"))
					{
						//Have actionlist create a action of the correct type instead of entity
						std::string className = attributes.Find(classString)->second;
						std::string instanceName = attributes.Find(nameString)->second;
						Action* newAction = curAction->As<ActionList>()->CreateAction(className, instanceName)->As<Action>();

						//Check to see if we need to set up a subtype for ReactionAttributed or ActionEvent
						if (newAction->Is("ReactionAttributed"))
						{
							if (!attributes.ContainsKey(subtypeString))
							{
								throw std::exception("ReactionAttributed and ActionEvent MUST have subtypes");
							}
							//ReactionAttributed objects can contain multiple subtypes to allow them to interact with multiple subtypes of ActionEvents
							//Multiple subtypes are seperated by commas in our grammar. If the subtype string contains no commas, we assume it is a single type
							//We can use an istringstream to split up the subtypes into tokens
							SList<std::string> tokens;
							std::istringstream iss(attributes.Find(subtypeString)->second);
							std::string s;

							while (getline(iss, s, ','))
							{
								tokens.PushBack(s);
							}

							int i = 0;

							for (auto& token : tokens)
							{
								newAction->As<ReactionAttributed>()->SetSubtype(token, i);
								i++;
							}
						}
						else if (newAction->Is("ActionEvent"))
						{
							if (!attributes.ContainsKey(subtypeString))
							{
								throw std::exception("ReactionAttributed and ActionEvent MUST have subtypes");
							}
							newAction->As<ActionEvent>()->SetSubtype(attributes.Find(subtypeString)->second);
						}
						else if (newAction->Is("ActionPlayAudio"))
						{
							if (!attributes.ContainsKey(fileNameString))
							{
								throw std::exception("ActionPlayMusic MUST have file name");
							}
							newAction->As<ActionPlayAudio>()->SetFileName(attributes.Find(fileNameString)->second);
						}

						reinterpereted->SetAction(newAction);
						reinterpereted->SetScope(newAction);
						reinterpereted->PushName(newAction->Name());
						reinterpereted->PushIndex(0);

						reinterpereted->IncrementDepth();
						return true;
					}
				}

				//Deal with adding actions to an entity
				Entity* curEntity = reinterpereted->GetEntity();

				//Confirm that we're an action within an entity
				if (curEntity == nullptr)
				{
					return false;
				}


				std::string className = attributes.Find(classString)->second;
				std::string instanceName = attributes.Find(nameString)->second;
				Action* newAction = curEntity->CreateAction(className, instanceName)->As<Action>();

				//Check to see if we need to set up a subtype for ReactionAttributed or ActionEvent
				if (newAction->Is("ReactionAttributed"))
				{
					if (!attributes.ContainsKey(subtypeString))
					{
						throw std::exception("ReactionAttributed and ActionEvent MUST have subtypes");
					}
					//ReactionAttributed objects can contain multiple subtypes to allow them to interact with multiple subtypes of ActionEvents
					//Multiple subtypes are seperated by commas in our grammar. If the subtype string contains no commas, we assume it is a single type
					//We can use an istringstream to split up the subtypes into tokens
					SList<std::string> tokens;
					std::istringstream iss(attributes.Find(subtypeString)->second);
					std::string s;

					while (getline(iss, s, ','))
					{
						tokens.PushBack(s);
					}

					int i = 0;

					for (auto& token : tokens)
					{
						newAction->As<ReactionAttributed>()->SetSubtype(token, i);
						i++;
					}
				}
				else if (newAction->Is("ActionEvent"))
				{
					if (!attributes.ContainsKey(subtypeString))
					{
						throw std::exception("ReactionAttributed and ActionEvent MUST have subtypes");
					}
					newAction->As<ActionEvent>()->SetSubtype(attributes.Find(subtypeString)->second);
				}
				else if (newAction->Is("ActionPlayAudio"))
				{
					if (!attributes.ContainsKey(fileNameString))
					{
						throw std::exception("ActionPlayMusic MUST have file name");
					}
					newAction->As<ActionPlayAudio>()->SetFileName(attributes.Find(fileNameString)->second);
				}

				reinterpereted->SetAction(newAction);
				reinterpereted->SetScope(newAction);
				reinterpereted->PushName(newAction->Name());
				reinterpereted->PushIndex(0);

				reinterpereted->IncrementDepth();

				//Deal with the case that we're of type ActionCreateAction
				//Attributes need a 'prototype' and 'creationName'
				ActionCreateAction* newCreation = newAction->As<ActionCreateAction>();
				if (newCreation != nullptr)
				{
					if (!attributes.ContainsKey(prototypeString) || !attributes.ContainsKey(creationNameString))
					{
						throw std::exception("CreateAction made in XML MUST contain prototype AND creationName attributes");
					}

					newCreation->SetCreationName(attributes.Find(creationNameString)->second);
					newCreation->SetPrototypeName(attributes.Find(prototypeString)->second);

				}

				//Deal with the case that we're of type ActionDestroyAction
				//Attributes need 'target'
				ActionDestroyAction* newDestruction = newAction->As<ActionDestroyAction>();
				if (newDestruction != nullptr)
				{
					if (!attributes.ContainsKey(targetString))
					{
						throw std::exception("DestroyAction made in XML MUST contain a target attribute");
					}
					newDestruction->SetTargetName(attributes.Find(targetString)->second);
				}

				//Deal with the case that we're of type ActionCreateEntity
				//Attributes need 'instanceName'
				ActionCreateEntity* newEntityCreator = newAction->As<ActionCreateEntity>();
				if (newEntityCreator != nullptr)
				{
					if (!attributes.ContainsKey(instanceNameString))
					{
						throw std::exception("Entity ereation action made in XML MUST contain an instanceName attribute");
					}
					newEntityCreator->SetInstanceName(attributes.Find("instanceName")->second);
				}

				//Deal with the case that we're of type ActionAdopt
				//Attributes need 'target'
				ActionAdopt* newAdopt = newAction->As<ActionAdopt>();
				if (newAdopt != nullptr)
				{
					if (!attributes.ContainsKey(targetString))
					{
						throw std::exception("ActionAdopt made in XML MUST contain a target attribute");
					}
					newAdopt->SetTargetSector(attributes.Find(targetString)->second);
				}

				return true;

			}
			else if (mStateStack.Front() == PARSING_WINDOW)
			{
				if (!attributes.ContainsKey(windowHeightString) || !attributes.ContainsKey(windowWidthString) || !attributes.ContainsKey(nameString))
				{
					throw std::exception("Windows made in XML MUST contain a height, a width and a name");
				}

				std::string heightString = attributes.Find(windowHeightString)->second;
				std::string widthString = attributes.Find(windowWidthString)->second;
				std::string name = attributes.Find(nameString)->second;
				std::float_t height = std::stof(heightString.c_str());
				std::float_t width = std::stof(widthString.c_str());
				reinterpereted->GetWorld()->CreateRenderWindow(static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height), name);
				return true;
			}

		}
		return false;
	}

	/**
	Handle the element end with the given name in the given hashmap

	@param name the name of the element to handle
	@return true if the element was handled, false otherwise
	*/
	bool XMLParseHelperUniverse::EndElementHandler(XmlParseMaster::SharedData* data, std::string name)
	{
		if (!data)
		{
			throw std::exception("Shared data is null");
		}

		//Check  out the data as our specific shared data
		SharedDataWorld* reinterpereted = data->As<SharedDataWorld>();

		//Used later to cache the current action list if we're working with nested actions in an actionList
		ActionList* containerList;

		if (reinterpereted != nullptr)
		{
			switch (mStateStack.Front())
			{
			case PARSING_WORLD:
				if (name != worldString)
				{
					return false;
				}
				mStateStack.PopFront();
				reinterpereted->DecrementDepth();
				reinterpereted->SetWorld(nullptr);
				reinterpereted->SetScope(nullptr);
				return true;
				break;
			case PARSING_SECTOR:
				if (name != sectorString)
				{
					return false;
				}
				mStateStack.PopFront();
				reinterpereted->DecrementDepth();
				reinterpereted->SetSector(nullptr);
				reinterpereted->SetScope(nullptr);
				reinterpereted->PopName();
				reinterpereted->PopIndex();
				return true;
				break;
			case PARSING_ENTITY:
				if (name != entityString)
				{
					return false;
				}
				mStateStack.PopFront();
				reinterpereted->DecrementDepth();
				reinterpereted->SetEntity(nullptr);
				reinterpereted->SetScope(nullptr);
				reinterpereted->PopName();
				reinterpereted->PopIndex();
				return true;
				break;
			case PARSING_ACTION:

				if (reinterpereted->PeekName() == "ActionKeyListen")
				{
					mStateStack.PopFront();
					reinterpereted->PopName();
					return true;
				}

				//Ensure that we're not stealing the parseHelperExpression's work
				if (reinterpereted->GetAction()->Is("ActionExpression"))
				{
					return false;
				}

				if (name != actionString)
				{
					return false;
				}

				mStateStack.PopFront();
				reinterpereted->DecrementDepth();

				//Account for actions nested in actionlists
				containerList = reinterpereted->GetAction()->GetContainer()->As<ActionList>();
				if (containerList != nullptr)
				{
					reinterpereted->SetAction(containerList);
					reinterpereted->SetScope(nullptr);
					reinterpereted->PopName();
					reinterpereted->PopIndex();
					break;
				}

				//Account for actions contained in entities
				reinterpereted->SetAction(nullptr);
				reinterpereted->SetScope(nullptr);
				reinterpereted->PopName();
				reinterpereted->PopIndex();
				return true;
				break;
			default:
				break;
			}
		}
		return false;
	}

	/**
	Given a string buffer of character data and an integer length, attempt to handle the character data

	@param data the string data to be handled
	@param length the number of characters in data
	@return true if the elemnt was handled, false otherwise
	*/
	bool XMLParseHelperUniverse::CharDataHandler(XmlParseMaster::SharedData* data, std::string charData, std::uint32_t length)
	{
		if (!data)
		{
			throw std::exception("Shared data is null");
		}

		//Check  out the data as our specific shared data
		SharedDataWorld* reinterpereted = data->As<SharedDataWorld>();
		if (reinterpereted != nullptr)
		{
			//At the moment, we don't want to handle any char data. This may change in the future, but for now this should be filled out via our table parser
		}
		return false;
	}


	XMLParseHelperUniverse* XMLParseHelperUniverse::Clone()
	{
		return new XMLParseHelperUniverse();
	}

}