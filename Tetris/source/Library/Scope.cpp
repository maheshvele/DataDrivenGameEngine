#include "pch.h"
#include "Scope.h"
namespace Library
{
	RTTI_DEFINITIONS(Scope);

	//Constructor
	Scope::Scope(std::uint32_t size) :
		mHashMap(size), mOrderVector(), mParent(nullptr)
	{
		mOrderVector.Reserve(size);
	}

	//Copy Constructor
	Scope::Scope(const Scope& rhs) :
		mHashMap(rhs.mHashMap.Size()), mOrderVector(), mParent(nullptr)
	{
		if (&rhs != this)
		{
			operator=(rhs);
		}
	}

	//Destructor
	Scope::~Scope()
	{
		Orphan();
		Clear();
	}

	//Append an item to the list if its not already there. Otherwise, return the existing item
	Datum& Scope::Append(const std::string& name)
	{
		Hashmap<std::string, Datum>::Iterator it = mHashMap.Find(name);
		
		//Create a new item if one does not already exist
		if (it == mHashMap.end())
		{
			Datum d;
			std::pair <std::string, Datum> newItem(name, d);
			Hashmap<std::string, Datum>::Iterator newLocation = mHashMap.Insert(newItem);
			std::pair <std::string, Datum> *itemAdress = &((*newLocation));
			mOrderVector.PushBack(itemAdress);
			return (*newLocation).second;
		}
		else
		{
			return (*it).second;
		}
	}

	//Get a reference to an item if its in the list
	Datum* Scope::Find(const std::string& name) const
	{
		Hashmap<std::string, Datum>::Iterator it = mHashMap.Find(name);
		if (it != mHashMap.end())
		{
			return &((*it).second);
		}
		else
		{
			return nullptr;
		}
	}

	//Get a reference to a datum with a name using the [] operator
	Datum& Scope::operator[](const std::string& name)
	{
		return Append(name);
	}

	//Get a reference to a datum by index using the [] operator
	Datum& Scope::operator[](std::uint32_t index)
	{
		return mOrderVector[index]->second;
	}

	//Add a fresh scope with a given name
	Scope& Scope::AppendScope(const std::string& name)
	{
		Datum d;
		d.SetType(Datum::TABLE);

		Scope *s = new Scope(10);
		s->mParent = this;
		d.Set(s);

		std::pair <std::string, Datum> newItem(name, d);

		Hashmap<std::string, Datum>::Iterator newLocation = mHashMap.Insert(newItem);
		std::pair <std::string, Datum> *itemAdress = &(*newLocation);
		mOrderVector.PushBack(itemAdress);
		return *s;
	}

	//Add a scope to our table with a given name and index
	void Scope::Adopt(Scope* newChild, const std::string& name, std::uint32_t index)
	{

		newChild->Orphan();

		Hashmap<std::string, Datum>::Iterator it = mHashMap.Find(name);


		//If the new item isn't present, add it to the hash map
		if (it == mHashMap.end())
		{		
			newChild->mParent = this;

			Datum d;
			d.SetType(Datum::TABLE);
			d.Set(newChild);
			std::pair <std::string, Datum> newItem(name, d);
			Hashmap<std::string, Datum>::Iterator newLocation = mHashMap.Insert(newItem);
			std::pair <std::string, Datum> *itemAdress = &((*newLocation));
			mOrderVector.PushBack(itemAdress);



		}
		//Otherwise, set the scope item to the given index in the datum
		else
		{
			//Ensure that the datum we're adopting into doesn't have external memory
			if ((*it).second.IsExternal())
			{
				return;
			}

			(*it).second.Set(newChild, index);
		}
	}

	//Check the current parent of this scope
	Scope* Scope::GetParent() const
	{
		return mParent;
	}

	//Get the name associated with a particular address
	std::string Scope::FindName(const Scope* toFind) const
	{
		for (std::uint32_t i = 0; i < mOrderVector.Size(); i++)
		{
			if (mOrderVector[i]->second.GetType() == Datum::TABLE)
			{
				for (std::uint32_t j = 0; j < mOrderVector[i]->second.Size(); j++)
				{
					if (toFind == mOrderVector[i]->second.Get<Scope*>(j))
					{
						return mOrderVector[i]->first;
					}
				}
			}
		}

		return "";

	}

	//Recursively search through all parents
	Datum* Scope::Search(const std::string& name, Scope** address)
	{
		Datum* returnVal = Find(name);
		if (returnVal == nullptr)
		{
			if (mParent != nullptr)
			{
				if (address != nullptr)
				{
					*address = this;
				}
				return  mParent->Search(name, address);
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			return returnVal;
		}


	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		if (this == &rhs)//Self assignment check
		{
			return *this;
		}
		Clear();

		//Copy the structures
		for (std::uint32_t i = 0; i < rhs.mOrderVector.Size(); i++)
		{
			Hashmap<std::string, Datum>::Iterator newLocation = mHashMap.Insert(*(rhs.mOrderVector[i]));
			std::pair <std::string, Datum> *itemAdress = &((*newLocation));
			mOrderVector.PushBack(itemAdress);
		}

		//Copy the individual datum subscopes
		for (std::uint32_t i = 0; i < rhs.mOrderVector.Size(); i++)
		{
			if (mOrderVector[i]->second.GetType() == Datum::TABLE)
			{
				for (std::uint32_t j = 0; j < rhs.mOrderVector[i]->second.Size(); j++)
				{
					Scope *s;

					if (mOrderVector[i]->second.IsExternal())
					{
						s = rhs.mOrderVector[i]->second.Get<Scope*>();
					}
					else
					{
						//Check for uninitialized data
						if (rhs.mOrderVector[i]->second.Get<Scope*>(j) != nullptr)
						{
							s = new Scope(rhs.mOrderVector[i]->second.Get<Scope*>(j)->mOrderVector.Size());
							*s = *(rhs.mOrderVector[i]->second.Get<Scope*>(j));
						}
						else
						{
							s = new Scope();
						}

						s->mParent = this;
					}

					mOrderVector[i]->second.Set(s, j);
				}
			}
		}

		return *this;
	}

	void Scope::Orphan()
	{
		if (mParent == nullptr)
		{
			return;
		}

		for (std::uint32_t i = 0; i < mParent->mOrderVector.Size(); i++)
		{
			if (mParent->mOrderVector[i]->second !=  nullptr && mParent->mOrderVector[i]->second.GetType() == Datum::TABLE)
			{
				for (std::uint32_t j = 0; j < mParent->mOrderVector[i]->second.Size(); j++)
				{
					if (mParent->mOrderVector[i]->second.Get<Scope*>(j) == this)
					{
						mParent->mOrderVector[i]->second.Set((Scope*)nullptr, j);
					}
				}
			}
		}

		mParent = nullptr;

	}

	void Scope::Clear()
	{
		//Delete allocated memory
		for (std::uint32_t i = 0; i < mOrderVector.Size(); i++)
		{
			if (mOrderVector[i]->second.GetType() == Datum::TABLE && !mOrderVector[i]->second.IsExternal())
			{
				for (std::uint32_t j = 0; j < mOrderVector[i]->second.Size(); j++)
				{
					if (!mOrderVector[i]->second.IsExternal())
					{
						Scope *temp = mOrderVector[i]->second.Get<Scope*>(j);

						if (temp != nullptr)
						{
							if (temp->mParent != nullptr)
							{
								delete temp;
							}
							else
							{
								temp->Orphan();
							}
						}
					}
				}
			}
		}
		mHashMap.Clear();
		mOrderVector.Clear();
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		if (mOrderVector.Size() != rhs.mOrderVector.Size())
		{
			return false;
		}

		for (std::uint32_t i = 0; i < mOrderVector.Size(); i++)
		{
			if (mOrderVector[i] == nullptr && rhs.mOrderVector[i] == nullptr)
			{
				continue;
			}


			if ((*(mOrderVector[i])).first != (*(rhs.mOrderVector[i])).first)
			{
				return false;
			}
			else if ( (*(mOrderVector[i])).second != (*(rhs.mOrderVector[i])).second )
			{
				return false;
			}
		}

		return true;
	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		return !(operator==(rhs));
	}

	std::uint32_t Scope::Size()
	{
		return mOrderVector.Size();
	}

	Vector<std::pair<std::string, Datum>*>::Iterator Scope::begin() const
	{
		return mOrderVector.begin();
	}

	Vector<std::pair<std::string, Datum>*>::Iterator Scope::end() const
	{
		return mOrderVector.end();
	}
}