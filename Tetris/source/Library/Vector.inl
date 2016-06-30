namespace Library
{

#pragma region Iterator
	//Default constructor
	//Set the index to the max unsigned integer to mark that it is not currently referring to anything
	template <typename T>
	Vector<T>::Iterator::Iterator() :
		mIndex(0xffffffff), mOwner(nullptr)
	{
		
	}

	//Constructor
	template <typename T>
	Vector<T>::Iterator::Iterator(unsigned int index, const Vector* owner) :
		mIndex(index), mOwner(owner)
	{
	}

	//Copy constructor
	template <typename T>
	Vector<T>::Iterator::Iterator(const typename Vector<T>::Iterator& rhs) :
		mIndex(0), mOwner(nullptr)
	{
		operator=(rhs);
	}

	//Assignment operator
	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const typename Vector<T>::Iterator& rhs)
	{
		//Self assignment check
		if (this == &rhs)
		{
			return *this;
		}

		mIndex = rhs.mIndex;
		mOwner = rhs.mOwner;
		return *this;
	}

	//Comparison operator
	template <typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return((mIndex == rhs.mIndex) && (mOwner == rhs.mOwner));
	}

	//Not-equal operator
	template <typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}

	//Prefix increment operator
	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (mIndex != (mOwner->Size() - 1))
		{
			++mIndex;
			return *this;
		}
		else
		{
			//Deal with going out of bounds
			mIndex = mOwner->Size();
			return *this;
		}
	}

	//Postfix increment operator
	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator temp = *this;
		operator++();
		return temp;
	}
	

	//Dereference operator
	template <typename T>
	T& Vector<T>::Iterator::operator*() const
	{
		return mOwner->operator[](mIndex);
	}


#pragma endregion
	//Constructor
	//Sets initial size to zero and the buffer to null
	template <typename T>
	Vector<T>::Vector() : 
		mSize(0), mCapacity(0), mBuffer(nullptr)
	{
	}

	//Destructor
	template <typename T>
	Vector<T>::~Vector()
	{
		Clear();
	}

	//Copy constructor
	template <typename T>
	Vector<T>::Vector(Vector& rhs) :
		mSize(0), mCapacity(0), mBuffer(nullptr)
	{
		operator=(rhs);		
	}

	//Assignment operator
	template <typename T>
	typename Vector<T>& Vector<T>::operator=(Vector& rhs)
	{
		Clear();
		//Check for self assignment
		if (this != &rhs)
		{
			for (unsigned int i = 0; i < rhs.Size(); ++i)
			{
				PushBack(rhs[i]);
			}
		}

		return *this;
	}

	//Check if the vector contains anything
	template <typename T>
	bool Vector<T>::IsEmpty()
	{
		return mSize == 0;
	}

	//Check number of elements
	template <typename T>
	unsigned int Vector<T>::Size() const
	{
		return mSize;
	}

	//Get front element
	template <typename T>
	T& Vector<T>::Front()
	{
		return mBuffer[0];
	}

	//Get back element
	template <typename T>
	T& Vector<T>::Back()
	{
		return mBuffer[mSize - 1];
	}

	//Get front element (const)
	template <typename T>
	T& Vector<T>::Front() const
	{
		return mBuffer[0];
	}

	//Get back element (const)
	template <typename T>
	T& Vector<T>::Back() const
	{
		return mBuffer[mSize - 1];
	}

	//Append an element to the end of the vector
	template <typename T>
	typename Vector<T>::Iterator Vector<T>::PushBack(T& newValue)
	{
		//If we don't have space for the new item, add 1 then double our capacity
		if ((mSize + 1) > mCapacity)
		{
			Reserve((mCapacity + 1) * 2);
		}
		
		mBuffer[mSize] = newValue;
		return Iterator(mSize++, this);
	}

	//Add space to the buffer
	//Note that this will never shrink the capacity and never delete items in the container
	//This also the only place where memory should ever be allocated in the Vector class
	template <typename T>
	void Vector<T>::Reserve(const unsigned int capacity)
	{
		if (capacity <= mCapacity)
		{
			if (capacity == 0)
			{
				return;
			}

			throw std::exception("Cannot reserve less capacity");
			return;
		}
				
		//Allocate memory into buffer
		T* tempBuffer = new T[capacity];


		if (mSize != 0)
		{
			//Copy values into the temporary buffer
			for (unsigned int i = 0; i < mSize; ++i)
			{
				tempBuffer[i] = mBuffer[i];
			}

			delete[] mBuffer;
		}

		mBuffer = tempBuffer;


		mCapacity = capacity;
	}

	//Remove the last element of the vector
	template <typename T>
	void Vector<T>::PopBack()
	{
		mSize--;
	}

	//Empty the vector
	template <typename T>
	void Vector<T>::Clear()
	{
		if (mCapacity > 0)
		{
			mSize = 0;
			mCapacity = 0;
			delete[] mBuffer;
			mBuffer = nullptr;
		}

	}

	//Brackets operator
	template <typename T>
	T& Vector<T>::operator[](const unsigned int index)
	{
		if (index >= mCapacity)
		{
			throw std::exception("out of bounds");
		}
		else if (index >= mSize)
		{
			mSize = index + 1;
		}
		return mBuffer[index];
	}

	//Brackets operator (const version)
	template <typename T>
	T& Vector<T>::operator[](const unsigned int index) const
	{
		if (index >= mCapacity)
		{
			throw std::exception("out of bounds");
		}
		return mBuffer[index];
	}

	//Find a reference to the item at the given index
	//If the index is larger than capacity, throw an exception
	//If the index is larger than the size, but smaller than the capacity, increase size to accomodate the index
	template <typename T>
	T& Vector<T>::At(const unsigned int index)
	{
		if (index > (mCapacity - 1))
		{
			throw std::exception("out of bounds");
		}
		else if (index >= mSize)
		{
			//Increase the size to accomidate the index
			mSize = index + 1;
		}

		return mBuffer[index];
	}

	//Return an iterator pointing at the beginning of this vector
	template <typename T>
	typename Vector<T>::Iterator Vector<T>::begin() const
	{
		return Iterator(0, this);
	}
	
	//Return an iterator indicating 'not in the container'
	template <typename T>
	typename Vector<T>::Iterator Vector<T>::end() const
	{
		return Iterator(mSize, this);
	}

	//Return an iterator pointing at a certain item in the vector
	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& item)
	{
		Iterator myIterator = begin();
		while (myIterator != end())
		{
			if (*(myIterator) == item)
			{
				break;
			}
			++myIterator;
		}

		return myIterator;
		

	}

	//Remove an element from the list pointed at by a given iterator
	template <typename T>
	void Vector<T>::Remove(const Iterator& target)
	{
		//Sanity check the target
		if ((target.mIndex >= mSize) || (target.mOwner != this))
		{
			throw std::exception("Invalid iterator");
		}

		mSize--;
		for (unsigned int i = target.mIndex; i < mSize; i++)
		{
			mBuffer[i] = mBuffer[i + 1];
		}

	}
	
	//Remove an element by index
	template <typename T>
	void Vector<T>::Remove(const std::uint32_t index)
	{
		//Sanity check the target
		if (index >= mSize)
		{
			throw std::exception("Invalid index");
		}

		mSize--;
		for (std::uint32_t i = index; i < mSize; i++)
		{
			mBuffer[i] = mBuffer[i + 1];
		}
	}

	//Remove all elements between two iterators
	template <typename T>
	void Vector<T>::Remove(const Iterator& startTarget, const Iterator& endTarget)
	{
		//Sanity check both targets
		if ((startTarget.mIndex >= mSize) || (endTarget.mOwner != this))
		{
			throw std::exception("Invalid iterator");
		}
		else if (endTarget.mIndex >= mSize)
		{
			throw std::exception("Invalid iterator");
		}
		else if (startTarget.mIndex >= endTarget.mIndex)
		{
			return;
		}

		unsigned int i = startTarget.mIndex;
		unsigned int j = endTarget.mIndex + 1;
		unsigned int numElements = j - i;

		//Copy the elements after the removal into the earlier parts of the array
		for (; j < mSize; i++, j++)
		{
			mBuffer[i] = mBuffer[j];
		}

		mSize -= numElements;
	}
}