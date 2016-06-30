#include "pch.h"
#include "Attributed.h"

namespace Library
{
	RTTI_DEFINITIONS(Attributed)

	//Constructor
	Attributed::Attributed(std::uint32_t size) :
		Scope(size), mSignatures(size)
	{
	}

	//Destructor
	Attributed::~Attributed()
	{
	}

	//Copy constructor
	Attributed::Attributed(const Attributed& rhs) :
		mSignatures(rhs.mSignatures.Size()), Scope(rhs)
	{
		operator=(rhs);
	}

	//Assignment operator
	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		for (auto& item : rhs.mSignatures)
		{
			mSignatures.Insert(item);
		}

		Scope::operator=(rhs);

		//Make sure we have our own 'this' pointer
		(*this)["this"] = (RTTI*)this;
		//Datum *tempThis = Find("this");
		//tempThis->Clear();
		//tempThis->Set((RTTI*)this);

		return *this;
	}

	//Populate the scope with Prescribed memebrs
	void Attributed::Populate()
	{
		//Add 'this' to the perscribed attribute list
		(*this)["this"] = (RTTI*)this;
		//Datum &thisDatum = Append("this");
		//thisDatum.SetType(Datum::POINTER);
		//thisDatum.SetSize(1);
		//thisDatum.Set((RTTI*)this);

		//Populate based on the signatures
		for (auto &sig : mSignatures)
		{
			
			if (sig.second.mType == Datum::TABLE)
			{
				if (Find(sig.second.mName) == nullptr)
				{
					AppendScope(sig.second.mName);
				}
				continue;
			}

			Datum &d = Append(sig.second.mName);
			d.SetType(sig.second.mType);
			
			if (sig.second.mStorage == nullptr)//Set up the size ahead of time unless we're external
			{
				d.SetSize(sig.second.mSize);

				//Initialize values if we have an initial value
				//Otherwise, set them to a default value
				std::uint32_t i;

				switch (sig.second.mType)
				{
					case Library::Datum::UNKNOWN:
						throw std::exception("Cannot compare unknown data");
						break;
					case Library::Datum::INTEGER:
						if (sig.second.mInitialValue != nullptr)
						{
							for (i = 0; i < sig.second.mSize; i++)
							{
								d.Set(((int*)sig.second.mInitialValue)[i], i);
							}
						}
						else
						{
							d.Set(0);
						}
						break;
					case Library::Datum::FLOAT:
						if (sig.second.mInitialValue != nullptr)
						{
							for (i = 0; i < sig.second.mSize; i++)
							{
								d.Set(((float*)sig.second.mInitialValue)[i], i);
							}
						}
						else
						{
							d.Set(0.f);
						}
						break;
					case Library::Datum::VECTOR:
						if (sig.second.mInitialValue != nullptr)
						{
							for (i = 0; i < sig.second.mSize; i++)
							{
								d.Set(((glm::vec4*)sig.second.mInitialValue)[i], i);
							}
						}
						else
						{
							d.Set(glm::vec4(0.f));
						}
						break;
					case Library::Datum::MATRIX:
						if (sig.second.mInitialValue != nullptr)
						{
							for (i = 0; i < sig.second.mSize; i++)
							{
								d.Set(((glm::mat4*)sig.second.mInitialValue)[i], i);
							}
						}
						else
						{
							d.Set(glm::mat4(0.f));
						}
						break;
					case Library::Datum::STRING:
						if (sig.second.mInitialValue != nullptr)
						{
							for (i = 0; i < sig.second.mSize; i++)
							{
								d.Set( ( (std::string*)sig.second.mInitialValue )[i], i);
								std::string s = d.Get<std::string>(i);
								if (s == s){}
							}
						}
						else
						{
							d.Set("");
						}
						break;
					case Library::Datum::POINTER:
						if (sig.second.mInitialValue != nullptr)
						{
							for (i = 0; i < sig.second.mSize; i++)
							{
								d.Set(((RTTI**)sig.second.mInitialValue)[i], i);
							}
						}
						else
						{
							d.Set((RTTI*)nullptr);
						}
						break;
					default:
						break;
				}
			}
			//Initialize external value if we have one
			else
			{
				switch (sig.second.mType)
				{
				case Library::Datum::UNKNOWN:
					throw std::exception("Cannot compare unknown data");
					break;
				case Library::Datum::INTEGER:
					d.SetStorage((int*)sig.second.mStorage, sig.second.mSize);
					break;
				case Library::Datum::FLOAT:
					d.SetStorage((float*)sig.second.mStorage, sig.second.mSize);
					break;
				case Library::Datum::VECTOR:
					d.SetStorage((glm::vec4*)sig.second.mStorage, sig.second.mSize);
					break;
				case Library::Datum::MATRIX:
					d.SetStorage((glm::mat4*)sig.second.mStorage, sig.second.mSize);
					break;
				case Library::Datum::STRING:
					d.SetStorage((std::string*)sig.second.mStorage, sig.second.mSize);
					break;
				case Library::Datum::POINTER:
					d.SetStorage((RTTI**)sig.second.mStorage, sig.second.mSize);
					break;
				case Library::Datum::TABLE:
					d.SetStorage((Scope**)sig.second.mStorage, sig.second.mSize);
					break;
				default:
					break;
				}
			}


		}
	}

	//Check to see if we have an attribute of the given name
	bool Attributed::IsAttribute(const std::string& name) const
	{
		Datum *temp = Find(name);
		if (temp == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	//Chekc to see if we have a prescribed attribute of the given name
	bool Attributed::IsPrescribedAttribute(const std::string& name) const
	{
		return (name == "this" || mSignatures.Find(name) != mSignatures.end());
	}

	//Check to see if we have an auxiliary attribute of the given name
	bool  Attributed::IsAuxiliaryAttribute(const std::string& name) const
	{
		return (IsAttribute(name) && !IsPrescribedAttribute(name));
	}


	//Add a new auxiliary attribute to the scope. Return existing if its already there
	Datum& Attributed::AppendAuxiliaryAttribute(std::string name)
	{
		if (IsPrescribedAttribute(name))
		{
			//return *(mScope.Find(name));
			throw std::exception("Cannot append an auxiliary attribute with the same name as a prescribed atribute");
		}
		
		Datum &d = Append(name);
		return d;
	}

	//Get the beginning of our auxiliary attributes
	std::uint32_t Attributed::AuxiliaryBegin() const
	{
		return mSignatures.Size() + 1; //1 over the size to account for this pointer
	}
}