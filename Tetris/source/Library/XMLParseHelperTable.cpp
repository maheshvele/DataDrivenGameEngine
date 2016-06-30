#include "pch.h"
#include "XMLParseHelperTable.h"

namespace Library
{

#pragma region SharedData

	RTTI_DEFINITIONS(XMLParseHelperTable::SharedDataScope);

	//Default constructor
	XMLParseHelperTable::SharedDataScope::SharedDataScope() :
		mScope(nullptr), mIsClone(false)
	{
	}

	//Constructor with a defined initial scope
	XMLParseHelperTable::SharedDataScope::SharedDataScope(Scope* initialScope) :
		mScope(initialScope), mIsClone(false)
	{
	}

	//Default destructor
	XMLParseHelperTable::SharedDataScope::~SharedDataScope()
	{
		if (mIsClone)
		{
			delete mScope;
		}
	}

	//Clone (Virtual constructor)
	XMLParseHelperTable::SharedDataScope* XMLParseHelperTable::SharedDataScope::Clone()
	{
		SharedDataScope* returnVal = new SharedDataScope();
		returnVal->mIsClone = true;
		Scope* returnScope = new Scope(*mScope);
		returnVal->mScope = returnScope;
		return returnVal;
	}

	/*
	Getter and setter for scope
	*/

	Scope& XMLParseHelperTable::SharedDataScope::GetScope()
	{
		return *mScope;
	}

	void XMLParseHelperTable::SharedDataScope::SetScope(Scope* newAddress)
	{
		mScope = newAddress;
	}

	/*
	Push and pop for name and index stack
	*/
	void XMLParseHelperTable::SharedDataScope::PushName(const std::string& name)
	{
		mNameStack.PushFront(name);
	}

	void XMLParseHelperTable::SharedDataScope::PopName()
	{
		mNameStack.PopFront();
	}

	void XMLParseHelperTable::SharedDataScope::PushIndex(std::uint32_t index)
	{
		mIndexStack.PushFront(index);
	}

	void XMLParseHelperTable::SharedDataScope::PopIndex()
	{
		mIndexStack.PopFront();
	}

	/**
	Peek functions to check the current front of the two stacks
	*/

	std::string XMLParseHelperTable::SharedDataScope::PeekName()
	{
		return mNameStack.Front();
	}

	std::uint32_t XMLParseHelperTable::SharedDataScope::PeekIndex()
	{
		return mIndexStack.Front();
	}


#pragma endregion

	//String constants
	const std::string XMLParseHelperTable::nameString = "name";
	const std::string XMLParseHelperTable::indexString = "index";
	const std::string XMLParseHelperTable::tableString = "table";
	const std::string XMLParseHelperTable::integerString = "integer";
	const std::string XMLParseHelperTable::floatString = "float";
	const std::string XMLParseHelperTable::vectorString = "vector";
	const std::string XMLParseHelperTable::matrixString = "matrix";
	const std::string XMLParseHelperTable::stringString = "string";

	XMLParseHelperTable::XMLParseHelperTable()
	{
		Initialize();
	}

	XMLParseHelperTable::~XMLParseHelperTable() 
	{
		Initialize();
	}

	//Set the helper up for a fresh parse
	void XMLParseHelperTable::Initialize()
	{
		mStateStack.Clear();
		mInsertionStack.Clear();
	}

	//Handler functions	
	/*
	Format:
		<table><element name="string">value</element></table>
		elements are of the following types
			integer
			float
			string
			vector
			matrix
		each element MUST have a name attribute that we use for creating the name/datum pair used in the scope
	*/

	//Handles start elements
	bool XMLParseHelperTable::StartElementHandler(XmlParseMaster::SharedData* data, std::string name, Hashmap<std::string, std::string>& attributes)
	{
		if (!data)
		{
			throw std::exception("Shared data is null");
		}

		if (data->Is("SharedDataScope"))
		{

			//Reinterperet the shared data
			SharedDataScope* reinterpereted = data->As<SharedDataScope>();

			//Figure out the type of the current element and push the appropriate state onto the state stack
			if (name == tableString)
			{
				mStateStack.PushFront(PARSING_TABLE);
			}
			else if (name == integerString)
			{
				mStateStack.PushFront(PARSING_INTEGER);
			}
			else if (name == floatString)
			{
				mStateStack.PushFront(PARSING_FLOAT);
			}
			else if (name == vectorString)
			{
				mStateStack.PushFront(PARSING_VECTOR);
			}
			else if (name == matrixString)
			{
				mStateStack.PushFront(PARSING_MATRIX);
			}
			else if (name == stringString)
			{
				mStateStack.PushFront(PARSING_STRING);
			}
			else//In this case, it is not a data type that we handle
			{
				return false;
			}

			//If we're not at the base element, we need to set up the element for use by the char data handler
			if (reinterpereted->Depth() > 0)
			{
				//Nested elements are required to have a name. We don't handle anything that does not
				if (!attributes.ContainsKey(nameString))
				{
					return false;
				}
				else
				{
					reinterpereted->PushName(attributes.Find(nameString)->second);					
				}

				//Optionally non table elements can also have an insertion index. If this is not provided, it defaults to zero
				if (!attributes.ContainsKey(indexString))
				{
					reinterpereted->PushIndex(0);					
				}
				else
				{
					reinterpereted->PushIndex(atoi(attributes.Find(indexString)->second.c_str()));
				}


				if (name != tableString)//Deal with normal elements
				{
					//Seperate block for if current scope is an action event, as we will Append a datum in the arguments list instead of the raw scope
					if (reinterpereted->GetScope().Is("ActionEvent"))
					{
						Scope* argScope = reinterpereted->GetScope().As<ActionEvent>()->GetArguments();
						argScope->Append(reinterpereted->PeekName());
					}	
					else
					{
						reinterpereted->GetScope().Append(reinterpereted->PeekName());
					}
				}
				else if (reinterpereted->Depth() > 0)//Deal with nested scope
				{
					Scope& nested = reinterpereted->GetScope().AppendScope(reinterpereted->PeekName());

					reinterpereted->SetScope(&nested);
				}

			}

			reinterpereted->IncrementDepth();


			return true;
		}
		return false;
	}

	//Handles end elements
	bool XMLParseHelperTable::EndElementHandler(XmlParseMaster::SharedData* data, std::string name)
	{
		if (!data)
		{
			throw std::exception("Shared data is null");
		}

		if (data->Is("SharedDataScope"))
		{
			//Reinterperet the shared data
			SharedDataScope* reinterpereted = data->As<SharedDataScope>();

			//Make sure this is one of the things handled in scope
			if (name != tableString && name != integerString && name != floatString && name != vectorString && name != matrixString && name != stringString)			
			{
				return false;
			}

			reinterpereted->DecrementDepth();
			mStateStack.PopFront();
			if (reinterpereted->Depth() > 0)
			{
				reinterpereted->PopName();
				reinterpereted->PopIndex();
			}
			//mInsertionStack.PopFront();
			
			if (name == tableString && reinterpereted->Depth() > 0)//Deal with nested scopes
			{
				reinterpereted->SetScope(reinterpereted->GetScope().GetParent());
			}

			return true;
		}
		return false;
	}

	/*Character data is used here to fill out the individual datum elements of the scope
	  Each element is in the form <type name="string" index="int">value</type>
	*/
	bool XMLParseHelperTable::CharDataHandler(XmlParseMaster::SharedData* data, std::string charData, std::uint32_t length)
	{
		if (data->Is("SharedDataScope"))
		{
			//Reinterperet the data
			SharedDataScope* reinterpereted = data->As<SharedDataScope>();

			Datum* curDatum = nullptr;

			//Seperate block for if current scope is an action event, as we will find our current datum in the arguments list instead of the raw scope
			if (reinterpereted->GetScope().Is("ActionEvent"))
			{
				curDatum = reinterpereted->GetScope().As<ActionEvent>()->GetArguments()->Find(reinterpereted->PeekName());
			}
			else
			{
				//Get address of the current datum that we are interpereting chararcter data for
				curDatum = reinterpereted->GetScope().Find(reinterpereted->PeekName());
			}

			//Get the index of the datum that we want to insert into
			std::uint32_t index = reinterpereted->PeekIndex();

			//Read the char data into a string
			std::string stringData;

			for (std::uint32_t i = 0; i < length; i++)
			{
				stringData.push_back(charData[i]);
			}

			//Use our current state to figure out what kind of data we are meant to be reading in
			//Once the data type is determined, use the index of the insertionStack to insert the new char data into the datum.
			//Set the data type and size if necessary

			//Check to see if we've actually been dealing with this one
			if (mStateStack.Size() == 0)
			{
				return false;
			}

			StateType curState = mStateStack.Front();
			switch (curState)
			{
			case Library::XMLParseHelperTable::PARSING_INTEGER:

				if (curDatum->GetType() == Datum::UNKNOWN)
				{
					curDatum->SetType(Datum::INTEGER);
				}
				
				if (curDatum->Size() <= index)
				{
					curDatum->SetSize(index + 1);
				}
				
				curDatum->SetFromString(stringData, index);
				return true;				
				break;
			case Library::XMLParseHelperTable::PARSING_FLOAT:

				if (curDatum->GetType() == Datum::UNKNOWN)
				{
					curDatum->SetType(Datum::FLOAT);
				}

				if (curDatum->Size() <= index)
				{
					curDatum->SetSize(index + 1);
				}
				curDatum->SetFromString(stringData, index);
				return true;
				break;
			case Library::XMLParseHelperTable::PARSING_VECTOR:

				if (curDatum->GetType() == Datum::UNKNOWN)
				{
					curDatum->SetType(Datum::VECTOR);
				}

				if (curDatum->Size() <= index)
				{
					curDatum->SetSize(index + 1);
				}				

				curDatum->SetFromString(stringData, index);
				return true;
				break;
			case Library::XMLParseHelperTable::PARSING_MATRIX:

				if (curDatum->GetType() == Datum::UNKNOWN)
				{
					curDatum->SetType(Datum::MATRIX);
				}

				if (curDatum->Size() <= index)
				{
					curDatum->SetSize(index + 1);
				}								

				curDatum->SetFromString(stringData, index);
				return true;
				break;
			case Library::XMLParseHelperTable::PARSING_STRING:

				if (curDatum->GetType() == Datum::UNKNOWN)
				{
					curDatum->SetType(Datum::STRING);
				}

				if (curDatum->Size() <= index)
				{
					curDatum->SetSize(index + 1);
				}

				curDatum->SetFromString(stringData, index);
				return true;
				break;
			default:
				return false;
				break;
			}

		}
		
		return false;
	}

	//Clone (Virtual constructor)
	XMLParseHelperTable* XMLParseHelperTable::Clone()
	{
		XMLParseHelperTable* returnVal = new XMLParseHelperTable();

		return returnVal;
	}

}