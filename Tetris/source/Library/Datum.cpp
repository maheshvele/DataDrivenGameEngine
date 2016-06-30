#include "pch.h"
#include "Datum.h"

namespace Library
{
	//Set up static function pointer arrays
	Datum::reserveMemoryFP Datum::reservePointers[9] = { nullptr, Datum::IntReserveCopy, Datum::FloatReserveCopy, Datum::VecReserveCopy, Datum::MatReserveCopy, Datum::StringReserveCopy, Datum::PointerReserveCopy, Datum::ScopeReserveCopy, nullptr };
	Datum::deleteMemoryFP Datum::deletionPointers[9] = { nullptr, Datum::IntDelete, Datum::FloatDelete, Datum::VecDelete, Datum::MatDelete, Datum::StringDelete, Datum::PointerDelete, Datum::ScopeDelete, nullptr };

	//Default constructor
	Datum::Datum() :
		mType(UNKNOWN), mSize(0), mCapacity(0), mIsExternal(false), mValues()
	{
	}

	//Constructor with type and size
	Datum::Datum(DatumType type, std::uint32_t size) :
		mType(type), mSize(0), mCapacity(0), mIsExternal(false), mValues()
	{
		SetSize(size);
	}

	//Default destructor
	Datum::~Datum()
	{
		if (mType != UNKNOWN && !mIsExternal)
		{
			deletionPointers[mType](mValues);
		}
	}

	//Copy constructor
	Datum::Datum(const Datum& rhs) :
		mType(UNKNOWN)
	{
		operator=(rhs);
	}

	//Assinment operator
	Datum& Datum::operator=(const Datum& rhs)
	{
		//Self assignment test
		if (this == &rhs)
		{
			return *this;
		}

		
		if (!mIsExternal) //lhs internal
		{
			if (mType != UNKNOWN)
			{
				deletionPointers[mType](mValues);
			}

			//rhs internal
			if (!rhs.mIsExternal)
			{
				if (rhs.mType != UNKNOWN)
				{
					mValues = reservePointers[rhs.mType](rhs.mSize, rhs.mSize, rhs.mValues);
				}
				mType = rhs.mType;
				mSize = rhs.mSize;
				mCapacity = rhs.mCapacity;
				mIsExternal = rhs.mIsExternal;
			}
			else //rhs external
			{
				if (rhs.mType != UNKNOWN)
				{
					mValues = rhs.mValues;//reservePointers[rhs.mType](rhs.mSize, rhs.mSize, rhs.mValues);
				}
				mType = rhs.mType;
				mSize = rhs.mSize;
				mCapacity = rhs.mCapacity;
				mIsExternal = rhs.mIsExternal;
			}

		}
		else //lhs external
		{
			//rhs internal
			if (!rhs.mIsExternal)
			{
				if (rhs.mType != UNKNOWN)
				{
					mValues = reservePointers[rhs.mType](rhs.mSize, rhs.mSize, rhs.mValues);
				}
				mType = rhs.mType;
				mSize = rhs.mSize;
				mCapacity = rhs.mCapacity;
				mIsExternal = rhs.mIsExternal;
			}
			else //rhs external
			{
				if (rhs.mType != UNKNOWN)
				{
					mValues = rhs.mValues; //reservePointers[rhs.mType](rhs.mSize, rhs.mSize, rhs.mValues);
				}
				mType = rhs.mType;
				mSize = rhs.mSize;
				mCapacity = rhs.mCapacity;
				mIsExternal = rhs.mIsExternal;
			}
		}

		return *this;
	}

	//Assignment operator for scalar int
	Datum& Datum::operator=(const int& rhs)
	{
		if (mType == UNKNOWN)
		{
			mType = INTEGER;
		}
		else if (mType != INTEGER)
		{
			throw std::exception("Wrong type");
		}

		//Internal
		if (!mIsExternal)
		{
			SetSize(1);
			Set(rhs);
		}
		else //External
		{
			mValues.i = nullptr;
			mIsExternal = false;
			SetSize(1);
			Set(rhs);
		}

		return *this;
	}

	//Assignment operator for scalar float
	Datum& Datum::operator=(const float& rhs)
	{
		if (mType == UNKNOWN)
		{
			mType = FLOAT;
		}
		else if (mType != FLOAT)
		{
			throw std::exception("Wrong type");
		}

		//Internal
		if (!mIsExternal)
		{
			SetSize(1);
			Set(rhs);
		}
		else //External
		{
			mValues.i = nullptr;
			mIsExternal = false;
			SetSize(1);
			Set(rhs);
		}

		return *this;
	}

	//Assignment operator for scalar vector
	Datum& Datum::operator=(const glm::vec4& rhs)
	{
		if (mType == UNKNOWN)
		{
			mType = VECTOR;
		}
		else if (mType != VECTOR)
		{
			throw std::exception("Wrong type");
		}

		//Internal
		if (!mIsExternal)
		{
			SetSize(1);
			Set(rhs);
		}
		else //External
		{
			mValues.i = nullptr;
			mIsExternal = false;
			SetSize(1);
			Set(rhs);
		}

		return *this;
	}

	//Assingment operator for scalar matrix
	Datum& Datum::operator=(const glm::mat4& rhs)
	{
		if (mType == UNKNOWN)
		{
			mType = MATRIX;
		}
		else if (mType != MATRIX)
		{
			throw std::exception("Wrong type");
		}

		//Internal
		if (!mIsExternal)
		{
			SetSize(1);
			Set(rhs);
		}
		else //External
		{
			mValues.i = nullptr;
			mIsExternal = false;
			SetSize(1);
			Set(rhs);
		}

		return *this;
	}

	//Assignment opertor for scalar string
	Datum& Datum::operator=(const std::string& rhs)
	{
		if (mType == UNKNOWN)
		{
			mType = STRING;
		}
		else if (mType != STRING)
		{
			throw std::exception("Wrong type");
		}

		//Internal
		if (!mIsExternal)
		{
			SetSize(1);
			Set(rhs);
		}
		else //External
		{
			mValues.i = nullptr;
			mIsExternal = false;
			SetSize(1);
			Set(rhs);
		}

		return *this;
	}

	//Assignment operator for scalar pointer
	Datum& Datum::operator=(RTTI* rhs)
	{
		if (mType == UNKNOWN)
		{
			mType = POINTER;
		}
		else if (mType != POINTER)
		{
			throw std::exception("Wrong type");
		}

		//Internal
		if (!mIsExternal)
		{
			SetSize(1);
			Set(rhs);
		}
		else //External
		{
			mValues.i = nullptr;
			mIsExternal = false;
			SetSize(1);
			Set(rhs);
		}

		return *this;
	}

	//Assignment operator for scalar scope
	Datum& Datum::operator=(Scope* rhs)
	{
		if (mType == UNKNOWN)
		{
			mType = TABLE;
		}
		else if (mType != TABLE)
		{
			throw std::exception("Wrong type");
		}

		//Internal
		if (!mIsExternal)
		{
			SetSize(1);
			Set(rhs);
		}
		else //External
		{
			mValues.i = nullptr;
			mIsExternal = false;
			SetSize(1);
			Set(rhs);
		}

		return *this;
	}

	//Equality operator
	bool Datum::operator==(const Datum& rhs)
	{
		if (mIsExternal != rhs.mIsExternal || mType != rhs.mType || mSize != rhs.mSize)
		{
			return false;
		}

		std::uint32_t i;

		switch (mType)
		{
		case Library::Datum::UNKNOWN:
			throw std::exception("Cannot compare unknown data");
			break;
		case Library::Datum::INTEGER:
			for (i = 0; i < mSize; i++)
			{
				if (mValues.i[i] != rhs.mValues.i[i])
				{
					return false;
				}
			}
			break;
		case Library::Datum::FLOAT:
			for (i = 0; i < mSize; i++)
			{
				if (mValues.f[i] != rhs.mValues.f[i])
				{
					return false;
				}
			}
			break;
		case Library::Datum::VECTOR:
			for (i = 0; i < mSize; i++)
			{
				if (mValues.v[i] != rhs.mValues.v[i])
				{
					return false;
				}
			}
			break;
		case Library::Datum::MATRIX:
			for (i = 0; i < mSize; i++)
			{
				if (mValues.m[i] != rhs.mValues.m[i])
				{
					return false;
				}
			}
			break;
		case Library::Datum::STRING:
			for (i = 0; i < mSize; i++)
			{
				if (mValues.s[i] != rhs.mValues.s[i])
				{
					return false;
				}
			}
			break;
		case Library::Datum::POINTER:
			for (i = 0; i < mSize; i++)
			{
				if (mValues.p[i] != rhs.mValues.p[i])
				{
					return false;
				}
			}
			break;
		case Library::Datum::TABLE:
			for (i = 0; i < mSize; i++)
			{
				if (mValues.sc[i] != rhs.mValues.sc[i])
				{
					return false;
				}
			}
			break;
		default:
			break;
		}

		return true;
	}

	//Equailty operator (scalar int)
	bool Datum::operator==(const int& rhs)
	{
		if (mSize != 1 || mType != INTEGER || mValues.i[0] != rhs)
		{
			return false;
		}

		return true;
	}

	//Equality operator (scalar float)
	bool Datum::operator==(const float& rhs)
	{
		if (mSize != 1 || mType != FLOAT || mValues.f[0] != rhs)
		{
			return false;
		}

		return true;
	}

	//Equality (scalar vector)
	bool Datum::operator==(const glm::vec4& rhs)
	{
		if (mSize != 1 || mType != VECTOR || mValues.v[0] != rhs)
		{
			return false;
		}

		return true;
	}

	//Equality (scalar matrix)
	bool Datum::operator==(const glm::mat4 &rhs)
	{
		if (mSize != 1 || mType != MATRIX || mValues.m[0] != rhs)
		{
			return false;
		}

		return true;
	}

	//Equality (scalar string)
	bool Datum::operator==(const std::string& rhs)
	{
		if (mSize != 1 || mType != STRING || mValues.s[0] != rhs)
		{
			return false;
		}

		return true;
	}

	//Equality (scalar pointer)
	bool Datum::operator==(const RTTI* rhs)
	{
		if (mSize != 1 || mType != POINTER || mValues.p[0] != rhs)
		{
			return false;
		}

		return true;
	}

	//Inequality operator
	bool Datum::operator!=(const Datum& rhs)
	{
		return !(operator==(rhs));
	}

	//Inequality operator (scalar int)
	bool Datum::operator!=(const int& rhs)
	{
		return !(operator==(rhs));
	}

	//Inequality operator (scalar float)
	bool Datum::operator!=(const float& rhs)
	{
		return !(operator==(rhs));
	}

	//Inequality operator (scalar vector)
	bool Datum::operator!=(const glm::vec4& rhs)
	{
		return !(operator==(rhs));
	}

	//Inequality operator (scalar matrix)
	bool Datum::operator!=(const glm::mat4& rhs)
	{
		return !(operator==(rhs));
	}

	//Inequality operator (scalar string)
	bool Datum::operator!=(const std::string& rhs)
	{
		return !(operator==(rhs));
	}

	//Inequality operator (scalar pointer)
	bool Datum::operator!=(RTTI* rhs)
	{
		return !(operator==(rhs));
	}
	
	//Check the type
	Datum::DatumType Datum::GetType() const
	{
		return mType;
	}

	//Check number of elements
	std::uint32_t Datum::Size() const
	{
		return mSize;
	}

	//Set type of current data
	void Datum::SetType(DatumType newType)
	{
		if (mType != UNKNOWN && mType != newType)
		{
			throw std::exception("Type is already defined. Cannot be changed");
		}
		mType = newType;
	}

	//Update size and reserve more memory if needed
	void Datum::SetSize(std::uint32_t newSize)
	{
		//Ensure that our type isn't unknown
		if (mType == UNKNOWN)
		{
			throw std::exception("Cannot change size. Type is not yet known");
		}

		//Ensure that we're not external
		if (mIsExternal)
		{
			throw std::exception("Cannot resize external storage");
		}

		if (newSize > mCapacity)
		{
			DatumValues tempValues = reservePointers[mType](newSize, mSize, mValues);
			deletionPointers[mType](mValues);
			mValues = tempValues;

			//Update the capacity
			mCapacity = newSize;
		}

		mSize = newSize;

	}

	//Set array up with external data (int)
	void Datum::SetStorage(int *newData, std::uint32_t newSize)
	{
		if (!mIsExternal && ((mType != UNKNOWN && mType != INTEGER) || mSize > 0))
		{
			throw std::exception("Cannot set storage with datum that already has allocations");
		}

		

		mSize = newSize;
		mValues.i = newData;
		mType = INTEGER;
		mIsExternal = true;
	}

	//Set array up with external data (float)
	void Datum::SetStorage(float *newData, std::uint32_t newSize)
	{
		if (!mIsExternal && ((mType != UNKNOWN && mType != FLOAT) || mSize > 0))
		{
			throw std::exception("Cannot set storage with datum that already has allocations");
		}

		mSize = newSize;
		mValues.f = newData;
		mType = FLOAT;
		mIsExternal = true;
	}

	//Set array up with external data (vector)
	void Datum::SetStorage(glm::vec4 *newData, std::uint32_t newSize)
	{
		if (!mIsExternal && ((mType != UNKNOWN && mType != VECTOR) || mSize > 0))
		{
			throw std::exception("Cannot set storage with datum that already has allocations");
		}

		mSize = newSize;
		mValues.v = newData;
		mType = VECTOR;
		mIsExternal = true;
	}

	//Set array up with external data (matrix)
	void Datum::SetStorage(glm::mat4 *newData, std::uint32_t newSize)
	{
		if (!mIsExternal && ((mType != UNKNOWN && mType != MATRIX) || mSize > 0))
		{
			throw std::exception("Cannot set storage with datum that already has allocations");
		}

		mSize = newSize;
		mValues.m = newData;
		mType = MATRIX;
		mIsExternal = true;
	}

	//Set array up with external data (string)
	void Datum::SetStorage(std::string *newData, std::uint32_t newSize)
	{
		if (!mIsExternal && ((mType != UNKNOWN && mType != STRING) || mSize > 0))
		{
			throw std::exception("Cannot set storage with datum that already has allocations");
		}

		mSize = newSize;
		mValues.s = newData;
		mType = STRING;
		mIsExternal = true;
	}

	//Set array up with external data (poointer)
	void Datum::SetStorage(RTTI **newData, std::uint32_t newSize)
	{
		if (!mIsExternal && ((mType != UNKNOWN && mType != POINTER) || mSize > 0))
		{
			throw std::exception("Cannot set storage with datum that already has allocations");
		}

		mSize = newSize;
		mValues.p = newData;
		mType = POINTER;
		mIsExternal = true;
	}

	//Set array up with external data (scope)
	void Datum::SetStorage(Scope **newData, std::uint32_t newSize)
	{
		if (!mIsExternal && ((mType != UNKNOWN && mType != TABLE) || mSize > 0))
		{
			throw std::exception("Cannot set storage with datum that already has allocations");
		}

		mSize = newSize;
		mValues.sc = newData;
		mType = TABLE;
		mIsExternal = true;
	}

	//Set a value in the array (int)
	void Datum::Set(int newInt, std::uint32_t index)
	{
		//Type check
		if (mType != INTEGER)
		{
			throw std::exception("Wrong datum type");
		}

		//Size check
		if (index >= mSize)
		{
			//Check if we're using external data
			if (mIsExternal)
			{
				return;
			}

			//Create new space if data is internal
			SetSize(index+1);
		}

		//Set value
		mValues.i[index] = newInt;
	}

	//Set a value in the array (float)
	void Datum::Set(float newFloat, std::uint32_t index)
	{
		//Type check
		if (mType != FLOAT)
		{
			throw std::exception("Wrong datum type");
		}

		//Size check
		if (index >= mSize)
		{
			//Check if we're using external data
			if (mIsExternal)
			{
				return;
			}

			//Create new space if data is internal
			SetSize(index+1);
		}

		//Set value
		mValues.f[index] = newFloat;
	}

	//Set a value in the array (vector)
	void Datum::Set(glm::vec4 newVec, std::uint32_t index)
	{
		if (mType != VECTOR)
		{
			throw std::exception("Wrong datum type");
		}

		//Size check
		if (index >= mSize)
		{
			//Check if we're using external data
			if (mIsExternal)
			{
				return;
			}

			//Create new space if data is internal
			SetSize(index+1);
		}

		//Set values
		mValues.v[index] = newVec;
	}

	//Set a value in the array (matrix)
	void Datum::Set(glm::mat4 newMat, std::uint32_t index)
	{
		if (mType != MATRIX)
		{
			throw std::exception("Wrong datum type");
		}

		//Size check
		if (index >= mSize)
		{
			//Check if we're using external data
			if (mIsExternal)
			{
				return;
			}

			//Create new space if data is internal
			SetSize(index+1);
		}

		//Set values
		mValues.m[index] = newMat;
	}

	//Set a value in the array (string)
	void Datum::Set(std::string newString, std::uint32_t index)
	{
		//Type check
		if (mType != STRING)
		{
			throw std::exception("Wrong datum type");
		}

		//Size check
		if (index >= mSize)
		{
			//Check if we're using external data
			if (mIsExternal)
			{
				return;
			}

			//Create new space if data is internal
			SetSize(index+1);
		}

		//Set value
		mValues.s[index] = newString;
	}

	//Set a value in the array (RTTI)
	void Datum::Set(RTTI* newPointer, std::uint32_t index)
	{
		//Type check
		if (mType != POINTER)
		{
			throw std::exception("Wrong datum type");
		}

		//Size check
		if (index >= mSize)
		{
			//Check if we're using external data
			if (mIsExternal)
			{
				return;
			}

			//Create new space if data is internal
			SetSize(index + 1);
		}

		//Set value
		mValues.p[index] = newPointer;
	}
	
	//Set for scope
	void Datum::Set(Scope* newScope, std::uint32_t index)
	{
		//Type check
		if (mType != TABLE)
		{
			throw std::exception("Wrong datum type");
		}

		//Size check
		if (index >= mSize)
		{
			//Check if we're using external data
			if (mIsExternal)
			{
				return;
			}

			//Create new space if data is internal
			SetSize(index + 1);
		}

		//Set value
		mValues.sc[index] = newScope;
	}

	
	//Get a value (int template)
	template<>
	int& Datum::Get(std::uint32_t index)
	{
		
		//Type check
		if (mType != INTEGER)
		{
			throw std::exception("Wrong datum type");
		}
	
		//Sanity check index
		if (index >= mSize)
		{
			throw std::exception("Out of bounds");
		}

		return mValues.i[index];
	}

	//Get a value (float template)
	template<>
	float& Datum::Get(std::uint32_t index)
	{
		//Type check
		if (mType != FLOAT)
		{
			throw std::exception("Wrong datum type");
		}

		//Sanity check index
		if (index >= mSize)
		{
			throw std::exception("Out of bounds");
		}

		return mValues.f[index];
	}

	//Get a value (vector template)
	template<>
	glm::vec4& Datum::Get(std::uint32_t index)
	{
		//Type check
		if (mType != VECTOR)
		{
			throw std::exception("Wrong datum type");
		}

		//Sanity check index
		if (index >= mSize)
		{
			throw std::exception("Out of bounds");
		}

		return mValues.v[index];
	}

	//Get a value (matrix template)
	template<>
	glm::mat4& Datum::Get(std::uint32_t index)
	{
		//Type check
		if (mType != MATRIX)
		{
			throw std::exception("Wrong datum type");
		}

		//Sanity check index
		if (index >= mSize)
		{
			throw std::exception("Out of bounds");
		}

		return mValues.m[index];
	}

	//Get a value (string template)
	template<>
	std::string& Datum::Get(std::uint32_t index)
	{
		//Type check
		if (mType != STRING)
		{
			throw std::exception("Wrong datum type");
		}

		//Sanity check index
		if (index >= mSize)
		{
			throw std::exception("Out of bounds");
		}

		return mValues.s[index];
	}


	//Get a value (Pointer template)
	template<>
	RTTI*& Datum::Get(std::uint32_t index)
	{

		//Type check
		if (mType != POINTER)
		{
			throw std::exception("Wrong datum type");
		}

		//Sanity check index
		if (index >= mSize)
		{
			throw std::exception("Out of bounds");
		}

		return mValues.p[index];
	}
	
	//Get a value (Scope template)
	template<>
	Scope*& Datum::Get(std::uint32_t index)
	{

		//Type check
		if (mType != TABLE)
		{
			throw std::exception("Wrong datum type");
		}

		//Sanity check index
		if (index >= mSize)
		{
			throw std::exception("Out of bounds");
		}

		return mValues.sc[index];
	}

	//Get the size of the datum
	std::uint32_t Datum::GetSize()
	{
		return mSize;
	}

	//Clear the data
	void Datum::Clear()
	{
		mSize = 0;
	}

	//Set the value of an element at a given index (default zero) to the value represented by the given string
	void Datum::SetFromString(std::string stringValue, std::uint32_t index)
	{

		//Sanity check index
		if (index >= mSize)
		{
			throw std::exception("Out of bounds");
		}

		int i = 0;
		int j = 0;

		//Values for tokenizing vector and matrix
		glm::vec4 v(0.0f);
		glm::mat4 m(0.0f);
		std::string token;
		std::string returnVal;
		std::istringstream iss(stringValue);

		switch (mType)
		{
		case Library::Datum::UNKNOWN:
			throw std::exception("Cannot set values before type is set");
			break;
		case Library::Datum::INTEGER:
			sscanf_s(stringValue.c_str(), "%d", &mValues.i[index]);
			break;
		case Library::Datum::FLOAT:
			sscanf_s(stringValue.c_str(), "%f", &mValues.f[index]);
			break;
		case Library::Datum::VECTOR:
			for (i = 0; i < 4; i++)
			{
				getline(iss, token, ',');
				sscanf_s(token.c_str(), "%f", &mValues.v[index][i]);
			}
			break;
		case Library::Datum::MATRIX:
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 4; j++)
				{
					if (j == 3)
					{
						getline(iss, token, ';');
						sscanf_s(token.c_str(), "%f", &mValues.m[index][i][j]);
					}
					else
					{
						getline(iss, token, ',');
						sscanf_s(token.c_str(), "%f", &mValues.m[index][i][j]);
					}
				}
			}
			break;
		case Library::Datum::STRING:
			mValues.s[index] = stringValue;
			break;
		case Library::Datum::POINTER:
			throw std::exception("Cannot set underlying value from pointer from string");
			break;	
		default:
			break;
		}

	}

	//Function gets string representation of data
	std::string Datum::ToString(std::uint32_t index)
	{
		//Sanity check index
		if (index >= mSize)
		{
			throw std::exception("Out of bounds");
		}

		std::string returnVal("");
		char temp[10]; //This is size 10 because the maximum value of an int or float has 10 digits
		std::uint32_t i, j;

		switch (mType)
		{
		case Library::Datum::UNKNOWN:
			throw std::exception("Cannot represent unknown data");
			break;
		case Library::Datum::INTEGER:
			sprintf_s(temp, "%d", Get<int>(index));
			returnVal = temp;
			break;
		case Library::Datum::FLOAT:
			sprintf_s(temp, "%f", Get<float>(index));
			returnVal = temp;
			break;
		case Library::Datum::VECTOR:
			for (i = 0; i < 4; i++)
			{
				sprintf_s(temp, "%f", mValues.v[index][i]);
				returnVal += temp;
				if (i != 3)
				{
					returnVal += ',';
				}
			}

			break;
		case Library::Datum::MATRIX:
				for (i = 0; i < 4; i++)
				{
					for (j = 0; j < 4; j++)
					{
						sprintf_s(temp, "%f", mValues.m[index][i][j]);
						returnVal += temp;
						if (j != 3)
						{
							returnVal += ',';
						}
					}
					returnVal += '\n';
				}
			break;
		case Library::Datum::STRING:
			return mValues.s[index];
			break;
		case Library::Datum::POINTER:
			throw std::exception("Cannot conovert underlying data of pointer type to string");
			break;
		default:
			break;
		}

		return returnVal;

	}

	//Function for allocating memory for ints
	Datum::DatumValues Datum::IntReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy)
	{
		DatumValues newValues;
		newValues.i = new int[size];
		for (std::uint32_t i = 0; i < oldSize; ++i)
		{
			newValues.i[i] = toCopy.i[i];
		}

		return newValues;
	}

	//Function for allocating memory for floats
	Datum::DatumValues Datum::FloatReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy)
	{
		DatumValues newValues;
		newValues.f = new float[size];
		for (std::uint32_t i = 0; i < oldSize; ++i)
		{
			newValues.f[i] = toCopy.f[i];
		}

		return newValues;
	}

	//Function for allocating memory for vectors
	Datum::DatumValues Datum::VecReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy)
	{
		DatumValues newValues;
		newValues.v = new glm::vec4[size];
		for (std::uint32_t i = 0; i < oldSize; ++i)
		{
			newValues.v[i] = toCopy.v[i];
		}
		return newValues;
	}

	//Function for allocating memory for matrices
	Datum::DatumValues Datum::MatReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy)
	{
		DatumValues newValues;
		newValues.m = new glm::mat4[size];
		for (std::uint32_t i = 0; i < oldSize; ++i)
		{
			newValues.m[i] = toCopy.m[i];
		}
		return newValues;
	}

	//Function for allocating memory for strings
	Datum::DatumValues Datum::StringReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy)
	{
		DatumValues newValues;
		newValues.s = new std::string[size];
		for (std::uint32_t i = 0; i < oldSize; ++i)
		{
			newValues.s[i] = toCopy.s[i];
		}

		return newValues;
	}

	//Function for allocating memory for pointers
	Datum::DatumValues Datum::PointerReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy)
	{
		DatumValues newValues;
		newValues.p = new RTTI*[size];
		for (std::uint32_t i = 0; i < oldSize; ++i)
		{
			newValues.p[i] = toCopy.p[i];
		}

		return newValues;
	}

	//Function for allocating memory for scopes
	Datum::DatumValues Datum::ScopeReserveCopy(std::uint32_t size, std::uint32_t oldSize, const DatumValues& toCopy)
	{
		DatumValues newValues;
		newValues.sc = new Scope*[size];
		for (std::uint32_t i = 0; i < oldSize; ++i)
		{
			newValues.sc[i] = toCopy.sc[i];
		}

		//Set new slots to nullptr so they don't get deleted if they're never allocated
		for (std::uint32_t j = oldSize; j < size; j++)
		{
			newValues.sc[j] = nullptr;
		}

		return newValues;
	}

	//Function for deleting memory for ints
	void Datum::IntDelete(DatumValues& toDelete)
	{
		delete[] toDelete.i;
	}

	//Function for deleting memory for floats
	void Datum::FloatDelete(DatumValues& toDelete)
	{
		delete[] toDelete.f;
	}

	//Function for allocating deleting for vectors
	void Datum::VecDelete(DatumValues& toDelete)
	{
		delete[] toDelete.v;
	}

	//Function for allocating deleting for matrices
	void Datum::MatDelete(DatumValues& toDelete)
	{
		delete[] toDelete.m;
	}


	//Function for deleting memory for strings
	void Datum::StringDelete(DatumValues& toDelete)
	{
		delete[] toDelete.s;
	}

	//Function for deleting meory from RTTI pointers
	void Datum::PointerDelete(DatumValues& toDelete)
	{
		delete[] toDelete.p;
	}

	//Function for deleting meory from Scopes pointers
	void Datum::ScopeDelete(DatumValues& toDelete)
	{
		delete[] toDelete.sc;
	}

	//Bracket operator
	Scope& Datum::operator[](std::uint32_t index)
	{
		return *Get<Scope*>(index);
	}

	//Check external vs internal
	bool Datum::IsExternal()
	{
		return mIsExternal;
	}

}